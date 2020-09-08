#include "gtest/gtest.h"
#include <darabonba/util.hpp>

using namespace Darabonba_Util;

TEST(util_test, getNonce)
{
  ASSERT_EQ(36, Client::getNonce().size());
}

TEST(util_test, getDateUTCString)
{
  ASSERT_EQ(29, Client::getDateUTCString().size());
}
