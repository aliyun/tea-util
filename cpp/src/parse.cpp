#include <darabonba/util.hpp>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

string url_encode(const string &str) {
  ostringstream escaped;
  escaped.fill('0');
  escaped << hex;

  for (char c : str) {
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      escaped << c;
      continue;
    }
    escaped << uppercase;
    escaped << '%' << setw(2) << int((unsigned char)c);
    escaped << nouppercase;
  }

  return escaped.str();
}

vector<uint8_t> Darabonba::Util::toBytes(const string &val) {
  vector<uint8_t> vec(val.begin(), val.end());
  return vec;
}

string Darabonba::Util::toString(const vector<uint8_t> &val) {
  string str(val.begin(), val.end());
  return str;
}

json Darabonba::Util::parseJSON(const string &val) {
  return json::parse(val);
}

string Darabonba::Util::toJSONString(const json &value) {
  return value.dump();
}

vector<uint8_t> Darabonba::Util::readAsBytes(Darabonba::ResponseBody* respBody) {
  if (!respBody) {
    return vector<uint8_t>();
  }
  string str = readAsString(respBody);
  vector<uint8_t> buffer(str.begin(), str.end());
  return buffer;
}

string Darabonba::Util::readAsString(Darabonba::ResponseBody* respBody) {
  if (!respBody) {
    return string("");
  }
  string ret;
  while(respBody->read() > 0) {
    string tmp =  respBody->str();
    ret += tmp;
  };
  return ret;
}

json Darabonba::Util::readAsJSON(Darabonba::ResponseBody* respBody) {
  string json = readAsString(respBody);
  return Util::parseJSON(json);
}

string Darabonba::Util::toFormString(const json &val) {
  if (!val || val.empty() || val.is_null()) {
    return string("");
  }
  stringstream tmp;
  for (const auto &el : val.items()) {
    tmp << el.key() << " = " << url_encode(el.value().get<string>()) << "&";
  }
  string formstring = tmp.str();
  return formstring.substr(0, formstring.size() - 1);
}

json Darabonba::Util::anyifyMapValue(const map<string, string> &m) {
  if (m.empty()) {
    return json();
  }
  json data = m;
  return data;
}

map<string, string> Darabonba::Util::stringifyMapValue(const json &m) {
  if (m.empty() || m.is_null()) {
    return map<string, string>();
  }
  return m.get<map<string, string>>();
//  for (const auto &it : *m) {
//    if (typeid(int) == it.second.type()) {
//      data[it.first] = to_string(boost::any_cast<int>(it.second));
//    } else if (typeid(long) == it.second.type()) {
//      data[it.first] = to_string(boost::any_cast<long>(it.second));
//    } else if (typeid(double) == it.second.type()) {
//      data[it.first] = to_string(boost::any_cast<double>(it.second));
//    } else if (typeid(float) == it.second.type()) {
//      data[it.first] = to_string(boost::any_cast<float>(it.second));
//    } else if (typeid(bool) == it.second.type()) {
//      string v = boost::any_cast<bool>(it.second) ? "true" : "false";
//      data[it.first] = v;
//    } else if (typeid(string) == it.second.type()) {
//      string v = boost::any_cast<string>(it.second);
//      data[it.first] = v;
//    }
//  }
//  return data;
}
