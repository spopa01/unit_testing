#ifndef __UNIT_TESTING_FRAMEWORK__
#define __UNIT_TESTING_FRAMEWORK__

#include <iostream>
#include <sstream>
#include <exception>
#include <memory>

#define S_(e) #e
#define S(e)  S_(e)

struct errmsg{
  std::shared_ptr<std::stringstream> msg;
  errmsg() : msg(new std::stringstream){}
  template <class T> errmsg& operator<<(T value){ (*msg) << value; return *this; }
  std::string str() { return msg->str(); }
};

#define TEST_WHERE  __FILE__ "(" S(__LINE__) "): "

#define VERIFY(expression) {                                                                                \
  auto e = (expression);                                                                                    \
  if (!e){                                                                                                  \
    throw std::logic_error( (errmsg() << TEST_WHERE << "!(" << e << ") in VERIFY("#expression")").str() );  \
  }                                                                                                         \
}

#define VERIFY_EQ(expected, actual) {                                                                                               \
  auto e = (expected);                                                                                                              \
  auto a = (actual);                                                                                                                \
  if (e != a){                                                                                                                      \
    throw std::logic_error( (errmsg() << TEST_WHERE << "(" << e << ")!=(" << a << ") in VERIFY_EQ("#expected","#actual")").str() ); \
  }                                                                                                                                 \
}

struct empty_testcase{ void run(){} const char* name(){return 0;} };
template <size_t offset> struct testcase : empty_testcase{};

template <size_t begin, size_t end> struct testrange {
  void run(size_t& pass, size_t& fail) {
    {
      testcase<begin> a_case;
      if (a_case.name()) {
        size_t p=0, f=0;
        std::cout << "TEST: " << a_case.name() << std::endl;
        try {
          a_case.run();
          std::cout << std::endl;
          ++p;
        } catch (std::logic_error& e) {
          std::cerr << "ERRORS:" << std::endl;
          std::cerr << "  " << e.what() << std::endl;
          std::cerr << std::endl;
          ++f;
        }
        pass += p; fail += f;
      }
    }

    const size_t rem = (end-begin-1);
    testrange<begin+1, begin+1+rem/2>().run(pass, fail);
    testrange<begin+1+rem/2, end>().run(pass, fail);
  }
};
template <size_t begin> struct testrange<begin,begin> { void run(size_t& pass, size_t& fail) {}; };

#define BEGIN_TEST(test_name)                   \
void test_name ();                              \
template <>                                     \
struct testcase<__LINE__> {                     \
  const char* name() { return(S(test_name)); }  \
  void run() { test_name(); }                   \
};                                              \
void test_name() {

#define END_TEST }

#define RUN_UNIT_TESTING_FRAMEWORK() {                                                        \
  size_t pass=0, fail=0;                                                                      \
  std::cout << std::endl << "BEGIN " << std::endl << std::endl;                               \
  testrange<0,__LINE__>().run(pass, fail);                                                    \
  std::cout << "END" << std::endl << std::endl;                                               \
  std::cout << "STATISTICS - Pass: " << pass << ", Fail: " << fail << std::endl << std::endl; \
}

#endif//__UNIT_TESTING_FRAMEWORK__
