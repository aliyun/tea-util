#include <boost/lexical_cast.hpp>
#include <darabonba/util.hpp>

using namespace std;

string Darabonba_Util::Client::defaultString(void *real, string default_) {
  if (real == nullptr) {
    return default_;
  }
  auto *str = static_cast<string *>(real);
  return *str;
}

int Darabonba_Util::Client::defaultNumber(void *real, int default_) {
  if (real == nullptr) {
    return default_;
  }
  auto *num = static_cast<int *>(real);
  return *num;
}
