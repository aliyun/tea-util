#include <boost/lexical_cast.hpp>
#include <darabonba/util.hpp>

using namespace std;

string Darabonba_Util::Client::defaultString(void *real, string default_) {
  if (real == nullptr) {
    return default_;
  }
  return boost::lexical_cast<string>(real);
}

int Darabonba_Util::Client::defaultNumber(void *real, int default_) {
  if (real == nullptr) {
    return default_;
  }
  return boost::lexical_cast<int>(real);
}