#include "iocpp.h"
#include <iostream>
#include <type_traits>

using namespace std;
using namespace iocpp;

class A {
public:
  virtual void Test() = 0;
};

class B : public A {
public:
  void Test() { cout << "test" << endl; }
};

int main(int argc, char **argv) {
  cout << "Hello" << endl
       << Iocpp::Instance() << endl
       << std::is_abstract<A>::value << endl
       << std::is_abstract<B>::value << endl;
  Iocpp::Instance()->Register<A, B>();
  return 0;
}