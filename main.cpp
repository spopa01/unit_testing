#include "unit_testing.hpp"

BEGIN_TEST(dummy1)
  VERIFY(true)
END_TEST

BEGIN_TEST(dummy2)
  VERIFY(false)
END_TEST

BEGIN_TEST(dummy3)
  VERIFY_EQ(1, 1)
END_TEST

BEGIN_TEST(dummy4)
  VERIFY_EQ(0, 1)
END_TEST

int main(){
  RUN_UNIT_TESTING_FRAMEWORK()
  return 0;
}
