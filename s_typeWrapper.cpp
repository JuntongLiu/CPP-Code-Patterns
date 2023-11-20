/* 
 * Juntong Liu 
 *          2023-July-10 
 * 
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

// ...




