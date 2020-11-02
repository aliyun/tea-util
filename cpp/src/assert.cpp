#include <boost/lexical_cast.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/throw_exception.hpp>
#include <cpprest/streams.h>
#include <darabonba/util.hpp>

using namespace std;

bool Darabonba_Util::Client::empty(const shared_ptr<string> &val) {
  return !val || val->empty();
}

bool Darabonba_Util::Client::equalString(const shared_ptr<string> &val1,
                                         const shared_ptr<string> &val2) {
  if (!val1 && !val2) {
    return true;
  }
  if (!val1 || !val2) {
    return false;
  }
  return *val1 == *val2;
}

bool Darabonba_Util::Client::equalNumber(const shared_ptr<int> &val1,
                                         const shared_ptr<int> &val2) {
  if (!val1 && !val2) {
    return true;
  }
  if (!val1 ^ !val2) {
    return false;
  }
  return val1 == val2;
}

bool Darabonba_Util::Client::isUnset(const shared_ptr<void> &value) {
  return !value;
}

bool Darabonba_Util::Client::assertAsBoolean(const boost::any &value) {
  if (typeid(shared_ptr<bool>) != value.type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a bool")));
  }
  shared_ptr<bool> val = boost::any_cast<shared_ptr<bool>>(value);
  return *val;
}

string Darabonba_Util::Client::assertAsString(const boost::any &value) {
  if (typeid(shared_ptr<string>) != value.type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a string")));
  }
  shared_ptr<string> val = boost::any_cast<shared_ptr<string>>(value);
  ;
  return *val;
}

vector<uint8_t> Darabonba_Util::Client::assertAsBytes(const boost::any &value) {
  if (typeid(shared_ptr<vector<uint8_t>>) != value.type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a bytes")));
  }
  shared_ptr<vector<uint8_t>> val =
      boost::any_cast<shared_ptr<vector<uint8_t>>>(value);
  return *val;
}

int Darabonba_Util::Client::assertAsNumber(const boost::any &value) {
  if (typeid(shared_ptr<int>) != value.type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a int number")));
  }
  shared_ptr<int> val = boost::any_cast<shared_ptr<int>>(value);
  return *val;
}

map<string, boost::any>
Darabonba_Util::Client::assertAsMap(const boost::any &value) {
  if (typeid(shared_ptr<map<string, boost::any>>) != value.type()) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a map<string, any>")));
  }
  shared_ptr<map<string, boost::any>> val =
      boost::any_cast<shared_ptr<map<string, boost::any>>>(value);
  return *val;
}

Darabonba::Stream
Darabonba_Util::Client::assertAsReadable(const boost::any &value) {
  if (typeid(shared_ptr<Darabonba::Stream>) != value.type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a readable")));
  }
  shared_ptr<Darabonba::Stream> val =
      boost::any_cast<shared_ptr<Darabonba::Stream>>(value);
  return *val;
}

bool Darabonba_Util::Client::is2xx(const shared_ptr<int> &code) {
  return code && *code >= 200 && *code < 300;
}

bool Darabonba_Util::Client::is3xx(const shared_ptr<int> &code) {
  return code && *code >= 300 && *code < 400;
}

bool Darabonba_Util::Client::is4xx(const shared_ptr<int> &code) {
  return code && *code >= 400 && *code < 500;
}

bool Darabonba_Util::Client::is5xx(const shared_ptr<int> &code) {
  return code && *code >= 500 && *code < 600;
}
