#include "gtest/gtest.h"
#include <darabonba/util.hpp>
#include <boost/any.hpp>

using namespace std;

TEST(tests_parse, toBytes) {
  std::vector<uint8_t> bytes({116, 101, 115, 116});
  ASSERT_EQ(bytes, Darabonba_Util::Client::toBytes(new string("test")));
}

TEST(tests_parse, toString) {
  std::vector<uint8_t> bytes({116, 101, 115, 116});
  ASSERT_EQ(string("test"), Darabonba_Util::Client::toString(&bytes));
}

template<typename T>
bool eq_boost_any(T val1, boost::any val2) {
  return val1 == boost::any_cast<T>(val2);
}

TEST(tests_parse, parseJSON) {
  string json =
      R"({"bool":true,"foo":"bar","long":9223372036854775807,"map":{"foo":"bar"},"string":string,"vector":["foo"]})";
  map<string, boost::any> m = {
      {"foo", boost::any("bar")},
      {"string", boost::any(string("string"))},
      {"long", boost::any(LONG_MAX)},
      {"bool", boost::any(true)},
      {"vector", boost::any(vector<boost::any>({{boost::any("foo")}}))},
      {"map", boost::any(map<string, boost::any>({{"foo", boost::any("bar")}}))}
  };
  ASSERT_TRUE(eq_boost_any<const char *>("bar", m["foo"]));
  ASSERT_TRUE(eq_boost_any<string>(string("string"), m["string"]));
  ASSERT_TRUE(eq_boost_any<long>(LONG_MAX, m["long"]));
}

TEST(tests_parse, toJSONString) {
  map<string, boost::any> m = {
      {"foo", boost::any("bar")},
      {"string", boost::any(string("string"))},
      {"long", boost::any(LONG_MAX)},
      {"bool", boost::any(true)},
      {"vector", boost::any(vector<boost::any>({
                                                   {boost::any("foo")}
                                               }))
      },
      {"map", boost::any(map<string, boost::any>({
                                                     {"foo", boost::any("bar")}
                                                 }))
      }
  };
  string res = Darabonba_Util::Client::toJSONString(new boost::any(m));
  ASSERT_EQ(string(
                "{\"bool\":true,\"foo\":\"bar\",\"long\":9223372036854775807,\"map\":{\"foo\":\"bar\"},\"string\":string,\"vector\":[\"foo\"]}"),
            res);
}