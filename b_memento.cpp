/*
 * Juntong Liu
 *       2023-nov-06
 * 
 *       
 *  The Originator (the object to be saved) creates a snap-shot of itself as a Memento object, and passes that reference to the Care taker 
 *  object. The Caretaker object keeps the Memento until such a time as the Originator may want to revert to a previous state as recorded 
 *  in the Memento object. 
 * 
 */

#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <list>
#include <limits>

#define MAX_NUM_UNDO  100     // maximum number of undo that can be performed.

class Memento;

class Object {
    public:
        Object(int i) : m_accum{i}{}

        void func1(int x){          // addition
            m_accum += x;
        }

        void func2(int x){          // multiply
            m_accum *= x;
        }

        std::unique_ptr<Memento> createMemento() const { 
            return std::make_unique<Memento>(*this);
        }

        void set_accum(int sum){m_accum = sum;}
        int get_accum(){return m_accum;}
        
    private:
        int m_accum;
};

class Memento { 
    public:
        Memento(Object obj) 
            : m_object{obj}{}

        Object m_object;
};

class Command {
    typedef std::function<void(Object*, int)>  Mfuncp;
    public:
        Command(Object *obj, Mfuncp funcp)
            : m_object{obj}, m_action{funcp}{}
        Command(Object *obj, Mfuncp funcp, int x)           
            : m_object{obj}, m_action{funcp}, m_x{x}{}
      
        void execute(int);
        static void redo();
        static void undo();
        
    private:
        Object *m_object;
        Mfuncp m_action;
        int m_x;
        static int m_index;
        static std::list<std::unique_ptr<Memento>> m_mementoList;       
        static std::list<std::unique_ptr<Command>> m_commandList;
};

int Command::m_index;
std::list<std::unique_ptr<Memento>> Command::m_mementoList;
std::list<std::unique_ptr<Command>> Command::m_commandList;

void Command::execute(int i) { 
    if(m_index + 1 > MAX_NUM_UNDO){   // only keep MAX_NUM_UNDO, older will be overwrite 
        m_mementoList.pop_front();
        m_commandList.pop_front();
        m_index--;
    }
    m_x = i;
    m_action(m_object, i);
    std::unique_ptr<Memento> ump = m_object->createMemento();
    m_mementoList.push_back(std::move(ump));
    std::unique_ptr<Command> cmdp = std::make_unique<Command>(*this);
    if(i == 1)
        std::cout << "\naccumulater add one, m_accum = " << cmdp->m_object->get_accum() << '\n' << '\n';
    else
        std::cout << "\naccumulator multiply two, m_accum = " << cmdp->m_object->get_accum() << '\n' << '\n';
    m_commandList.push_back(std::move(cmdp));  
    m_index++;
}

void Command::redo(){ 
    if(m_index == 0){
        std::cout << "No command has been excuted! \n";
        return;
    }
    if(m_index + 1 > MAX_NUM_UNDO){
        m_mementoList.pop_front();
        m_commandList.pop_front();
        m_index--;
    }
    
    Command *cmdp = m_commandList.back().get(); 
    cmdp->m_action(cmdp->m_object, cmdp->m_x); 
    std::cout << "\nRedo() is executed, now m_accum = " << cmdp->m_object->get_accum() << '\n' << '\n'; 
    std::unique_ptr<Memento> ummtp = cmdp->m_object->createMemento();
    m_mementoList.push_back(std::move(ummtp));
    std::unique_ptr<Command> ucmdp = std::make_unique<Command>(cmdp->m_object, cmdp->m_action, cmdp->m_x); 
    m_commandList.push_back(std::move(ucmdp));
    m_index++;    
}
   

void Command::undo(){ 
    if(m_index == 1){
        auto  tmp = m_commandList.end();  // can use .back().get() 
        Command *cmd = (*--tmp).get();
        cmd->m_object->set_accum(0); 
        std::cout << "\nUndo() is executed, now m_accum = " << cmd->m_object->get_accum() << '\n' << '\n'; 
        //change other states if has......
        m_mementoList.pop_back();
        m_commandList.pop_back();
        m_index--;
    }
    else if (m_index > 1) {      
        std::list<std::unique_ptr<Memento>>::iterator tmp1 = m_mementoList.end();    // can use .back().get();
        Memento *memp = (*--tmp1).get();
        std::list<std::unique_ptr<Command>>::iterator tmp2 = m_commandList.end();
        Command *cmdp = (*--tmp2).get();

        if(cmdp->m_x == 1){  
            cmdp->m_object->set_accum(memp->m_object.get_accum()-1);  
            std::cout << "\nUndo() is executed to -1, now m_accum = " << cmdp->m_object->get_accum() << '\n' << '\n';  
        }else if(cmdp->m_x == 2){
            cmdp->m_object->set_accum(memp->m_object.get_accum()/2);
            std::cout << "\nUndo() is executed to /2, now m_accum = " << cmdp->m_object->get_accum() << '\n' << '\n';  
        }
        //... if there are more states, retore them

        m_mementoList.pop_back();   // remove the undo-ed entries
        m_commandList.pop_back();
        m_index--;
    }
    else if (m_index == 0)
        std::cout << "Can not execute undo, no command has be execute!"  << '\n';
};   

class UserInput{
    public:
        double getNumber(){
            while(true){
                double user_in{};
                //std::cout << "Enter a number: ";
                std::cin >> user_in;

                // Check for failed extraction
                if (!std::cin) // if the previous extraction failed.  Same as:  if(std::cin.fail())
                {
                    if (std::cin.eof()) // if the stream was closed
                    {
                        exit(0); // shut down the program now
                    }

                    // let's handle the failure
                    std::cin.clear(); // put us back in 'normal' operation mode
                    ignoreLine();     // and remove the bad input

                    std::cout << "Oops, input is invalid.  Please try again.\n\n";
                }
                else
                {
                    ignoreLine(); // remove any extraneous input
                    return user_in;
                }
            }
        }

        void ignoreLine() {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }   
};

int main(){
    
    Object object(0);
    Command cmd1(&object, &Object::func1);   // plus 1
    Command cmd2(&object, &Object::func2);   // multiply 2
    UserInput uinput{};
    double user_in{};

    while(true){
        while(true){
            std::cout << "\n Enter a command:  \n 0 : Quite,  \n 1 : accumulator plus one,  \n 2 : accumulator multiply two, \n 3 : REDO, \n 4 : UNDO" << '\n' << '\n';
            user_in = uinput.getNumber();

            if(user_in == 0)
                return 0;
            else if (user_in == 1 || user_in == 2 || user_in == 3 || user_in == 4)
                break;
            else
                std::cout << "Invalid command! Try again: \n";
        }
   
        if (user_in == 1){
            cmd1.execute(user_in);
        }
        else if (user_in == 2){
            cmd2.execute(user_in);
        }
        else if(user_in == 3){
            Command::redo();
        }
        else if(user_in == 4){
            Command::undo();
        }
        else
            std::cout << "Error happened!\n";
    }
    
    return 0;
}
