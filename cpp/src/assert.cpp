#include <darabonba/util.hpp>

using namespace std;

bool Darabonba::Util::empty(const string &val) {
  return val.empty();
}

bool Darabonba::Util::equalString(const string &val1,
                                         const string &val2) {
  if (val1.empty() && val2.empty()) {
    return true;
  }
  return val1 == val2;
}

bool Darabonba::Util::equalNumber(const int64_t &val1,
                                         const int64_t &val2) {
  return val1 == val2;
}

bool Darabonba::Util::assertAsBoolean(const json &value) {
  if(!value.is_boolean()) {
    throw Darabonba::Error("value is not a bool");
  }
  return value.get<bool>();
}

string Darabonba::Util::assertAsString(const json &value) {
  if(!value.is_string()) {
    throw Darabonba::Error("value is not a string");
  }
  return value.get<string>();
}

vector<uint8_t> Darabonba::Util::assertAsBytes(const json &value) {
  if(!value.is_array()) {
    throw Darabonba::Error("value is not a bytes");
  }
  try {
    return value.get<vector<uint8_t>>();
  } catch (exception&) {
    throw Darabonba::Error("value is not a bytes");
  }


}

int64_t Darabonba::Util::assertAsNumber(const json &value) {
  if(!value.is_number()) {
    throw Darabonba::Error("value is not a bytes");
  }
  return value.get<int64_t>();
}

json Darabonba::Util::assertAsMap(const json &value) {
  if(!value.is_object()) {
    throw Darabonba::Error("value is not a object");
  }
  return value;
}

ostringstream* Darabonba::Util::assertAsReadable(void* value) {
  try {
    return static_cast<ostringstream*>(value);
  } catch (exception&) {
    throw Darabonba::Error("value is not a object");
  }
}

bool Darabonba::Util::is2xx(const int64_t &code) {
  return code >= 200 && code < 300;
}

bool Darabonba::Util::is3xx(const int64_t &code) {
  return code >= 300 && code < 400;
}

bool Darabonba::Util::is4xx(const int64_t &code) {
  return code >= 400 && code < 500;
}

bool Darabonba::Util::is5xx(const int64_t &code) {
  return code >= 500 && code < 600;
}
