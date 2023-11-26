/*
 * Juntong Liu
 *         2023-nov-22
 * 
 * This Pattern defines an one-to-many relationship between objects. When changes occure in publisher object, other related objects are notified 
 * and updated automatically.
 * 
 */


#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <random>
#include <chrono>
#include <mutex>
#include <memory>

class Publisher; 

class ObserverBase{
	public:
		virtual ~ObserverBase() = default;
		virtual void update(std::string str) = 0;
		virtual void display_msg() = 0;
		virtual int get_id() const = 0;
};

class PublisherBase{
	public:
		virtual ~PublisherBase() = default;
		virtual void addObserver(ObserverBase *) = 0;
		virtual void removeObserver(int id) = 0;
		virtual void notification(std::string) = 0;

};

class Observer_1 : public ObserverBase {
	public:
		Observer_1(Publisher &pbls, int id = 1, int count = 0)
			: m_publisher{pbls}, m_id{id}, m_count{count}{}
		
		void update(std::string str) override {
			m_mtx.lock();
			m_msg_list.push_back(str);
			m_mtx.unlock();
		}

		void display_msg() override {
			//while(1){
			for(int i=0; i<5000; i++){           // for test
				if(!m_msg_list.empty()){
					m_mtx.lock();
					std::cout << '\n' << "Observer-1:\n";
					for(auto el : m_msg_list)
						std::cout << el <<  ' '; 
					std::cout << "Notification " << m_count++ << " processed." << '\n' << '\n';
					m_msg_list.clear();
					m_mtx.unlock();
				}
				else
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
		
		int get_id() const override {return m_id;};

	private:
		std::mutex m_mtx;
		std::list<std::string> m_msg_list;
		Publisher &m_publisher;
		int m_id;
		int m_count;
};

class Observer_2 : public ObserverBase {
	#define MAX_MSG_LEN 100
	public:
		Observer_2(Publisher &pbls, int id = 2, int count = 0)
			: m_publisher{pbls}, m_id{id}, m_count{count}{}

		void update(std::string str) override {
			if(m_msg_list.size() > MAX_MSG_LEN)
				m_msg_list.pop_front();
			m_msg_list.push_back(str);
			update_states();
			display_msg();
		}

		void display_msg() override {
			std::cout << "All received notifications:\n";
			for(auto elem : m_msg_list)
				std::cout << elem << ' ';	
			std::cout << '\n' << '\n';
		}

		int get_id() const override { return m_id;};

		void update_states() {std::cout << "Observer-2:\nNotification " << m_count++ << " processed and updated states.\n";};

	private:
		std::list<std::string> m_msg_list;
		Publisher &m_publisher;
		int m_id;
		int m_count;
};

std::vector<std::string> data_events{"State-1 changed, ", "State-2 changed, ", "State-3 changed, ", "State-4 changed, ", "State-5 changed, ", "State-6 changed, "};

class Publisher : public PublisherBase {
	public:
		Publisher() = default;
		~Publisher() = default;
		
		void addObserver(ObserverBase *obsv) override {
			m_observer_list.push_back(obsv);
		}
		
		void removeObserver(int id) override {
			for(std::list<ObserverBase *>::iterator it = m_observer_list.begin();
				it != m_observer_list.end(); ++it){
					if((*it)->get_id() == id){
						m_observer_list.erase(it);
					}
				}
		}
		
		void notification(std::string str) override {
			for(std::list<ObserverBase *>::iterator it = m_observer_list.begin(); 
				it != m_observer_list.end(); it++){
					(*it)->update(str);
				}
		}

		void dataSource() {
			//while(1){
			for(int i=0; i<50; i++){          // for test
				std::random_device os_seed;
				uint_least32_t seed = os_seed();
				std::mt19937 generator(seed);
				std::uniform_int_distribution<uint_least32_t> distribution(0, 5);
				unsigned int rn = distribution(generator);
				notification(data_events[rn]);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		}

	private:
		std::list<ObserverBase *> m_observer_list;
};

int main(){

	std::shared_ptr<Publisher> pbls = std::make_shared<Publisher>();
	std::shared_ptr<Observer_1> obs1 = std::make_shared<Observer_1>(*pbls.get(), 1, 0);
	std::shared_ptr<Observer_2> obs2 = std::make_shared<Observer_2>(*pbls.get(), 2, 0);
	pbls->addObserver(obs1.get());
	pbls->addObserver(obs2.get());

	std::thread th2(&Publisher::dataSource, pbls.get());
	std::thread th1(&Observer_1::display_msg, obs1.get());
	
	th1.join();
	th2.join();

	return 0;
}
