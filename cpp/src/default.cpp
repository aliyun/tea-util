#include <darabonba/util.hpp>

using namespace std;

string Darabonba::Util::defaultString(const string &real,
                                      const string &default_) {
  if (real.empty()) {
    if (default_.empty()) {
      return string("");
    }
    return default_;
  }
  return real;
}

int64_t Darabonba::Util::defaultNumber(const int64_t &real,
                                          const int64_t &default_) {
  if (!real) {
    if (!default_) {
      return 0;
    }
    return default_;
  }
  return real;
}
