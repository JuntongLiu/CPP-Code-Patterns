/* 
 * Juntong Liu 
 *          2023-July-10 
 * 
 * Wrap differet types with an interface into an unified wrapper type so that they can be managed together.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Concept{
    public:
        ~Concept() = default;
        virtual std::string InterfaceFunc() = 0;    
};

template<typename T>
class Model : public Concept {
    public:
        Model(const std::shared_ptr<T> t) : object{t}{};
        std::string InterfaceFunc() override {
            return object->InterfaceFunc();
        }

    private:
        std::shared_ptr<T> object; 
};

class TypeWrapper{
    public:
        template<typename T>
        TypeWrapper(std::shared_ptr<Model<T>> obj) : object{obj} {};

        std::string InterfaceFunc() {
            return object->InterfaceFunc();
        }

    private:
        std::shared_ptr<Concept> object;
};

struct TypeBar{
    public:
        TypeBar(double x, double y) : x{x}, y{y}{}

        std::string InterfaceFunc() {
            std::cout << "x = " << x << ", y = " << y << '\n'; 
            std::cout << "in TypeBar, sum = " << getSum() << '\n'; 
            return "Module TypeBar has been executed!";
        }   
        
        double getSum() { 
            sum = x + y; 
            return sum;
        }

    private:
        double x;
        double y;
        double sum;
};

struct TypeFoo{
    public:
        TypeFoo(int x, int y) : x{x}, y{y}{};

        std::string InterfaceFunc() {
            std::cout << "x = " << x << ", y = " << y << '\n'; 
            getResult();
            return "Module TypeFoo has been executed!";
        }

        void getResult() {
            mult = x * y;
            std::cout << "In TypeFoo, multiply get : " << mult << '\n';
        }

    private:
        int x;
        int y;
        int mult;
}; 

// .... more types/modules....

class ModulesList{
    public:
        ModulesList(int i = 0) : m_count{i}{};
        ~ModulesList() = default;

        void addObject(std::unique_ptr<TypeWrapper> obj){
            m_obj_list.push_back(std::move(obj));
            m_count++;
        };

        void runModules() { 
            for (std::vector<std::unique_ptr<TypeWrapper>>::iterator it =  m_obj_list.begin(); 
                it != m_obj_list.end(); it++){ 
                std::cout << (*it)->InterfaceFunc() << '\n';
            }
        }

        void printCount() const {
            std::cout << "Count = " << m_count << '\n'; }

    private:
        std::vector<std::unique_ptr<TypeWrapper>> m_obj_list;
        int m_count;
};

int main(){

    ModulesList modules;

    std::shared_ptr<TypeBar> bp = std::make_shared<TypeBar>(1.1, 1.1); 
    std::shared_ptr<Model<TypeBar>> pmb = std::make_shared<Model<TypeBar>>(bp); 
    std::unique_ptr<TypeWrapper> ombp = std::make_unique<TypeWrapper>(pmb);
    modules.addObject(std::move(ombp));

    std::shared_ptr<TypeFoo> fp = std::make_shared<TypeFoo>(22, 22);
    std::shared_ptr<Model<TypeFoo>> pmf = std::make_shared<Model<TypeFoo>>(fp);
    std::unique_ptr<TypeWrapper> omfp = std::make_unique<TypeWrapper>(pmf);
    modules.addObject(std::move(omfp));

    modules.runModules();
    modules.printCount();

    return 0;
}
