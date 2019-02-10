#ifndef IOCPP_H
#define IOCPP_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>


namespace iocpp {
class IocppException {
public:
  std::string message;
};

class Iocpp {
public:
  static Iocpp *Instance() {
    static MemGuard memGuard;

    if (!pInstance) {
      pInstance = new Iocpp();
    }
    return pInstance;
  }

  template <class TInterface, class TImplementation> void Register() {
    std::cout << typeid(TInterface).name() << std::endl
              << typeid(TImplementation).name() << endl
              << std::is_base_of<TInterface, TImplementation>::value << endl;

    if (!std::is_base_of<TInterface, TImplementation>::value) {
    }
  }

private:
  static Iocpp *pInstance;
  Iocpp(){};
  Iocpp(const Iocpp &iocpp){};
  ~Iocpp(){};

  class MemGuard {
  public:
    ~MemGuard() {
      if (NULL != Iocpp::pInstance) {
        delete Iocpp::pInstance;
        Iocpp::pInstance = NULL;
      }
    }
  };
};
Iocpp *Iocpp::pInstance = NULL;
} // namespace iocpp

#endif