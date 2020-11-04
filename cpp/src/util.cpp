#include <boost/any.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <ctime>
#include <darabonba/core.hpp>
#include <darabonba/util.hpp>
#include <iostream>
#include <map>

using namespace std;

string Darabonba_Util::Client::getNonce() {
  boost::uuids::uuid uid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uid);
}

string Darabonba_Util::Client::getDateUTCString() {
  char buf[80];
  time_t t = time(nullptr);
  std::strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&t));
  return buf;
}

std::string os_name() {
#ifdef _WIN32
  return "Windows32";
#elif _WIN64
  return "Windows64";
#elif __APPLE__ || __MACH__
  return "MacOS";
#elif __linux__
  return "Linux";
#elif __FreeBSD__
  return "FreeBSD";
#elif __unix || __unix__
  return "Unix";
#else
  return "Other";
#endif
}

string
Darabonba_Util::Client::getUserAgent(const shared_ptr<string> &userAgent) {
  string ua = !userAgent ? "" : *userAgent;
  string _default_user_agent("AlibabaCloud OS/" + os_name() + " DaraDSL/1");
  if (ua.empty()) {
    return _default_user_agent;
  }
  ua = _default_user_agent + ua;
  return ua;
}

void Darabonba_Util::Client::validateModel(
    const shared_ptr<Darabonba::Model> &m) {
  m->validate();
}

map<string, boost::any>
Darabonba_Util::Client::toMap(const shared_ptr<Darabonba::Model> &in) {
  if (!in) {
    return map<string, boost::any>();
  }
  return in->toMap();
}

void Darabonba_Util::Client::sleep(const shared_ptr<int> &millisecond) {
  int m = !millisecond ? 0 : *millisecond;
  boost::this_thread::sleep_for(boost::chrono::milliseconds(m));
}
