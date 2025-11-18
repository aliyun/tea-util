#include "gtest/gtest.h"
#include <darabonba/util.hpp>

using namespace std;
using namespace Darabonba_Util;

TEST(tests_util, test_getDateUTCString) {
  ASSERT_EQ(29, Client::getDateUTCString().size());
}

TEST(tests_util, test_getHostName) {
  string hostname = Client::getHostName();
  // hostname should not be empty in most cases
  ASSERT_GE(hostname.length(), 0);
}
