// Example program
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <map>

using namespace std;

typedef struct NODE{
    function<void*()> func;
}Node;

map<string, Node> m_nodes = map<string, Node>();

template<class T>
void Register()
{
        const char *key = typeid(T).name();
        
        
        Node node = Node();
        node.func = []()-> void* {
            return (void*) new T();
        };
        
        m_nodes[key] = node;
}

template<class TInterface, class TImplementation>
void Register()
{
        const char *key = typeid(TInterface).name();
        
        
        Node node = Node();
        node.func = []()-> void* {
            return (void*) new TImplementation();
        };
        
        m_nodes[key] = node;
}

template<class T>
Node Resolve()
{
    const char *key = typeid(T).name();
    map<string, Node>::iterator iMapping = m_nodes.find(key);

    if (iMapping != m_nodes.end())
    {
      return iMapping->second;
    }
}

class IService
{
    public:
        IService(){}
        IService(void* _){}
        virtual void Work(){};
};

class Service : IService
{
    public:
        Service(){}
        Service(void* p){Service();}
        void Work() {cout<<"Worked"<<endl;}
};

class Consumer
{
    private:
        IService m_service;
    public:
        Consumer()
        {
            Node n = Resolve<IService>();
            m_service = (IService) n.func();
            cout<<"Instance created default"<<endl;
        }
        
        Consumer(void* _)
        {
            Consumer();
        }
        
        void doSomeThing()
        {
            cout<<"Done something"<<endl;
            m_service.Work();
        }
};

int main()
{
        Register<Consumer>();
        Register<IService, Service>();
        Node n = Resolve<Consumer>();
        
        Consumer P = (Consumer)n.func() ;
        P.doSomeThing();
}
