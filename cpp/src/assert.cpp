#include "util.h"
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

template<class T> T assertAsValue(const boost::any &value) {
  if (typeid(shared_ptr<T>) == value.type()) {
    shared_ptr<T> ptr = cast_any<T>(value);
    if (ptr) {
      return *ptr;
    }
  } else if (typeid(shared_ptr<boost::any>) == value.type()) {
    shared_ptr<boost::any> any_ptr = cast_any<boost::any>(value);
    if (any_ptr && !any_ptr->empty()) {
      if (typeid(shared_ptr<T>) == any_ptr->type()) {
        shared_ptr<T> ptr = cast_any<T>(*any_ptr);
        if (ptr) {
          return *ptr;
        }
      } else if (typeid(T) == any_ptr->type()) {
        return boost::any_cast<T>(*any_ptr);
      }
    }
  }
  throw exception();
}

bool Darabonba_Util::Client::assertAsBoolean(const boost::any &value) {
  try {
    return assertAsValue<bool>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a bool")));
  }
}

string Darabonba_Util::Client::assertAsString(const boost::any &value) {
  try {
    return assertAsValue<string>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a string")));
  }
}

vector<uint8_t> Darabonba_Util::Client::assertAsBytes(const boost::any &value) {
  try {
    return assertAsValue<vector<uint8_t>>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a bytes")));
  }
}

int Darabonba_Util::Client::assertAsNumber(const boost::any &value) {
  try {
    return assertAsValue<int>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a int number")));
  }
}

int Darabonba_Util::Client::assertAsInteger(const boost::any &value) {
  try {
    return assertAsValue<int>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a int number")));
  }
}

map<string, boost::any>
Darabonba_Util::Client::assertAsMap(const boost::any &value) {
  try {
    return assertAsValue<map<string, boost::any>>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a map<string, any>")));
  }
}

Darabonba::Stream
Darabonba_Util::Client::assertAsReadable(const boost::any &value) {
  try {
    return assertAsValue<Darabonba::Stream>(value);
  } catch (exception&) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a readable")));
  }
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
