#include "gtest/gtest.h"
#include <boost/any.hpp>
#include <cpprest/http_client.h>
#include <cpprest/streams.h>
#include <darabonba/util.hpp>

using namespace std;

TEST(tests_parse, toBytes) {
  vector<uint8_t> bytes({116, 101, 115, 116});
  ASSERT_EQ(bytes,
            Darabonba_Util::Client::toBytes(make_shared<string>("test")));
}

TEST(tests_parse, toString) {
  vector<uint8_t> bytes({116, 101, 115, 116});
  ASSERT_EQ(string("test"), Darabonba_Util::Client::toString(
                                make_shared<vector<uint8_t>>(bytes)));
}

template <typename T> bool eq_boost_any(T val1, boost::any val2) {
  return val1 == boost::any_cast<T>(val2);
}

TEST(tests_parse, parseJSON) {
  string json =
      R"({"bool":true,"foo":"bar","long":9223372036854775807,"map":{"foo":"bar"},"string":"string","vector":["foo","bar"]})";
  map<string, boost::any> m = {
      {"foo", boost::any("bar")},
      {"string", boost::any(string("string"))},
      {"long", boost::any(LONG_MAX)},
      {"bool", boost::any(true)},
      {"vector", boost::any(vector<boost::any>({{boost::any("foo")}}))},
      {"map",
       boost::any(map<string, boost::any>({{"foo", boost::any("bar")}}))}};
  boost::any target =
      Darabonba_Util::Client::parseJSON(make_shared<string>(json));
  map<string, boost::any> data =
      boost::any_cast<map<string, boost::any>>(target);
  vector<boost::any> vec = boost::any_cast<vector<boost::any>>(data["vector"]);

  ASSERT_EQ(string("foo"), boost::any_cast<string>(vec[0]));
  ASSERT_EQ(string("bar"), boost::any_cast<string>(vec[1]));
}

TEST(tests_parse, toJSONString) {
  map<string, boost::any> m = {
      {"foo", boost::any("bar")},
      {"string", boost::any(string("string"))},
      {"long", boost::any(LONG_MAX)},
      {"bool", boost::any(true)},
      {"vector", boost::any(vector<boost::any>({{boost::any("foo")}}))},
      {"map",
       boost::any(map<string, boost::any>({{"foo", boost::any("bar")}}))}};
  string res = Darabonba_Util::Client::toJSONString(make_shared<boost::any>(m));
  ASSERT_EQ(
      string(
          "{\"bool\":true,\"foo\":\"bar\",\"long\":9223372036854775807,\"map\":"
          "{\"foo\":\"bar\"},\"string\":string,\"vector\":[\"foo\"]}"),
      res);
}

TEST(tests_parse, readAsBytes) {
  string str("string");
  concurrency::streams::stringstreambuf string_buf(str);

  vector<uint8_t> res =
      Darabonba_Util::Client::readAsBytes(make_shared<Darabonba::Stream>(
          make_shared<concurrency::streams::istream>(string_buf)));
  vector<uint8_t> exp(str.begin(), str.end());
  ASSERT_EQ(exp, res);
}

TEST(tests_parse, readAsString) {
  string str("string");
  concurrency::streams::stringstreambuf string_buf(str);

  string res =
      Darabonba_Util::Client::readAsString(make_shared<Darabonba::Stream>(
          make_shared<concurrency::streams::istream>(string_buf)));
  ASSERT_EQ(str, res);
}

TEST(tests_parse, readAsJSON) {
  string json(R"({"test": "string"})");
  concurrency::streams::stringstreambuf string_buf(json);

  map<string, boost::any> res = boost::any_cast<map<string, boost::any>>(
      Darabonba_Util::Client::readAsJSON(make_shared<Darabonba::Stream>(
          make_shared<concurrency::streams::istream>(string_buf))));
  ASSERT_EQ(string("string"), boost::any_cast<string>(res["test"]));

  string json_array(R"(["test", "string"])");
  vector<boost::any> array = boost::any_cast<vector<boost::any>>(
      Darabonba_Util::Client::readAsJSON(make_shared<Darabonba::Stream>(
          make_shared<stringstream>(json_array))));

  ASSERT_EQ(string("test"), boost::any_cast<string>(array[0]));
  ASSERT_EQ(string("string"), boost::any_cast<string>(array[1]));
}

TEST(test_parse, toFormString) {
  map<string, boost::any> m = {{"RegionId", string("cn-hangzhou")}};
  string res = Darabonba_Util::Client::toFormString(
      make_shared<map<string, boost::any>>(m));
  ASSERT_EQ("RegionId=cn-hangzhou", res);
}
