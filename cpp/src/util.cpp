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

using namespace Darabonba;
using namespace std;
using namespace boost;

string Darabonba_Util::Client::getNonce() {
  boost::uuids::uuid uid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uid);
}

string Darabonba_Util::Client::getDateUTCString() {
  auto now = std::chrono::system_clock::now();
  auto itt = std::chrono::system_clock::to_time_t(now);

  std::ostringstream ss;
  ss << std::put_time(gmtime(&itt), "%a, %d %b %Y %H:%M:%S GMT");
  return ss.str();
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

string Darabonba_Util::Client::getUserAgent(string userAgent) {
  string _default_user_agent("AlibabaCloud OS/" + os_name() + " DaraDSL/1");
  if (userAgent.empty()) {
    return _default_user_agent;
  }
  userAgent = _default_user_agent + userAgent;
  return userAgent;
}

void Darabonba_Util::Client::validateModel(Model m) { m.validate(); }

map<string, boost::any> Darabonba_Util::Client::toMap(Model in) {
  return in.toMap();
}

void Darabonba_Util::Client::sleep(int millisecond) {
  boost::this_thread::sleep_for(boost::chrono::milliseconds(millisecond));
}
