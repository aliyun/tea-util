#include <boost/lexical_cast.hpp>
#include <darabonba/util.hpp>

using namespace std;

string Darabonba_Util::Client::defaultString(string *real, string *default_) {
  if (real == nullptr) {
    if (nullptr == default_) {
      return string("");
    }
    return *default_;
  }
  return *real;
}

int Darabonba_Util::Client::defaultNumber(int *real, int *default_) {
  if (real == nullptr) {
    if (nullptr == default_) {
      return 0;
    }
    return *default_;
  }
  return *real;
}

int Darabonba_Util::Client::defaultNumber(int *real, long *default_) {
  if (real == nullptr) {
    if (nullptr == default_) {
      return 0;
    }
    return boost::lexical_cast<int>(*default_);
  }
  return *real;
}