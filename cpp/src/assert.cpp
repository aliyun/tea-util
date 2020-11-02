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

map<string, string> Darabonba_Util::Client::stringifyMapValue(
    const shared_ptr<map<string, boost::any>> &m) {
  if (nullptr == m) {
    return map<string, string>();
  }

  map<string, string> data;
  if (m->empty()) {
    return data;
  }

  for (const auto &it : *m) {
    if (typeid(int) == it.second.type()) {
      data[it.first] = to_string(boost::any_cast<int>(it.second));
    } else if (typeid(long) == it.second.type()) {
      data[it.first] = to_string(boost::any_cast<long>(it.second));
    } else if (typeid(double) == it.second.type()) {
      data[it.first] = to_string(boost::any_cast<double>(it.second));
    } else if (typeid(float) == it.second.type()) {
      data[it.first] = to_string(boost::any_cast<float>(it.second));
    } else if (typeid(bool) == it.second.type()) {
      string v = boost::any_cast<bool>(it.second) ? "true" : "false";
      data[it.first] = v;
    } else if (typeid(string) == it.second.type()) {
      string v = boost::any_cast<string>(it.second);
      data[it.first] = v;
    }
  }
  return data;
}

bool Darabonba_Util::Client::assertAsBoolean(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(bool) != val->type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a bool")));
  }
  return boost::any_cast<bool>(*val);
}

string Darabonba_Util::Client::assertAsString(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(string) != val->type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a string")));
  }
  return boost::any_cast<string>(*val);
}

vector<uint8_t>
Darabonba_Util::Client::assertAsBytes(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(vector<uint8_t>) != val->type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a bytes")));
  }
  return boost::any_cast<vector<uint8_t>>(*val);
}

int Darabonba_Util::Client::assertAsNumber(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(int) != val->type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a int number")));
  }
  return boost::any_cast<int>(*val);
}

map<string, boost::any>
Darabonba_Util::Client::assertAsMap(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(map<string, boost::any>) != val->type()) {
    BOOST_THROW_EXCEPTION(boost::enable_error_info(
        runtime_error("value is not a map<string, any>")));
  }
  return boost::any_cast<map<string, boost::any>>(*val);
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

Darabonba::Stream
Darabonba_Util::Client::assertAsReadable(const shared_ptr<void> &value) {
  if (!value) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is nullptr")));
  }
  shared_ptr<boost::any> val = static_pointer_cast<boost::any>(value);
  if (typeid(Darabonba::Stream) != val->type()) {
    BOOST_THROW_EXCEPTION(
        boost::enable_error_info(runtime_error("value is not a readable")));
  }
  Darabonba::Stream f = boost::any_cast<Darabonba::Stream>(*val);
  return f;
}