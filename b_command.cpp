/* 
 * File name: b_command.cpp
 *
 * Design pattern is a common way to solve a generic problem.
 * Design pattern can be roughly divided into 3 categories: 
 *
 *     Behavioral     ---- Behavioral design patterns that focus on the interactions and communication between objects concerned with 
 *                         algorithms and the assignment of responsibilities between objects.
 *     Creational     ---- Creational design patterns that deal with object creation mechanisms, trying to create objects in a manner suitable to the situation.
 *     Structural     ---- structural patterns are used to describe how objects can be composed to form larger structures while 
 *                         keeping the individual objects and their relationships intact.   
 */

#include <iostream>
#include <memory>

class CommandBase {
    public:
      CommandBase() = default;
      virtual ~CommandBase() = default;
      // declares an interface for executing an operation.
      virtual void execute() = 0;
}; 

template <typename CmdCodeT>
class Commands : public CommandBase {  
    public:
        typedef void (CmdCodeT::* Action)();     // or use thypedef std::function<void()> Action;
        Commands(std::unique_ptr<CmdCodeT> receiver, Action action) 
            : m_receiver{std::move(receiver)}, m_action{action} { }
        
    
        virtual void execute() {
            //m_receiver.get()->action();     
            m_receiver->action();         
        }

    private:
        std::unique_ptr<CmdCodeT> m_receiver;
        Action m_action;
};

// 
class CommandAction_1 {    
    public:
        void action() {
            std::cout << "CommandAction_1::action" << '\n';
            do_something_1();
            do_something_2();
            // ...
        }
        void do_something_1() {std::cout << "Command execute command-code-set-1 CommandAction_1::do_something_1" << '\n';};
        void do_something_2() {std::cout << "Command execute command-code-set-1 CommandAction_1::do_something_2" << '\n';};
};

class CommandAction_2 {   
    public:
        void action() {
            std::cout << "CommandAction_2::::action\n";
            do_something_1(); 
            do_something_2();
            //...
        }
        void do_something_1() {std::cout << "Command execute command-code-set-2 CommandAction_2::do_something_1\n";};
        void do_something_2() {std::cout << "Command execute command-code-set-2 CommandAction_2::do_something_2" << '\n';};

};

// ....

int main() {
  std::unique_ptr<CommandAction_1> cmd_code_1 = std::make_unique<CommandAction_1>();
  std::unique_ptr<CommandAction_2> cmd_code_2 = std::make_unique<CommandAction_2>();
  // ...
  std::unique_ptr<Commands<CommandAction_1>> command1 = std::make_unique<Commands<CommandAction_1>>(std::move(cmd_code_1), &CommandAction_1::action);
  std::unique_ptr<Commands<CommandAction_2>> command2 = std::make_unique<Commands<CommandAction_2>>(std::move(cmd_code_2), &CommandAction_2::action);
  // Execute the commands.  
  command1->execute();
  command2->execute();  

  // Or: 
  Commands cmd1 =  Commands(std::move(cmd_code_1), &CommandAction_1::action);
  Commands cmd2 =  Commands(std::move(cmd_code_2), &CommandAction_2::action);
  // Execute the commands.  
  cmd1.execute();
  cmd2.execute();

  return 0;
  
}
