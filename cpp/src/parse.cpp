#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cpprest/streams.h>
#include <darabonba/util.hpp>
#include <json/json.h>
#include <sstream>
#include <string>

string url_encode(const std::string &str) {
  std::ostringstream escaped;
  escaped.fill('0');
  escaped << hex;

  for (char c : str) {
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      escaped << c;
      continue;
    }
    escaped << std::uppercase;
    escaped << '%' << std::setw(2) << int((unsigned char)c);
    escaped << nouppercase;
  }

  return escaped.str();
}

std::string implode(const std::vector<std::string> &vec,
                    const std::string &glue) {
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

std::vector<uint8_t> Darabonba_Util::Client::toBytes(std::string *val) {
  std::string v = nullptr == val ? "" : *val;
  std::vector<uint8_t> vec(v.begin(), v.end());
  return vec;
}

string Darabonba_Util::Client::toString(std::vector<uint8_t> *val) {
  std::vector<uint8_t> v = nullptr == val ? std::vector<uint8_t>() : *val;
  std::string str(v.begin(), v.end());
  return str;
}

boost::any parse_json(boost::property_tree::ptree pt) {
  if (pt.empty()) {
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

boost::any Darabonba_Util::Client::parseJSON(std::string *val) {
  string v = nullptr == val ? "" : *val;
  std::stringstream ss(v);
  using namespace boost::property_tree;
  ptree pt;
  read_json(ss, pt);
  return parse_json(pt);
}

template <typename T> bool can_cast(const boost::any &v) {
  return typeid(T) == v.type();
}

void json_encode(boost::any val, std::stringstream &ss) {
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
    ss << std::to_string(i);
  } else if (can_cast<long>(val)) {
    long l = boost::any_cast<long>(val);
    ss << std::to_string(l);
  } else if (can_cast<double>(val)) {
    auto d = boost::any_cast<double>(val);
    ss << std::to_string(d);
  } else if (can_cast<float>(val)) {
    auto f = boost::any_cast<float>(val);
    ss << std::to_string(f);
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

std::string Darabonba_Util::Client::toJSONString(boost::any *val) {
  if (nullptr == val) {
    return string("{}");
  }
  map<string, boost::any> a = boost::any_cast<map<string, boost::any>>(*val);
  std::stringstream s;
  json_encode(a, s);
  return s.str();
}

std::vector<uint8_t>
Darabonba_Util::Client::readAsBytes(concurrency::streams::istream *stream) {
  if (nullptr == stream) {
    return std::vector<uint8_t>();
  }
  size_t count = stream->streambuf().size();
  std::vector<uint8_t> buffer;
  buffer.resize(count);
  stream->seek(0);
  stream->streambuf().getn(buffer.data(), count).get();
  return buffer;
}

string
Darabonba_Util::Client::readAsString(concurrency::streams::istream *stream) {
  if (nullptr == stream) {
    return string("");
  }
  std::vector<uint8_t> bytes = readAsBytes(stream);
  string str(toString(&bytes));
  return str;
}

boost::any
Darabonba_Util::Client::readAsJSON(concurrency::streams::istream *stream) {
  string json = readAsString(stream);
  return Client::parseJSON(&json);
}

string Darabonba_Util::Client::toFormString(map<string, boost::any> *val) {
  if (nullptr == val || val->empty()) {
    return string("");
  }
  vector<string> tmp;
  for (const auto &it : *val) {
    string v = boost::any_cast<string>(val);
    v = url_encode(v);
    string str;
    str.append(it.first).append("=").append(v);
  }
  return implode(tmp, "&");
}

map<string, boost::any>
Darabonba_Util::Client::anyifyMapValue(map<string, string> *m) {
  if (nullptr == m) {
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
Darabonba_Util::Client::toArray(boost::any *input) {
  if (nullptr == input) {
    return vector<map<string, boost::any>>();
  }
  map<string, boost::any> m = boost::any_cast<map<string, boost::any>>(*input);
  vector<map<string, boost::any>> v;
  v.push_back(m);
  return v;
}