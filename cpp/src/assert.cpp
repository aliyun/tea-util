#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <darabonba/util.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <cpprest/streams.h>

using namespace std;
using namespace boost;

bool Darabonba_Util::Client::empty(string *val) {
  if (nullptr == val) {
    return true;
  }
  return val->empty();
}

bool Darabonba_Util::Client::equalString(string *val1, string *val2) {
  string s1 = nullptr == val1 ? "" : *val1;
  string s2 = nullptr == val2 ? "" : *val2;
  return s1 == s2;
}

bool Darabonba_Util::Client::equalNumber(int *val1, int *val2) {
  int i1 = nullptr == val1 ? 0 : *val1;
  int i2 = nullptr == val2 ? 0 : *val2;
  return i1 == i2;
}

bool Darabonba_Util::Client::isUnset(void *value) { return value == nullptr; }

map<string, string> Darabonba_Util::Client::stringifyMapValue(map<string, any> *m) {
  map<string, string> data;
  if (m == nullptr) {
    return data;
  }
  if (m->empty()) {
    return data;
  }
  for (const auto &it : *m) {
    if (typeid(int) == it.second.type()) {
      data[it.first] = to_string(any_cast<int>(it.second));
    } else if (typeid(long) == it.second.type()) {
      data[it.first] = to_string(any_cast<long>(it.second));
    } else if (typeid(double) == it.second.type()) {
      data[it.first] = to_string(any_cast<double>(it.second));
    } else if (typeid(float) == it.second.type()) {
      data[it.first] = to_string(any_cast<float>(it.second));
    } else if (typeid(bool) == it.second.type()) {
      string v = any_cast<bool>(it.second) ? "true" : "false";
      data[it.first] = v;
    } else if (typeid(string) == it.second.type()) {
      string v = any_cast<string>(it.second);
      data[it.first] = v;
    }
  }
  return data;
}

bool Darabonba_Util::Client::assertAsBoolean(any *value) {
  if (typeid(bool) != value->type()) {
    BOOST_THROW_EXCEPTION(
        enable_error_info(runtime_error("value is not a bool")));
  }
  return any_cast<bool>(value);
}

string Darabonba_Util::Client::assertAsString(any *value) {
  if (typeid(string) != value->type()) {
    BOOST_THROW_EXCEPTION(
        enable_error_info(runtime_error("value is not a string")));
  }
  return any_cast<string>(*value);
}

vector<uint8_t> Darabonba_Util::Client::assertAsBytes(any *value) {
  if (typeid(vector<uint8_t>) != value->type()) {
    BOOST_THROW_EXCEPTION(
        enable_error_info(runtime_error("value is not a bytes")));
  }
  return any_cast<vector<uint8_t>>(*value);
}

int Darabonba_Util::Client::assertAsNumber(any *value) {
  if (typeid(int) != value->type()) {
    BOOST_THROW_EXCEPTION(
        enable_error_info(runtime_error("value is not a int number")));
  }
  return any_cast<int>(*value);
}

map<string, any> Darabonba_Util::Client::assertAsMap(any *value) {
  if (typeid(map<string, any>) != value->type()) {
    BOOST_THROW_EXCEPTION(enable_error_info(
        runtime_error("value is not a map<string, any>")));
  }
  return any_cast<map<string, any>>(*value);
}

bool Darabonba_Util::Client::is2xx(int *code) {
  return nullptr != code && Darabonba_Util::Client::is5xx(*code);
}

bool Darabonba_Util::Client::is2xx(int code) {
  return code >= 200 && code < 300;
}

bool Darabonba_Util::Client::is3xx(int *code) {
  return nullptr != code && Darabonba_Util::Client::is5xx(*code);
}

bool Darabonba_Util::Client::is3xx(int code) {
  return code >= 300 && code < 400;
}

bool Darabonba_Util::Client::is4xx(int *code) {
  return nullptr != code && Darabonba_Util::Client::is5xx(*code);
}

bool Darabonba_Util::Client::is4xx(int code) {
  return code >= 400 && code < 500;
}

bool Darabonba_Util::Client::is5xx(int *code) {
  return nullptr != code && Darabonba_Util::Client::is5xx(*code);
}

bool Darabonba_Util::Client::is5xx(int code) {
  return code >= 500 && code < 600;
}

concurrency::streams::istream Darabonba_Util::Client::assertAsReadable(any *value) {
  if (typeid(concurrency::streams::istream) != value->type()) {
    BOOST_THROW_EXCEPTION(
        enable_error_info(runtime_error("value is not a concurrency::streams::istream")));
  }
  concurrency::streams::istream f = any_cast<concurrency::streams::istream>(*value);
  return f;
}