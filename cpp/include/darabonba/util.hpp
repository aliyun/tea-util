// This file is auto-generated, don't edit it. Thanks.

#ifndef DARABONBA_UTIL_H_
#define DARABONBA_UTIL_H_

#include <boost/any.hpp>
#include <darabonba/core.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace Darabonba;
using namespace std;

namespace Darabonba_Util {
class RuntimeOptions : public Model {
public:
  explicit RuntimeOptions(const std::map<string, boost::any> &config) : Model(config) {};
  RuntimeOptions();
  ~RuntimeOptions();

  bool getAutoretry(){
    string name = "autoretry";
    bool prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<bool>(val);
    }
    return prop_val;
  }
  void setAutoretry(bool val){
    string name = "autoretry";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  bool getIgnoreSSL(){
    string name = "ignoreSSL";
    bool prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<bool>(val);
    }
    return prop_val;
  }
  void setIgnoreSSL(bool val){
    string name = "ignoreSSL";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getMaxAttempts(){
    string name = "maxAttempts";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setMaxAttempts(int val){
    string name = "maxAttempts";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getBackoffPolicy(){
    string name = "backoffPolicy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setBackoffPolicy(string val){
    string name = "backoffPolicy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getBackoffPeriod(){
    string name = "backoffPeriod";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setBackoffPeriod(int val){
    string name = "backoffPeriod";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getReadTimeout(){
    string name = "readTimeout";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setReadTimeout(int val){
    string name = "readTimeout";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getConnectTimeout(){
    string name = "connectTimeout";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setConnectTimeout(int val){
    string name = "connectTimeout";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getHttpProxy(){
    string name = "httpProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setHttpProxy(string val){
    string name = "httpProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getHttpsProxy(){
    string name = "httpsProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setHttpsProxy(string val){
    string name = "httpsProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getNoProxy(){
    string name = "noProxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setNoProxy(string val){
    string name = "noProxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  int getMaxIdleConns(){
    string name = "maxIdleConns";
    int prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<int>(val);
    }
    return prop_val;
  }
  void setMaxIdleConns(int val){
    string name = "maxIdleConns";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getLocalAddr(){
    string name = "localAddr";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setLocalAddr(string val){
    string name = "localAddr";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getSocks5Proxy(){
    string name = "socks5Proxy";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setSocks5Proxy(string val){
    string name = "socks5Proxy";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
  string getSocks5NetWork(){
    string name = "socks5NetWork";
    string prop_val;
    if (_properties.find(name) != _properties.end()) {
      boost::any val = _properties.at(name);
      prop_val = boost::any_cast<string>(val);
    }
    return prop_val;
  }
  void setSocks5NetWork(string val){
    string name = "socks5NetWork";
    boost::any prop_val(val);
    _properties.insert(pair<string, boost::any>(name, prop_val));
  }
};
class Client {
public:
  Client();
  ~Client();

  vector<int> toBytes(string val);
  string toString(vector<int> val);
  boost::any parseJSON(string val);
  vector<int> readAsBytes(ofstream stream);
  string readAsString(ofstream stream);
  boost::any readAsJSON(ofstream stream);
  string getNonce();
  string getDateUTCString();
  string defaultString(string real, string default);
  int defaultNumber(int real, int default);
  string toFormString(map<string, boost::any> val);
  string toJSONString(boost::any val);
  bool empty(string val);
  bool equalString(string val1, string val2);
  bool equalNumber(int val1, int val2);
  bool isUnset(boost::any value);
  map<string, string> stringifyMapValue(map<string, boost::any> m);
  map<string, boost::any> anyifyMapValue(map<string, string> m);
  bool assertAsBoolean(boost::any value);
  string assertAsString(boost::any value);
  vector<int> assertAsBytes(boost::any value);
  int assertAsNumber(boost::any value);
  map<string, boost::any> assertAsMap(boost::any value);
  string getUserAgent(string userAgent);
  bool is2xx(int code);
  bool is3xx(int code);
  bool is4xx(int code);
  bool is5xx(int code);
  void validateModel(Model m);
  map<string, boost::any> toMap(Model in);
  void sleep(int millisecond);
  vector<map<string, boost::any>> toArray(boost::any input);
  ofstream assertAsReadable(boost::any value);
};
} // namespace Darabonba_Util

#endif
