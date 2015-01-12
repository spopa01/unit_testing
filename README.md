unit_testing
============

A (far too basic) "unit testing" framework.

See https://github.com/Reactive-Extensions/RxCpp/blob/master/Ix/CPP/unittest/testbench.hpp for the license (of the original code) etc...

(Note: In the real world, do yourself a favour and use google's unit testing framework)

Usage:

```C++

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

```

Outut:
```
BEGIN 

TEST: dummy1

TEST: dummy2
ERRORS:
  main.cpp(8): !(0) in VERIFY(false)

TEST: dummy3

TEST: dummy4
ERRORS:
  main.cpp(16): (0)!=(1) in VERIFY_EQ(0,1)

END

STATISTICS - Pass: 2, Fail: 2
```
