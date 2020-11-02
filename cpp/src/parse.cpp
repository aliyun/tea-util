#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cpprest/http_client.h>
#include <cpprest/streams.h>
#include <darabonba/util.hpp>
#include <json/json.h>
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

string implode(const vector<string> &vec, const string &glue) {
  string res;
  int n = 0;
  for (const auto &str : vec) {
    if (n == 0) {
      res = str;
    } else {
      res += glue + str;
    }
    n++;
  }
  return res;
}

vector<uint8_t> Darabonba_Util::Client::toBytes(const shared_ptr<string> &val) {
  string v = !val ? "" : *val;
  vector<uint8_t> vec(v.begin(), v.end());
  return vec;
}

string
Darabonba_Util::Client::toString(const shared_ptr<vector<uint8_t>> &val) {
  vector<uint8_t> v = !val ? vector<uint8_t>() : *val;
  string str(v.begin(), v.end());
  return str;
}

boost::any parse_json(boost::property_tree::ptree pt) {
  if (pt.empty()) {
    if (pt.data() == "true" || pt.data() == "false") {
      return boost::any(pt.get_value<bool>());
    } else if (regex_search(pt.data(), regex("^-?\\d+$"))) {
      long ln = atol(pt.data().c_str());
      if (ln > 2147483647 || ln < -2147483648) {
        return boost::any(ln);
      } else {
        return boost::any(atoi(pt.data().c_str()));
      }
    } else if (regex_search(pt.data(), regex(R"(^-?\d+\.{1}\d+$)"))) {
      return boost::any(atof(pt.data().c_str()));
    }
    return boost::any(pt.data());
  }
  vector<boost::any> vec;
  map<string, boost::any> m;
  for (const auto &it : pt) {
    if (!it.first.empty()) {
      m[it.first] = parse_json(it.second);
    } else {
      vec.push_back(parse_json(it.second));
    }
  }
  return vec.empty() ? boost::any(m) : boost::any(vec);
}

boost::any Darabonba_Util::Client::parseJSON(const shared_ptr<string> &val) {
  string v = !val ? "" : *val;
  stringstream ss(v);
  using namespace boost::property_tree;
  ptree pt;
  read_json(ss, pt);
  return parse_json(pt);
}

template <typename T> bool can_cast(const boost::any &v) {
  return typeid(T) == v.type();
}

void json_encode(boost::any val, stringstream &ss) {
  if (can_cast<map<string, boost::any>>(val)) {
    map<string, boost::any> m = boost::any_cast<map<string, boost::any>>(val);
    ss << '{';
    if (!m.empty()) {
      int n = 0;
      for (const auto &it : m) {
        if (n != 0) {
          ss << ",";
        }
        ss << '"' << it.first << '"' << ':';
        json_encode(it.second, ss);
        n++;
      }
    }
    ss << '}';
  } else if (can_cast<vector<boost::any>>(val)) {
    vector<boost::any> v = boost::any_cast<vector<boost::any>>(val);
    ss << '[';
    if (!v.empty()) {
      int n = 0;
      for (const auto &it : v) {
        if (n != 0) {
          ss << ",";
        }
        json_encode(it, ss);
        n++;
      }
    }
    ss << ']';
  } else if (can_cast<int>(val)) {
    int i = boost::any_cast<int>(val);
    ss << to_string(i);
  } else if (can_cast<long>(val)) {
    long l = boost::any_cast<long>(val);
    ss << to_string(l);
  } else if (can_cast<double>(val)) {
    auto d = boost::any_cast<double>(val);
    ss << to_string(d);
  } else if (can_cast<float>(val)) {
    auto f = boost::any_cast<float>(val);
    ss << to_string(f);
  } else if (can_cast<string>(val)) {
    auto s = boost::any_cast<string>(val);
    ss << s;
  } else if (can_cast<bool>(val)) {
    auto b = boost::any_cast<bool>(val);
    string c = b ? "true" : "false";
    ss << c;
  } else if (can_cast<const char *>(val)) {
    auto s = boost::any_cast<const char *>(val);
    ss << '"' << s << '"';
  } else if (can_cast<char *>(val)) {
    auto s = boost::any_cast<char *>(val);
    ss << '"' << s << '"';
  }
}

string Darabonba_Util::Client::toJSONString(const shared_ptr<void> &val) {
  if (!val) {
    return string("{}");
  }
  string b = typeid(val).name();
  shared_ptr<boost::any> v = static_pointer_cast<boost::any>(val);
  map<string, boost::any> a = boost::any_cast<map<string, boost::any>>(*v);
  stringstream s;
  json_encode(a, s);
  return s.str();
}

vector<uint8_t> Darabonba_Util::Client::readAsBytes(
    const shared_ptr<Darabonba::Stream> &stream) {
  if (!stream) {
    return vector<uint8_t>();
  }
  string str = readAsString(stream);
  vector<uint8_t> buffer(str.begin(), str.end());
  return buffer;
}

string Darabonba_Util::Client::readAsString(
    const shared_ptr<Darabonba::Stream> &stream) {
  if (!stream) {
    return string("");
  }
  return stream->read();
  ;
}

boost::any Darabonba_Util::Client::readAsJSON(
    const shared_ptr<Darabonba::Stream> &stream) {
  string json = readAsString(stream);
  return Client::parseJSON(make_shared<string>(json));
}

string
Darabonba_Util::Client::toFormString(shared_ptr<map<string, boost::any>> val) {
  if (!val || val->empty()) {
    return string("");
  }
  vector<string> tmp;
  for (const auto &it : *val) {
    string v = boost::any_cast<string>(it.second);
    v = url_encode(v);
    string str;
    str.append(it.first).append("=").append(v);
    tmp.push_back(str);
  }
  return implode(tmp, "&");
}

map<string, boost::any> Darabonba_Util::Client::anyifyMapValue(
    const shared_ptr<map<string, string>> &m) {
  if (!m) {
    return map<string, boost::any>();
  }
  map<string, boost::any> data;
  if (m->empty()) {
    return data;
  }
  for (const auto &it : *m) {
    data[it.first] = boost::any(it.second);
  }
  return data;
}

vector<map<string, boost::any>>
Darabonba_Util::Client::toArray(const shared_ptr<void> &input) {
  if (!input) {
    return vector<map<string, boost::any>>();
  }
  shared_ptr<boost::any> a = static_pointer_cast<boost::any>(input);
  map<string, boost::any> m = boost::any_cast<map<string, boost::any>>(*a);
  vector<map<string, boost::any>> v;
  v.push_back(m);
  return v;
}