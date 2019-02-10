#ifndef IOCPP_H
#define IOCPP_H

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>


namespace iocpp {
class IocppException {
private:
  std::string message;

public:
  IocppException(std::string pMessage) : message(pMessage) {}
  std::string GetMessage() { return this->message; }
};

class IocppRegistrationException : public IocppException {
public:
  IocppRegistrationException(std::string pMessage) : IocppException(pMessage) {}
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
    if (!std::is_base_of<TInterface, TImplementation>::value) {
      std::stringstream msgStream;
      msgStream << typeid(TImplementation).name() << " is not a base class of "
                << typeid(TInterface).name();
      throw IocppRegistrationException(msgStream.str());
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