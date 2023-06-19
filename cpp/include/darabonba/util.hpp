// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_UTIL_H_
#define DARABONBA_UTIL_H_

#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba {
class Util {
public:
  /************************** helper **************************/
  static string getNonce();

  static string getDateUTCString();

  static string getUserAgent(const string &userAgent);

  static void sleep(const int &millisecond);

  static void validateModel(const shared_ptr<Darabonba::Model> &m);

  /************************** default **************************/
  static string defaultString(const string &real,
                              const string &default_);

  static int64_t defaultNumber(const int64_t &real,
                           const int64_t &default_);

  /************************** parse **************************/
  static map<string, string> stringifyMapValue(const json &m);

  static json anyifyMapValue(const map<string, string> &m);

  static json toMap(const shared_ptr<Darabonba::Model> &in);

  static vector<uint8_t> toBytes(const string &val);

  static string toString(const vector<uint8_t> &val);

  static vector<json> toArray(const json &input) {
    if(!input.is_array()) {
      throw Darabonba::Error("input is not a array");
    }
    return input.get<vector<json>>();
  };

  static string toFormString(const json &val);

  static string toJSONString(const json &value);

  static json parseJSON(const string &val);

  static vector<uint8_t>
  readAsBytes(Darabonba::ResponseBody* respBody);

  static string readAsString(Darabonba::ResponseBody* respBody);

  static json readAsJSON(Darabonba::ResponseBody* respBody);

  /************************** assert **************************/
  static bool isUnset(const json &value) {
    return value.empty() || value.is_null();
  };

  static bool empty(const string &val);

  static bool equalString(const string &val1,
                          const string &val2);

  static bool equalNumber(const int64_t &val1,
                          const int64_t &val2);

  static bool assertAsBoolean(const json &value);

  static string assertAsString(const json &value);

  static vector<uint8_t> assertAsBytes(const json &value);

  static int64_t assertAsNumber(const json &value);

  static json assertAsMap(const json &value);

  static ostringstream* assertAsReadable(void* value);

  static bool is2xx(const int64_t &code);

  static bool is3xx(const int64_t &code);

  static bool is4xx(const int64_t &code);

  static bool is5xx(const int64_t &code);

  Util(){};
  ~Util(){};
};
} // namespace Darabonba_Util

#endif
