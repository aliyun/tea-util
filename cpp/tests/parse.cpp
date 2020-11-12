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

template<typename T> bool eq_boost_any(T val1, boost::any val2) {
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

class TestToArrayModel : public Darabonba::Model {
public:
  TestToArrayModel() = default;
  explicit TestToArrayModel(const std::map<string, boost::any> &config) : Darabonba::Model(config) {
    fromMap(config);
  };

  void validate() override {}

  map<string, boost::any> toMap() override {
    map<string, boost::any> res;
    if (key) {
      res["key"] = boost::any(*key);
    }
    if (value) {
      res["value"] = boost::any(*value);
    }
    return res;
  }

  void fromMap(map<string, boost::any> m) override {
    if (m.find("key") != m.end()) {
      key = make_shared<string>(boost::any_cast<string>(m["key"]));
    }
    if (m.find("value") != m.end()) {
      value = make_shared<string>(boost::any_cast<string>(m["value"]));
    }
  }

  shared_ptr<string> key{};
  shared_ptr<string> value{};

  ~TestToArrayModel() = default;
};

TEST(tests_parse, toArray) {
  TestToArrayModel t1;
  t1.key = make_shared<string>("k1");
  t1.value = make_shared<string>("v1");
  TestToArrayModel t2;
  t2.key = make_shared<string>("k2");
  t2.value = make_shared<string>("v2");
  vector<TestToArrayModel> vec;
  vec.push_back(t1);
  vec.push_back(t2);

  vector<map<string, boost::any>> res =
      Darabonba_Util::Client::toArray<vector<TestToArrayModel>>(
          make_shared<vector<TestToArrayModel>>(vec));
  map<string, boost::any> m1 = res[0];
  map<string, boost::any> m2 = res[1];
  ASSERT_EQ("k1",
            boost::any_cast<string>(m1["key"]));
  ASSERT_EQ("v1",
            boost::any_cast<string>(m1["value"]));
  ASSERT_EQ("k2",
            boost::any_cast<string>(m2["key"]));
  ASSERT_EQ("v2",
            boost::any_cast<string>(m2["value"]));
}

void testAny(const boost::any &value, const std::string &expected) {
  string res = Darabonba_Util::Client::toJSONString(value);
  ASSERT_EQ(expected, res);
}

void testVoid(shared_ptr<void> value, std::string &expected) {
  string res = Darabonba_Util::Client::toJSONString(value);
  ASSERT_EQ(expected, res);
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
  string res = Darabonba_Util::Client::toJSONString(
      make_shared<map<string, boost::any>>(m));
  string expected = "{\"bool\": true, \"foo\": \"bar\", \"long\": 9223372036854775807, \"map\": "
                    "{\"foo\": \"bar\"}, \"string\": \"string\", \"vector\": [\"foo\"]}";
  ASSERT_EQ(expected, res);

  testAny(make_shared<map<string, boost::any>>(m), expected);
  testVoid(make_shared<map<string, boost::any>>(m), expected);

  vector<boost::any> test_array = {"test", 1, 2.012123, true, map<string, boost::any>({{"key", "value"}})};
  ASSERT_EQ("[\"test\", 1, 2.012123, true, {\"key\": \"value\"}]", Darabonba_Util::Client::toJSONString(
      make_shared<vector<boost::any>>(test_array)));
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
  string json(
      R"({"test": "string", "int": 100, "long": -9999999999, "double": 1.0212199})");
  concurrency::streams::stringstreambuf string_buf(json);

  map<string, boost::any> res = boost::any_cast<map<string, boost::any>>(
      Darabonba_Util::Client::readAsJSON(make_shared<Darabonba::Stream>(
          make_shared<concurrency::streams::istream>(string_buf))));
  ASSERT_EQ(string("string"), boost::any_cast<string>(res["test"]));
  ASSERT_EQ(100, boost::any_cast<int>(res["int"]));
  ASSERT_EQ(-9999999999, boost::any_cast<long>(res["long"]));
  ASSERT_EQ(double(1.0212199), boost::any_cast<double>(res["double"]));

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
