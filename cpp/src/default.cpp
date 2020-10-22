#include <boost/lexical_cast.hpp>
#include <darabonba/util.hpp>

using namespace std;

string
Darabonba_Util::Client::defaultString(const shared_ptr<string> &real,
                                      const shared_ptr<string> &default_) {
  if (!real) {
    if (!default_) {
      return string("");
    }
    return *default_;
  }
  return *real;
}

int Darabonba_Util::Client::defaultNumber(const shared_ptr<int> &real,
                                          const shared_ptr<int> &default_) {
  if (!real) {
    if (!default_) {
      return 0;
    }
    return *default_;
  }
  return *real;
}
