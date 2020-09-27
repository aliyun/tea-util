#include "gtest/gtest.h"
#include <darabonba/util.hpp>
#include <boost/lexical_cast.hpp>

using namespace Darabonba_Util;
using namespace std;

TEST(assert, test_empty) {
  string str;
  ASSERT_TRUE(Client::empty(make_shared<string>(str)));
  str = "foo";
  ASSERT_FALSE(Client::empty(make_shared<string>(str)));
}

TEST(assert, equalString) {
  shared_ptr<string> left;
  shared_ptr<string> right;

  ASSERT_TRUE(Client::equalString(left, right));

  left = make_shared<string>("foo");
  ASSERT_FALSE(Client::equalString(left, right));

  right = make_shared<string>("bar");
  ASSERT_FALSE(Client::equalString(left, right));
}

TEST(assert, equalNumber) {
  shared_ptr<int> left(new int(0));
  shared_ptr<int> right(new int(0));
  ASSERT_EQ(*left, *right);

  *right = 1;
  ASSERT_FALSE(Client::equalNumber(left, right));
}

TEST(assert, isUnset) {
  shared_ptr<string> str;
  ASSERT_TRUE(Client::isUnset(str));
}

TEST(assert, stringifyMapValue) {
  shared_ptr<map<string, boost::any>> m(new map<string, boost::any>({
       {"int", boost::any(1)},
       {"long", boost::any(LONG_MAX)},
       {"double", boost::any(0.1)},
       {"float", boost::any(0.1)},
       {"bool", boost::any(true)},
       {"string", boost::any(string("test"))},
   }));

  map<string, string> expected;
  expected["int"] = "1";
  expected["long"] = "9223372036854775807";
  expected["double"] = "0.100000";
  expected["float"] = "0.100000";
  expected["bool"] = "true";
  expected["string"] = "test";
  ASSERT_EQ(expected, Client::stringifyMapValue(m));
}

TEST(assert, assertAsBoolean) {
  shared_ptr<boost::any> val(new boost::any(true));
  ASSERT_TRUE(Client::assertAsBoolean(val));

  try {
    *val = boost::any(string("test"));
    Client::assertAsBoolean(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bool", err);
  }
}

TEST(assert, assertAsString) {
  shared_ptr<boost::any> val(new boost::any(string("test")));
  ASSERT_EQ(string("test"), Client::assertAsString(val));

  try {
    *val = boost::any(true);
    Client::assertAsString(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a string", err);
  }
}

TEST(assert, assertAsBytes) {
  vector<uint8_t> vec;
  vec.push_back(1);
  shared_ptr<boost::any> val(new boost::any(vec));
  ASSERT_EQ(vec, Client::assertAsBytes(val));

  try {
    *val = boost::any(true);
    Client::assertAsBytes(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bytes", err);
  }
}

TEST(assert, assertAsNumber) {
  shared_ptr<boost::any> val(new boost::any(10));
  ASSERT_EQ(10, Client::assertAsNumber(val));

  try {
    *val = boost::any(true);
    Client::assertAsNumber(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a int number", err);
  }
}

TEST(assert, assertAsMap) {
  shared_ptr<boost::any> val(new boost::any(map<string, boost::any>({
     {"foo", string("bar")}
  })));
  map<string, boost::any> res = Client::assertAsMap(val);
  ASSERT_EQ(string("bar"), boost::any_cast<string>(res["foo"]));

  try {
    *val = boost::any(true);
    Client::assertAsMap(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a map<string, any>", err);
  }
}

TEST(assert, assertAsReadable) {
  concurrency::streams::istream s;
  shared_ptr<boost::any> val(new boost::any(s));
  concurrency::streams::istream res = Client::assertAsReadable(val);
  ASSERT_EQ(res, s);

  try {
    *val = boost::any(true);
    Client::assertAsReadable(val);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a concurrency::streams::istream", err);
  }
}

TEST(assert, is2xx) {
  ASSERT_TRUE(Client::is2xx(make_shared<int>(200)));
  ASSERT_TRUE(Client::is2xx(make_shared<int>(201)));
  ASSERT_FALSE(Client::is2xx(make_shared<int>(300)));
}

TEST(assert, is3xx) {
  ASSERT_TRUE(Client::is3xx(make_shared<int>(300)));
  ASSERT_TRUE(Client::is3xx(make_shared<int>(301)));
  ASSERT_FALSE(Client::is3xx(make_shared<int>(400)));
}

TEST(assert, is4xx) {
  ASSERT_TRUE(Client::is4xx(make_shared<int>(400)));
  ASSERT_TRUE(Client::is4xx(make_shared<int>(401)));
  ASSERT_FALSE(Client::is4xx(make_shared<int>(500)));
}

TEST(assert, is5xx) {
  ASSERT_TRUE(Client::is5xx(make_shared<int>(500)));
  ASSERT_TRUE(Client::is5xx(make_shared<int>(501)));
  ASSERT_FALSE(Client::is5xx(make_shared<int>(600)));
}

TEST(runtime, runtime_test)
{
  map<string, boost::any> runtime_opt = {
      {"autoretry", "autoretry"}
  };
  RuntimeOptions runtime(runtime_opt);
}