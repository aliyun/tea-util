#include "gtest/gtest.h"
#include <boost/lexical_cast.hpp>
#include <darabonba/util.hpp>
#include <fstream>

using namespace Darabonba_Util;
using namespace std;

TEST(tests_assert, test_empty) {
  string str;
  ASSERT_TRUE(Client::empty(make_shared<string>(str)));
  str = "foo";
  ASSERT_FALSE(Client::empty(make_shared<string>(str)));
}

TEST(tests_assert, equalString) {
  shared_ptr<string> left;
  shared_ptr<string> right;

  ASSERT_TRUE(Client::equalString(left, right));

  left = make_shared<string>("foo");
  ASSERT_FALSE(Client::equalString(left, right));

  right = make_shared<string>("bar");
  ASSERT_FALSE(Client::equalString(left, right));
}

TEST(tests_assert, equalNumber) {
  shared_ptr<int> left(new int(0));
  shared_ptr<int> right(new int(0));
  ASSERT_EQ(*left, *right);

  *right = 1;
  ASSERT_FALSE(Client::equalNumber(left, right));
}

class TestModel: public Darabonba::Model
{
  map<string, boost::any> toMap() override {
    return map<string, boost::any>();
  };
  void fromMap(map<string, boost::any> m) override {};
  void validate() override {};
};

TEST(tests_assert, isUnset) {
  shared_ptr<string> str = nullptr;
  ASSERT_TRUE(Client::isUnset<string>(str));

  str = make_shared<string>("test");
  ASSERT_FALSE(Client::isUnset<string>(str));

  shared_ptr<int> val;
  ASSERT_TRUE(Client::isUnset<int>(val));

  boost::any model = make_shared<TestModel>();
  shared_ptr<TestModel> tm;
  boost::any model1 = tm;
  ASSERT_FALSE(Darabonba_Util::Client::isUnset<TestModel>(model));
  ASSERT_TRUE(Darabonba_Util::Client::isUnset<TestModel>(model1));

  map<string, boost::any> mp;
  boost::any any = make_shared<boost::any>(mp["key"]);
  ASSERT_TRUE(Darabonba_Util::Client::isUnset<boost::any>(any));
}

TEST(tests_assert, stringifyMapValue) {
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

TEST(tests_assert, assertAsBoolean) {
  shared_ptr<bool> val = make_shared<bool>(true);
  ASSERT_TRUE(Client::assertAsBoolean(val));

  try {
    shared_ptr<string> fake = make_shared<string>("test");
    Client::assertAsBoolean(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bool", err);
  }
}

TEST(tests_assert, assertAsString) {
  shared_ptr<string> val = make_shared<string>("test");
  ASSERT_EQ(string("test"), Client::assertAsString(val));

  try {
    shared_ptr<bool> fake = make_shared<bool>(true);
    Client::assertAsString(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a string", err);
  }
}

TEST(tests_assert, assertAsBytes) {
  shared_ptr<vector<uint8_t>> val = make_shared<vector<uint8_t>>();
  val->push_back(1);
  vector<uint8_t> vec = *val;
  ASSERT_EQ(vec, Client::assertAsBytes(val));

  try {
    shared_ptr<bool> fake = make_shared<bool>(true);
    Client::assertAsBytes(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bytes", err);
  }
}

TEST(tests_assert, assertAsNumber) {
  shared_ptr<int> val = make_shared<int>(10);
  ASSERT_EQ(10, Client::assertAsNumber(val));

  try {
    shared_ptr<bool> fake = make_shared<bool>(true);
    Client::assertAsNumber(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a int number", err);
  }
}

TEST(tests_assert, assertAsMap) {
  shared_ptr<map<string, boost::any>> val =
      make_shared<map<string, boost::any>>(
          map<string, boost::any>({{"foo", string("bar")}}));

  map<string, boost::any> res = Client::assertAsMap(val);
  ASSERT_EQ(string("bar"), boost::any_cast<string>(res["foo"]));

  try {
    shared_ptr<bool> fake = make_shared<bool>(true);
    Client::assertAsMap(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a map<string, any>", err);
  }
}

TEST(tests_assert, assertAsReadable) {
  shared_ptr<Darabonba::Stream> val =
      make_shared<Darabonba::Stream>(make_shared<stringstream>("test stream"));
  Darabonba::Stream res = Client::assertAsReadable(val);
  ASSERT_EQ(string("test stream"), res.read());

  try {
    shared_ptr<bool> fake = make_shared<bool>(true);
    Client::assertAsReadable(fake);
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a readable", err);
  }
}

TEST(tests_assert, is2xx) {
  ASSERT_TRUE(Client::is2xx(make_shared<int>(200)));
  ASSERT_TRUE(Client::is2xx(make_shared<int>(201)));
  ASSERT_FALSE(Client::is2xx(make_shared<int>(300)));
}

TEST(tests_assert, is3xx) {
  ASSERT_TRUE(Client::is3xx(make_shared<int>(300)));
  ASSERT_TRUE(Client::is3xx(make_shared<int>(301)));
  ASSERT_FALSE(Client::is3xx(make_shared<int>(400)));
}

TEST(tests_assert, is4xx) {
  ASSERT_TRUE(Client::is4xx(make_shared<int>(400)));
  ASSERT_TRUE(Client::is4xx(make_shared<int>(401)));
  ASSERT_FALSE(Client::is4xx(make_shared<int>(500)));
}

TEST(tests_assert, is5xx) {
  ASSERT_TRUE(Client::is5xx(make_shared<int>(500)));
  ASSERT_TRUE(Client::is5xx(make_shared<int>(501)));
  ASSERT_FALSE(Client::is5xx(make_shared<int>(600)));
}

TEST(tests_runtime, basic) {
  map<string, boost::any> runtime_opt = {{"autoretry", "autoretry"}};
  RuntimeOptions runtime(runtime_opt);
}