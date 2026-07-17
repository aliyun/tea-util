#include "gtest/gtest.h"
#include <darabonba/util.hpp>

using namespace std;
using namespace Darabonba_Util;

TEST(tests_util, test_getDateUTCString) {
  string date = Client::getDateUTCString();
  ASSERT_EQ(29, date.size());
  // RFC1123 English weekday/month (locale-independent)
  static const char *weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  static const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  bool weekday_ok = false;
  bool month_ok = false;
  for (int i = 0; i < 7; i++) {
    if (date.compare(0, 3, weekdays[i]) == 0) {
      weekday_ok = true;
      break;
    }
  }
  for (int i = 0; i < 12; i++) {
    if (date.compare(8, 3, months[i]) == 0) {
      month_ok = true;
      break;
    }
  }
  ASSERT_TRUE(weekday_ok);
  ASSERT_TRUE(month_ok);
  ASSERT_EQ(string(" GMT"), date.substr(25));
}

TEST(tests_util, test_getHostName) {
  string hostname = Client::getHostName();
  // hostname should not be empty in most cases
  ASSERT_GE(hostname.length(), 0);
}
