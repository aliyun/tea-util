#include <ctime>
#include <darabonba/core.hpp>
#include <darabonba/util.hpp>
#include <iostream>
#include <map>

using namespace std;

string Darabonba::Util::getNonce() {
  return Darabonba::Core::uuid();
}

string Darabonba::Util::getDateUTCString() {
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

string Darabonba::Util::getUserAgent(const string &userAgent) {
  string _default_user_agent("AlibabaCloud OS/" + os_name() + " DaraDSL/1");
  if (userAgent.empty()) {
    return _default_user_agent;
  }
  return _default_user_agent + userAgent;
}

void Darabonba::Util::validateModel(
    const shared_ptr<Darabonba::Model> &m) {
    m->validate(toMap(m));
}

json Darabonba::Util::toMap(const shared_ptr<Darabonba::Model> &in) {
  if (!in) {
    return json();
  }
  return in->toMap();
}

void Darabonba::Util::sleep(const int &millisecond) {
  Darabonba::Core::sleep(millisecond);
}
