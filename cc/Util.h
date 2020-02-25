// import { Readable } from 'stream';
// import * as $tea from '@alicloud/tea-typescript';
// import * as kitx from 'kitx';
// import querystring from 'querystring';
// import { platform, arch } from 'os';
// const DEFAULT_USER_AGENT = `AlibabaCloud (${platform()}; ${arch()}) Node.js/${process.version} Core/1.0.1 TeaDSL/1`;
#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <unordered_map>
#include <sstream>
#include "Tea.h"

using namespace std;
using namespace Tea;

namespace Util {

class RuntimeOptions : Tea::Model {
public:
  bool autoretry;
  bool ignoreSSL;
  int maxAttempts;
  string backoffPolicy;
  int backoffPeriod;
  int readTimeout;
  int connectTimeout;
  string httpProxy;
  string httpsProxy;
  string noProxy;
  int maxIdleConns;
};

class Client {
public:
  static string toString(char * buff);
  static string getDateUTCString();

};

}

#endif
