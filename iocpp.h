#ifndef IOCPP_H
#define IOCPP_H

#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <type_traits>

namespace iocpp {
typedef enum IOCPP_LIFE_STYLE {
  SINGLETON = 0x1,
  TRANSIENT = 0x2
} IocppLifeStyle;

class IocppException {
private:
  std::string message;

public:
  IocppException(std::string pMessage) : message(pMessage) {}
  std::string GetMessage() { return message; }
};

class IocppRegistrationException : public IocppException {
public:
  IocppRegistrationException(std::string pMessage) : IocppException(pMessage) {}
};


class IocppRegistration {
public:

private:
  std::shared_ptr<void> m_instance;
};

class Iocpp {
private:
  static Iocpp *m_instance;
  std::mutex m_mapMutex;
  std::map<std::string, IocppRegistration> m_registrations;
  Iocpp() { m_registrations = std::map<std::string, IocppRegistration>(); };
  Iocpp(const Iocpp &iocpp){};
  ~Iocpp(){};
  class MemGuard {
  public:
    ~MemGuard() {
      if (NULL != Iocpp::m_instance) {
        delete Iocpp::m_instance;
        Iocpp::m_instance = NULL;
      }
    }
  };

public:
  static Iocpp *Instance() {
    static MemGuard mem_guard;

    if (!m_instance) {
      m_instance = new Iocpp();
    }
    return m_instance;
  }

  template <class TInterface, class TImplementation> void Register() {
    Register<TInterface, TImplementation>(IocppLifeStyle::SINGLETON);
  }

  template <class TInterface, class TImplementation>
  void Register(IocppLifeStyle pLifeStyle) {
    std::lock_guard<std::mutex> lock(m_mapMutex);

    if (!std::is_base_of<TInterface, TImplementation>::value) {
      std::stringstream msgStream;
      msgStream << typeid(TImplementation).name() << " is not a base class of "
                << typeid(TInterface).name();
      throw IocppRegistrationException(msgStream.str());
    }

    const char *key = typeid(TImplementation).name();

    std::map<std::string, IocppRegistration>::iterator iter =
        m_registrations.find(key);

    if (iter == m_registrations.end()) {
      m_registrations[key] = IocppRegistration();
    }
  }
};
Iocpp *Iocpp::m_instance = NULL;
} // namespace iocpp
#endif