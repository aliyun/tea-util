#include "gtest/gtest.h"
#include <darabonba/util.hpp>
#include <boost/lexical_cast.hpp>

using namespace Darabonba_Util;
using namespace boost;

TEST(assert, test_empty) {
  string str;
  ASSERT_TRUE(Client::empty(str));
  str = "foo";
  ASSERT_FALSE(Client::empty(str));
}

TEST(assert, equalString) {
  string left;
  string right;
  ASSERT_TRUE(Client::equalString(left, right));

  left = "foo";
  ASSERT_FALSE(Client::equalString(left, right));

  right = "bar";
  ASSERT_FALSE(Client::equalString(left, right));
}

TEST(assert, equalNumber) {
  int left = 0;
  int right = 0;
  ASSERT_EQ(left, right);

  right = 1;
  ASSERT_FALSE(Client::equalNumber(left, right));
}

TEST(assert, isUnset) {
  string *str = nullptr;
  ASSERT_TRUE(Client::isUnset(str));
}

TEST(assert, stringifyMapValue) {
  map<string, any> m;
  m["int"] = any(int(1));
  m["long"] = any(long(LONG_MAX));
  m["double"] = any(double(0.1));
  m["float"] = any(float(0.1));
  m["bool"] = any(bool(true));
  m["string"] = any(string("test"));

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
  bool b = true;
  ASSERT_TRUE(Client::assertAsBoolean(any(b)));

  try {
    Client::assertAsBoolean(any("test"));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bool", err);
  }
}

TEST(assert, assertAsString) {
  string val = "test";
  ASSERT_EQ(string("test"), Client::assertAsString(any(val)));

  try {
    Client::assertAsBoolean(any(true));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a string", err);
  }
}

TEST(assert, assertAsBytes) {
  vector<uint8_t> val;
  val.push_back(1);
  ASSERT_EQ(val, Client::assertAsBytes(any(val)));

  try {
    Client::assertAsBoolean(any(true));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a bytes", err);
  }
}

TEST(assert, assertAsNumber) {
  int val = 10;
  ASSERT_EQ(val, Client::assertAsNumber(any(val)));

  try {
    Client::assertAsNumber(any(true));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a int number", err);
  }
}

TEST(assert, assertAsMap) {
  map<string, any> val;
  val["foo"] = any(string("bar"));
  map<string, any> res = Client::assertAsMap(any(val));
  ASSERT_EQ(any_cast<string>(val["foo"]), any_cast<string>(res["foo"]));

  try {
    Client::assertAsMap(any(true));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a map<string, any>", err);
  }
}

TEST(assert, assertAsReadable) {
  concurrency::streams::istream val;
  concurrency::streams::istream res = Client::assertAsReadable(any(val));
  ASSERT_EQ(res, val);

  try {
    Client::assertAsReadable(any(true));
    ASSERT_TRUE(false);
  } catch (boost::exception &e) {
    string err = boost::current_exception_cast<std::runtime_error>()->what();
    ASSERT_EQ("value is not a concurrency::streams::istream", err);
  }
}

TEST(assert, is2xx) {
  ASSERT_TRUE(Client::is2xx(200));
  ASSERT_TRUE(Client::is2xx(201));
  ASSERT_FALSE(Client::is2xx(300));
}

TEST(assert, is3xx) {
  ASSERT_TRUE(Client::is2xx(300));
  ASSERT_TRUE(Client::is2xx(301));
  ASSERT_FALSE(Client::is2xx(400));
}

TEST(assert, is4xx) {
  ASSERT_TRUE(Client::is2xx(400));
  ASSERT_TRUE(Client::is2xx(401));
  ASSERT_FALSE(Client::is2xx(500));
}

TEST(assert, is5xx) {
  ASSERT_TRUE(Client::is2xx(500));
  ASSERT_TRUE(Client::is2xx(501));
  ASSERT_FALSE(Client::is2xx(200));
}
