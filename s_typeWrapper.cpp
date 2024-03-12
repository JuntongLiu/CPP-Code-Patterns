/* 
 * Juntong Liu 
 *          2023-July-10
 * 
 * A way to wrap different types.
 * 
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class TypeBar;
class TypeFoo;

#if 0
class Concept{
    public:
        virtual ~Concept() = default;
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
#endif

// ===========================================================================
// Or, put all together, we make a sigle typeWrapper class (same as above):
//============================================================================

class TypeWrapper 
{ 
    public:
    
        template <typename T> 
        TypeWrapper(T&& obj): object(std::make_shared<Model<T>>(std::forward<T>(obj))){}    

        std::string interfaceFunc()  const {    // can have more if needed  
            return object->interfaceFunc();
        }

        struct Concept {
            virtual ~Concept() {}
            virtual std::string interfaceFunc() = 0; 
        };

        template< typename T >
        struct Model : Concept {
                Model(const T& t) : object(t) {}
                std::string interfaceFunc() override {  
                    return object.interfaceFunc();
                }

            private:
                T object;
        };

    private:    
        std::shared_ptr<Concept> object;
};


// Different types:

class TypeBar{                 // type 1
    public:
        TypeBar(double x, double y) : m_x{x}, m_y{y}{}

        std::string interfaceFunc() {
            std::cout << "x = " << m_x << ", y = " << m_y << '\n'; 
            std::cout << "in TypeBar, sum = " << getSum() << '\n'; 
            return "Module TypeBar has been executed!";
        }   
        
        double getSum() { 
            m_sum = m_x + m_y; 
            return m_sum;
        }

    private:
        double m_x;
        double m_y;
        double m_sum;
};

class TypeFoo{              // type 2
    public:
        TypeFoo(int x, int y) : m_x{x}, m_y{y}{};

        std::string interfaceFunc() {
            std::cout << "x = " << m_x << ", y = " << m_y << '\n'; 
            getResult();
            return "Module TypeFoo has been executed!";
        }

        void getResult() {
            m_mult = m_x * m_y;
            std::cout << "In TypeFoo, multiply get : " << m_mult << '\n';
        }

    private:
        int m_x;
        int m_y;
        int m_mult;
}; 
// .... more types.

// Client codes to use the typeWrapper list with different types objects
int main(){
    std::vector<std::shared_ptr<TypeWrapper>> differentObjectList{};
    TypeFoo fobj(6, 6);
    std::shared_ptr<TypeWrapper> twp2 = std::make_shared<TypeWrapper>(fobj);
    differentObjectList.push_back(twp2);
    
    differentObjectList.push_back(std::make_shared<TypeWrapper>(TypeBar(1.1, 2.2)));
    //differentObjectList.push_back(std::make_shared<TypeWrapper>(*std::make_shared<TypeFoo>(3, 3))); // do not work
    std::shared_ptr<TypeBar> bptr = std::make_shared<TypeBar>(5.5, 5.5);          // OK
    std::shared_ptr<TypeWrapper> twp = std::make_shared<TypeWrapper>(*bptr);
    differentObjectList.push_back(twp);

    for (size_t i{0}; i<differentObjectList.size(); i++)
        differentObjectList[i]->interfaceFunc();

    return 0;
}
