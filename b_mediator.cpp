/*
 * Juntong Liu
 *         2023-nov-13
 * 
 *  Mediator is a behavioral design pattern that reduces coupling between components of a program by making them 
 *  communicate indirectly, through a special mediator object.
 *
 *  Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from 
 *  referring to each other explicitly, and it lets you vary their interaction independently. 
 *
 *  Popularity: Usage examples: The most popular usage of the Mediator pattern in C++ code is facilitating communications between GUI 
 *  components of an app. The synonym of the Mediator is the Controller part of MVC (model-viewer-controller) pattern.
 **/


#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <list>

#define MAX_KEEPT_MSG  100      // each component keep maximum 100 message.

class MediatorBase;

class ComponentBase{           // abstract component interface
    public:
        ComponentBase() = default;
        virtual ~ComponentBase() = default;

        virtual void SendMsg(const std::string msg, int id) const = 0; 
        virtual void RecvMsg(std::string msg) = 0;
        virtual int get_id() = 0;
};

class MediatorBase{        // abstract mediator interface
    public:
        virtual ~MediatorBase() = default;
        virtual void SendMsg(const std::string msg, int it) = 0;      // can not be const when using iterator within the func 
        virtual void RegisterComponent(std::unique_ptr<ComponentBase> cmpntin) = 0;
};

// a concrete mediator.
class Mediator : public MediatorBase { 
    public:
        Mediator() = default;
        ~Mediator() = default;

        void SendMsg(const std::string msg, int id) override {
            // id = -1 broadcast
            if(id < 0){
                for(std::vector<std::unique_ptr<ComponentBase>>::iterator it = m_component_list.begin(); 
                    it != m_component_list.end(); it++){ 
                        ComponentBase *bp = (*it).get();
                        if(bp->get_id() != id)
                            bp->RecvMsg(msg);
                }
            }
            else {  
                for(std::vector<std::unique_ptr<ComponentBase>>::iterator it = m_component_list.begin(); 
                    it != m_component_list.end(); it++){
                        ComponentBase *bp = (*it).get();                    
                        if(bp->get_id() == id){
                            bp->RecvMsg(msg);
                            break;
                        }
                    }
              }
        }
        
        void RegisterComponent(std::unique_ptr<ComponentBase> cmpnt) override {
            m_component_list.push_back(std::move(cmpnt));
        }

    private:
        std::vector<std::unique_ptr<ComponentBase>> m_component_list;
};

// Components
class Component_1 : public ComponentBase {
    public:
        Component_1(int id, MediatorBase *mediator = nullptr)
            : m_id{id}, m_mediator{mediator}{}

        void SendMsg(const std::string msg, int id) const override {
            m_mediator->SendMsg(msg, id);
        }

        void RecvMsg(std::string msg) override {
            if(m_received_msg.size() > MAX_KEEPT_MSG){
                m_received_msg.pop_front();
            }
            m_received_msg.push_back(msg);
            std::cout << "\nComponent_1 have received a message : " << msg << '\n' << '\n';
        }

        void Register() {
            m_mediator->RegisterComponent(std::make_unique<Component_1>(*this));   // <ComponentBase>(*this));  <<-- this is wrong
        }

        int get_id() override {return m_id;}

    private:
        int m_id;
        MediatorBase *m_mediator;
        std::list<std::string> m_received_msg;
};

class Component_2 : public ComponentBase {
    public:
        Component_2(int id, MediatorBase *mediator)
            : m_id{id}, m_mediator{mediator}{}

        void SendMsg(const std::string msg, int id) const override {
            m_mediator->SendMsg(msg, id);
        }

        void RecvMsg(std::string msg) override {
            if(m_received_msg.size() > MAX_KEEPT_MSG){
                m_received_msg.pop_front();
            }
            m_received_msg.push_back(msg);
            std::cout << "\nComponet_2 has received a message: " << msg << '\n' << '\n';
        }

        void Register() {
            m_mediator->RegisterComponent(std::make_unique<Component_2>(*this));
        }
        
        int get_id() override {return m_id;}

    private:
        int m_id;
        MediatorBase *m_mediator;
        std::list<std::string> m_received_msg;
};

//....more components 

int main(){

    Mediator mediator;                    // create a mediator
    Component_1 cpnt1(1, &mediator);
    cpnt1.Register();
    Component_2 cpnt2(2, &mediator);
    cpnt2.Register();

    cpnt1.SendMsg("........ A Test Message from component-1.........", 2);       // send a message to id=2 component
    cpnt2.SendMsg("+++++++ a test message from component-2 +++++++++", -1);      // broadcast a message

    return 0;
}
