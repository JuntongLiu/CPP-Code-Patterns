/* 
 *   Juntong Liu
 *        2024-03-05
 *   
 *   "Defines a family of algorithms, encapsulates each one, and make them interchangeable. Strategy lets the 
 *   algorithm vary independently from clients who use it.
 *
 *   The strategy pattern (also known as the policy pattern) is a behavioral software design pattern that enables 
 *   selecting an algorithm at runtime. Instead of implementing a single algorithm directly, code receives run-time 
 *   instructions as to which in a family of algorithms to use.[1]
 *
 *   Strategy lets the algorithm vary independently from clients that use it.
 *
 *   Strategy is a behavioral design pattern that turns a set of behaviors into objects and makes them interchangeable 
 *   inside original context object."
 * 
 *   Strategy pattern is a little similar to the state pattern.
 *
 */

#include <iostream>
#include <algorithm>
#include <string_view>
#include <memory>
#include <string>
#include <vector>
#include <limits>

class AlgorithmBase {
    public:
        virtual ~AlgorithmBase() = default;
        virtual std::string doAlgorithm(std::string_view st) const = 0;

};

// Sort string decendingly
class Algorithm_0 : public AlgorithmBase {
    public:
        std::string doAlgorithm(std::string_view st) const override {
            std::string result(st);
            std::sort(result.begin(), result.end());
            std::cout << result << ": Sorted acendingly\n";
            return result;
        } 
};

// sort string acendingly
class Algorithm_1 : public AlgorithmBase {
    public:
        std::string doAlgorithm(std::string_view st) const override {
            std::string result(st);
            std::sort(result.begin(), result.end(), [](int a, int b){return a > b;});     // sort decendingly use lambda
            std::cout << result << ": Sorted decendingly\n";
            return result;
        }
};

// reverse the string
class Algorithm_2: public AlgorithmBase {
    public:
        std::string doAlgorithm(std::string_view st) const override {
            std::string result(st);
            std::reverse(result.begin(), result.end());
            std::cout << result << ": String has be reversed.\n"; 
            return result;
        }
};

class Context {
    private:
        std::vector<std::unique_ptr<AlgorithmBase>> m_algorithm;

    public:
        void runAlgorithm(std::string_view st, int index){
            std::string ret = m_algorithm[index]->doAlgorithm(st);
        }
        void addAlgorithm(std::unique_ptr<AlgorithmBase> abp){
            if(abp)
                m_algorithm.push_back(std::move(abp));
        }
        AlgorithmBase *getAlgo(int index){ return m_algorithm[index].get();}
};

// Class handling user input from keyboard
class UserInput{
    public:
        double getNumber(){
            while(true){
                double user_in{};
                std::cout << "Enter a number: ";
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
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');;     // and remove the bad input

                    std::cout << "Oops, input is invalid.  Please try again.\n\n";
                }
                else
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove any extraneous input
                    return user_in;
                }
            }
        }
};

int main(){

    Context ctx;
    ctx.addAlgorithm(std::make_unique<Algorithm_0>());
    ctx.addAlgorithm(std::make_unique<Algorithm_1>());
    ctx.addAlgorithm(std::make_unique<Algorithm_2>());

    std::cout << "Type in a string(UTF-8) and then pick an algorithm to process it:";
    std::string user_str{};
    std::cin >> user_str;
    std::cout << "You typed in: " << user_str << '\n';

    UserInput uinput;
    double user_in{};
    while(true){
        while(true){
            std::cout << "\nPick an algorithm: 0, 1, or 2 \n";
            std::cout << "0: Sort the string decendingly;\n";
            std::cout << "1: Sort the string acendingly; \n";
            std::cout << "2: Reverse the string; \n";
            std::cout << "999 : quit the program; \n\n";

            user_in = uinput.getNumber();
            if(user_in == 999)
                return 0;
            if(user_in == 0 || user_in == 1 || user_in == 2)
                break;
            else
                std::cout << "Algorithm does not exist! Try again\n";
        }
      
        int algo_num = static_cast<int>(user_in);
        switch(algo_num){
            case 0:
                ctx.getAlgo(algo_num)->doAlgorithm(user_str);
                break;
            case 1:
                ctx.getAlgo(algo_num)->doAlgorithm(user_str);
                break;

            case 2:
                ctx.getAlgo(algo_num)->doAlgorithm(user_str);
                break;
            default:
                std::cout << "No algorithm found\n";
                break;
        };
    }
    
    return 0;
}
