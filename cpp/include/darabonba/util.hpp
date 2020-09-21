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
  explicit RuntimeOptions(const std::map<string, boost::any> &config)
      : Model(config) {
    _init();
  };

  map<string, boost::any> toMap() {
    map<string, boost::any> res;
    if (nullptr != autoretry) {
      res["autoretry"] = boost::any(*autoretry);
    }
    if (nullptr != ignoreSSL) {
      res["ignoreSSL"] = boost::any(*ignoreSSL);
    }
    if (nullptr != maxAttempts) {
      res["max_attempts"] = boost::any(*maxAttempts);
    }
    if (nullptr != backoffPolicy) {
      res["backoff_policy"] = boost::any(*backoffPolicy);
    }
    if (nullptr != backoffPeriod) {
      res["backoff_period"] = boost::any(*backoffPeriod);
    }
    if (nullptr != readTimeout) {
      res["readTimeout"] = boost::any(*readTimeout);
    }
    if (nullptr != connectTimeout) {
      res["connectTimeout"] = boost::any(*connectTimeout);
    }
    if (nullptr != httpProxy) {
      res["httpProxy"] = boost::any(*httpProxy);
    }
    if (nullptr != httpsProxy) {
      res["httpsProxy"] = boost::any(*httpsProxy);
    }
    if (nullptr != noProxy) {
      res["noProxy"] = boost::any(*noProxy);
    }
    if (nullptr != maxIdleConns) {
      res["maxIdleConns"] = boost::any(*maxIdleConns);
    }
    if (nullptr != localAddr) {
      res["localAddr"] = boost::any(*localAddr);
    }
    if (nullptr != socks5Proxy) {
      res["socks5Proxy"] = boost::any(*socks5Proxy);
    }
    if (nullptr != socks5NetWork) {
      res["socks5NetWork"] = boost::any(*socks5NetWork);
    }
    return res;
  }

  bool *autoretry{};
  bool *ignoreSSL{};
  int *maxAttempts{};
  string *backoffPolicy{};
  int *backoffPeriod{};
  int *readTimeout{};
  int *connectTimeout{};
  string *httpProxy{};
  string *httpsProxy{};
  string *noProxy{};
  int *maxIdleConns{};
  string *localAddr{};
  string *socks5Proxy{};
  string *socks5NetWork{};

  ~RuntimeOptions() {
    delete autoretry;
    delete ignoreSSL;
    delete maxAttempts;
    delete backoffPolicy;
    delete backoffPeriod;
    delete readTimeout;
    delete connectTimeout;
    delete httpProxy;
    delete httpsProxy;
    delete noProxy;
    delete maxIdleConns;
    delete localAddr;
    delete socks5Proxy;
    delete socks5NetWork;
  };
};
class Client {
public:
  static vector<uint8_t> toBytes(string *val);
  static string toString(vector<uint8_t> *val);
  static boost::any parseJSON(string *val);
  static vector<uint8_t> readAsBytes(concurrency::streams::istream *stream);
  static string readAsString(concurrency::streams::istream *stream);
  static boost::any readAsJSON(concurrency::streams::istream *stream);
  static string getNonce();
  static string getDateUTCString();
  static string defaultString(string *real, string *default_);
  static int defaultNumber(int *real, int *default_);
  static string toFormString(map<string, boost::any> *val);
  static string toJSONString(boost::any *val);
  static bool empty(string *val);
  static bool equalString(string *val1, string *val2);
  static bool equalNumber(int *val1, int *val2);
  static bool isUnset(void *value);
  static map<string, string> stringifyMapValue(map<string, boost::any> *m);
  static map<string, boost::any> anyifyMapValue(map<string, string> *m);
  static bool assertAsBoolean(boost::any *value);
  static string assertAsString(boost::any *value);
  static vector<uint8_t> assertAsBytes(boost::any *value);
  static int assertAsNumber(boost::any *value);
  static map<string, boost::any> assertAsMap(boost::any *value);
  static string getUserAgent(string *userAgent);
  static bool is2xx(int *code);
  static bool is3xx(int *code);
  static bool is4xx(int *code);
  static bool is5xx(int *code);
  static void validateModel(Darabonba::Model *m);
  static map<string, boost::any> toMap(Darabonba::Model *in);
  static void sleep(int *millisecond);
  static vector<map<string, boost::any>> toArray(boost::any *input);
  static concurrency::streams::istream assertAsReadable(boost::any *value);

  Client(){};
  ~Client(){};
};
} // namespace Darabonba_Util

#endif
