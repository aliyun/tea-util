#include "gtest/gtest.h"
#include <darabonba/util.hpp>

using namespace std;
using namespace Darabonba_Util;

TEST(assert, test_getDateUTCString) {
  ASSERT_EQ(29, Client::getDateUTCString().size());
}