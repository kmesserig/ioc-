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

map<string, Node> m_nodes;

template<class T>
void Register()
{
        const char *key = typeid(T).name();
        m_nodes = map<string, Node>();
        
        Node node = Node();
        node.func = [&]()-> void* {
            return (void*) new T();
        };
        
        m_nodes[key] = node;
}

template<class T>
void* Resolve()
{
    const char *key = typeid(T).name();
    return m_nodes[key].func();
}


class Person
{
    public:
        Person()
        {
            cout<<"Instance created default"<<endl;
        }
        
        Person(void* p)
        {
            cout<<"Instance created"<<endl;
        }
        
        void doSomeThing()
        {
            cout<<"Done something"<<endl;
        }
};

int main()
{
        Register<Person>();
        
        void* p = Resolve<Person>();
        Person pP = static_cast<Person>(p);
        pP.doSomeThing();
}
