// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_UTIL_H_
#define DARABONBA_UTIL_H_

#include <boost/any.hpp>
#include <cpprest/streams.h>
#include <darabonba/core.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace Darabonba_Util {
class RuntimeOptions : public Darabonba::Model {
protected:
  void _init() {
    _name = map<string, string>({
        {"autoretry", "autoretry"},
        {"ignoreSSL", "ignoreSSL"},
        {"maxAttempts", "max_attempts"},
        {"backoffPolicy", "backoff_policy"},
        {"backoffPeriod", "backoff_period"},
        {"readTimeout", "readTimeout"},
        {"connectTimeout", "connectTimeout"},
        {"httpProxy", "httpProxy"},
        {"httpsProxy", "httpsProxy"},
        {"noProxy", "noProxy"},
        {"maxIdleConns", "maxIdleConns"},
        {"localAddr", "localAddr"},
        {"socks5Proxy", "socks5Proxy"},
        {"socks5NetWork", "socks5NetWork"},
    });
  }

public:
  RuntimeOptions() { _init(); };
  explicit RuntimeOptions(const map<string, boost::any> &config)
      : Darabonba::Model(config) {
    _init();
  };

  void validate(){};
  void fromMap(map<string, boost::any> m) {}

  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (autoretry) {
      res["autoretry"] = boost::any(*autoretry);
    }
    if (ignoreSSL) {
      res["ignoreSSL"] = boost::any(*ignoreSSL);
    }
    if (maxAttempts) {
      res["max_attempts"] = boost::any(*maxAttempts);
    }
    if (backoffPolicy) {
      res["backoff_policy"] = boost::any(*backoffPolicy);
    }
    if (backoffPeriod) {
      res["backoff_period"] = boost::any(*backoffPeriod);
    }
    if (readTimeout) {
      res["readTimeout"] = boost::any(*readTimeout);
    }
    if (connectTimeout) {
      res["connectTimeout"] = boost::any(*connectTimeout);
    }
    if (httpProxy) {
      res["httpProxy"] = boost::any(*httpProxy);
    }
    if (httpsProxy) {
      res["httpsProxy"] = boost::any(*httpsProxy);
    }
    if (noProxy) {
      res["noProxy"] = boost::any(*noProxy);
    }
    if (maxIdleConns) {
      res["maxIdleConns"] = boost::any(*maxIdleConns);
    }
    if (localAddr) {
      res["localAddr"] = boost::any(*localAddr);
    }
    if (socks5Proxy) {
      res["socks5Proxy"] = boost::any(*socks5Proxy);
    }
    if (socks5NetWork) {
      res["socks5NetWork"] = boost::any(*socks5NetWork);
    }
    return res;
  }

  shared_ptr<bool> autoretry{};
  shared_ptr<bool> ignoreSSL{};
  shared_ptr<int> maxAttempts{};
  shared_ptr<string> backoffPolicy{};
  shared_ptr<int> backoffPeriod{};
  shared_ptr<int> readTimeout{};
  shared_ptr<int> connectTimeout{};
  shared_ptr<string> httpProxy{};
  shared_ptr<string> httpsProxy{};
  shared_ptr<string> noProxy{};
  shared_ptr<int> maxIdleConns{};
  shared_ptr<string> localAddr{};
  shared_ptr<string> socks5Proxy{};
  shared_ptr<string> socks5NetWork{};

  ~RuntimeOptions(){};
};
class Client {
public:
  static vector<uint8_t> toBytes(const shared_ptr<string> &val);
  static string toString(const shared_ptr<vector<uint8_t>> &val);
  static boost::any parseJSON(const shared_ptr<string> &val);
  static vector<uint8_t>
  readAsBytes(const shared_ptr<Darabonba::Stream> &stream);
  static string readAsString(const shared_ptr<Darabonba::Stream> &stream);
  static boost::any readAsJSON(const shared_ptr<Darabonba::Stream> &stream);
  static string getNonce();
  static string getDateUTCString();
  static string defaultString(const shared_ptr<string> &real,
                              const shared_ptr<string> &default_);
  static int defaultNumber(const shared_ptr<int> &real,
                           const shared_ptr<int> &default_);
  static string toFormString(shared_ptr<map<string, boost::any>> val);
  static string toJSONString(const shared_ptr<boost::any> &val);
  static bool empty(const shared_ptr<string> &val);
  static bool equalString(const shared_ptr<string> &val1,
                          const shared_ptr<string> &val2);
  static bool equalNumber(const shared_ptr<int> &val1,
                          const shared_ptr<int> &val2);
  static bool isUnset(const shared_ptr<void> &value);
  static map<string, string>
  stringifyMapValue(const shared_ptr<map<string, boost::any>> &m);
  static map<string, boost::any>
  anyifyMapValue(const shared_ptr<map<string, string>> &m);
  static bool assertAsBoolean(const shared_ptr<boost::any> &value);
  static string assertAsString(const shared_ptr<boost::any> &value);
  static vector<uint8_t> assertAsBytes(const shared_ptr<boost::any> &value);
  static int assertAsNumber(const shared_ptr<boost::any> &value);
  static map<string, boost::any>
  assertAsMap(const shared_ptr<boost::any> &value);
  static string getUserAgent(const shared_ptr<string> &userAgent);
  static bool is2xx(const shared_ptr<int> &code);
  static bool is3xx(const shared_ptr<int> &code);
  static bool is4xx(const shared_ptr<int> &code);
  static bool is5xx(const shared_ptr<int> &code);
  static void validateModel(const shared_ptr<Darabonba::Model> &m);
  static map<string, boost::any> toMap(const shared_ptr<Darabonba::Model> &in);
  static void sleep(const shared_ptr<int> &millisecond);
  static vector<map<string, boost::any>>
  toArray(const shared_ptr<boost::any> &input);
  static Darabonba::Stream
  assertAsReadable(const shared_ptr<boost::any> &value);

  Client(){};
  ~Client(){};
};
} // namespace Darabonba_Util

#endif
