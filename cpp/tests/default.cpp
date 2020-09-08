#include "gtest/gtest.h"
#include <darabonba/util.hpp>

using namespace Darabonba_Util;

TEST(default_test, defaultString)
{
  string defaultStr = "default";
  string str = Client::defaultString(nullptr, defaultStr);
  ASSERT_EQ(defaultStr, str);
  string reaStr = "real";
  ASSERT_EQ(reaStr ,Client::defaultString(&reaStr, defaultStr));
}

TEST(default_test, defaultNumber)
{
  int defaultNum = 1;
  ASSERT_EQ(defaultNum, Client::defaultNumber(nullptr, defaultNum));
  int reaNum = 1000;
  ASSERT_EQ(reaNum, Client::defaultNumber(&reaNum, defaultNum));
}
