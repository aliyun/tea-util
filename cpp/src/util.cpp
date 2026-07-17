#include <boost/any.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstdio>
#include <ctime>
#include <darabonba/core.hpp>
#include <darabonba/util.hpp>
#include <iostream>
#include <map>
#include <unistd.h>

using namespace std;

string Darabonba_Util::Client::getNonce() {
  boost::uuids::uuid uid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uid);
}

string Darabonba_Util::Client::getDateUTCString() {
  // English weekday/month names — std::strftime %a/%b follow LC_TIME and break RFC1123.
  static const char *kWeekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  static const char *kMonths[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char buf[80];
  time_t t = time(nullptr);
  struct tm *gmt = gmtime(&t);
  std::snprintf(buf, sizeof buf, "%s, %02d %s %04d %02d:%02d:%02d GMT",
                kWeekdays[gmt->tm_wday], gmt->tm_mday, kMonths[gmt->tm_mon],
                gmt->tm_year + 1900, gmt->tm_hour, gmt->tm_min, gmt->tm_sec);
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

string Darabonba_Util::Client::getHostName() {
  char hostname[256];
  if (gethostname(hostname, sizeof(hostname)) == 0) {
    return string(hostname);
  }
  return "";
}
