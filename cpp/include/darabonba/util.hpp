#ifndef DARABONBA_UTIL_H_
#define DARABONBA_UTIL_H_

#include <boost/any.hpp>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <cpprest/streams.h>

using namespace Darabonba;
using namespace std;

namespace Darabonba_Util {
class RuntimeOptions : public Model {
public:
  explicit RuntimeOptions(const std::map<string, boost::any> &config)
      : Model(config) {};
  RuntimeOptions();
  ~RuntimeOptions();

  bool getAutoretry() {
    string name = "autoretry";
    bool prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<bool>(val);
    }
    return prop_val;
  }
  void setAutoretry(bool val) {
    string name = "autoretry";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  bool getIgnoreSSL() {
    string name = "ignoreSSL";
    bool prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<bool>(val);
    }
    return prop_val;
  }
  void setIgnoreSSL(bool val) {
    string name = "ignoreSSL";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getMaxAttempts() {
    string name = "maxAttempts";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setMaxAttempts(int val) {
    string name = "maxAttempts";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getBackoffPolicy() {
    string name = "backoffPolicy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setBackoffPolicy(string val) {
    string name = "backoffPolicy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getBackoffPeriod() {
    string name = "backoffPeriod";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setBackoffPeriod(int val) {
    string name = "backoffPeriod";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getReadTimeout() {
    string name = "readTimeout";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setReadTimeout(int val) {
    string name = "readTimeout";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getConnectTimeout() {
    string name = "connectTimeout";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setConnectTimeout(int val) {
    string name = "connectTimeout";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getHttpProxy() {
    string name = "httpProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setHttpProxy(string val) {
    string name = "httpProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getHttpsProxy() {
    string name = "httpsProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setHttpsProxy(string val) {
    string name = "httpsProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getNoProxy() {
    string name = "noProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setNoProxy(string val) {
    string name = "noProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getMaxIdleConns() {
    string name = "maxIdleConns";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setMaxIdleConns(int val) {
    string name = "maxIdleConns";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getLocalAddr() {
    string name = "localAddr";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setLocalAddr(string val) {
    string name = "localAddr";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getSocks5Proxy() {
    string name = "socks5Proxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setSocks5Proxy(string val) {
    string name = "socks5Proxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getSocks5NetWork() {
    string name = "socks5NetWork";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setSocks5NetWork(string val) {
    string name = "socks5NetWork";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
};
class Client {
public:
  Client();
  ~Client();

  static std::vector<uint8_t> toBytes(const string &val);
  static string toString(std::vector<uint8_t> val);
  static boost::any parseJSON(const string &val);
  static std::vector<uint8_t> readAsBytes(const concurrency::streams::istream &stream);
  static string readAsString(const concurrency::streams::istream &stream);
  static boost::any readAsJSON(const concurrency::streams::istream &stream);
  static string getNonce();
  static string getDateUTCString();
  static string defaultString(void *real, string default_ = "");
  static int defaultNumber(void *real, int default_);
  static string toFormString(map<string, boost::any> val);
  static string toJSONString(boost::any val);
  static bool empty(const string& val);
  static bool equalString(const string &val1, const string &val2);
  static bool equalNumber(int val1, int val2);
  static bool isUnset(void *value);
  static map<string, string>
  stringifyMapValue(const map<string, boost::any> &m);
  static map<string, boost::any> anyifyMapValue(const map<string, string> &m);
  static bool assertAsBoolean(const boost::any &value);
  static string assertAsString(const boost::any &value);
  static std::vector<uint8_t> assertAsBytes(const boost::any &value);
  static int assertAsNumber(const boost::any &value);
  static map<string, boost::any> assertAsMap(boost::any value);
  static string getUserAgent(string userAgent = "");
  static bool is2xx(int code);
  static bool is3xx(int code);
  static bool is4xx(int code);
  static bool is5xx(int code);
  static void validateModel(Model m);
  static map<string, boost::any> toMap(Model in);
  static void sleep(int millisecond);
  static vector<map<string, boost::any>> toArray(boost::any input);
  static concurrency::streams::istream assertAsReadable(boost::any value);
};
} // namespace Darabonba_Util

#endif
