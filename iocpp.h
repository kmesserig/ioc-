#ifndef IOCPP_H
#define IOCPP_H

#include <iostream>
#include <map>
#include <memory>
#include <type_traits>

namespace iocpp {
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
              << typeid(TImplementation).name() << endl;
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