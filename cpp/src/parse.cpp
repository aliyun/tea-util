#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <darabonba/util.hpp>
#include <cpprest/streams.h>
#include <iostream>
#include <sstream>

std::vector<uint8_t> Darabonba_Util::Client::toBytes(const std::string &val) {
  std::vector<uint8_t> vec(val.begin(), val.end());
  return vec;
}

string Darabonba_Util::Client::toString(std::vector<uint8_t> val) {
  std::string str(val.begin(), val.end());
  return str;
}

boost::any Darabonba_Util::Client::parseJSON(const std::string &val) {
  std::stringstream ss(val);
  using namespace boost::property_tree;
  ptree pt;
  read_json(ss, pt);
  std::map<string, boost::any> m;
  for (auto it : pt) {
    m[it.first] = boost::any(it.second);
  }
  return boost::any(m);
}

//string Darabonba_Util::Client::toJSONString(boost::any val) {
//  map<string, boost::any> m = boost::any_cast<map<string, boost::any>>(val);
//  boost::property_tree::ptree out;
//  for (const auto &entry : m) {
//    pt.put(entry.first, entry.second);
//    pt.put()
//  }
//  std::ostringstream buf;
//  write_json(buf, pt, false);
//  return buf.str();
//}

std::vector<uint8_t> Darabonba_Util::Client::readAsBytes(const concurrency::streams::istream &stream) {
  size_t count = stream.streambuf().size();
  std::vector<uint8_t> buffer;
  buffer.resize(count);
  stream.seek(0);
  stream.streambuf().getn(buffer.data(), count).get();
  return buffer;
}

string Darabonba_Util::Client::readAsString(const concurrency::streams::istream &stream) {
  std::vector<uint8_t> bytes = readAsBytes(stream);
  string str(toString(bytes));
  return str;
}

boost::any Darabonba_Util::Client::readAsJSON(const concurrency::streams::istream &stream) {
  string json = readAsString(stream);
  return Client::parseJSON(json);
}

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
    escaped << '%' << std::setw(2) << int((unsigned char) c);
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

string Darabonba_Util::Client::toFormString(map<string, boost::any> val) {
  if (val.empty()) {
    return "";
  }
  vector<string> tmp;
  for (const auto &it : val) {
    string v = boost::any_cast<string>(val);
    v = url_encode(v);
    string str;
    str.append(it.first).append("=").append(v);
  }
  return implode(tmp, "&");
}

map<string, boost::any>
Darabonba_Util::Client::anyifyMapValue(const map<string, string> &m) {
  map<string, boost::any> data;
  if (m.empty()) {
    return data;
  }
  for (const auto &it : m) {
    data[it.first] = boost::any(it.second);
  }
  return data;
}

vector<map<string, boost::any>>
Darabonba_Util::Client::toArray(boost::any input) {
  map<string, boost::any> m = boost::any_cast<map<string, boost::any>>(input);
  vector<map<string, boost::any>> v;
  v.push_back(m);
  return v;
}