/* 
 * Juntong Liu 
 *           2024-Feb-28
 * 
 * A finite state-machine with 5 states.
 * 
 * This file contains 2 implementations, ALT_1 and ALT_2.
 * 
 * ALT_1 implementation uses a little more memory.
 * ALT_2 implementation uses a little less memory and should be a little little bit faster. But may not suite for some situations.
 * 
 * */

#define ALT_1
#ifdef ALT_1

#include <iostream>

enum STATES{
	STATE_STOP,         //  
	STATE_PLAYING,      // assume this state can be entered from any other state
	STATE_PAUSE,        // assume can pause play, forward and backward
	STATE_FORWARD,      // assume can only enter from play
	STATE_BACKWARD      // same as forward
};

class StateBase {
	public:
		virtual ~StateBase() = default;
		virtual void stop(void){};  
		virtual void play(void) {}; 
		virtual void pause(void){}; 
		virtual void forward(void){}; 
		virtual void backward(void){}; 
};

class StateStop : public StateBase {
	public:                                                                                   
		void stop(void) override {
			std::cout << "Entered stop state!\n";
		}
};

class StatePlaying : public StateBase {
	public:
		void play(void) override {
			std::cout << "Entered in playing state, do something.\n";
		}
};

class StatePause : public StateBase {
	public:
		void pause(void) override {
			std::cout << "Entered in pause state, do something\n";
		}
};

class StateForward : public StateBase {
	public:
		void forward(void) override {
			std::cout << "Entered forward state, do something\n";
		}
};

class StateBackward : public StateBase {
	public:
		void backward(void) override {
			std::cout << "Entered backward state, do something.\n";
		}	
};

class Machine {
	private:
		StateBase *m_sbp;              // base pointer to associate a state
		int m_currentState = 0;
		int m_state_v1 = 0;
		int m_state_v2 = 0;
		int m_state_v3 = 0;

	public:
		Machine(StateBase *sbp) 
			: m_sbp{sbp}{};

		void stop(StateBase **machine_states){
				std::cout << "stop event has been received\n";
				if(m_currentState != STATE_STOP) {
					m_sbp = machine_states[STATE_STOP];
					m_sbp->stop();
					m_currentState = STATE_STOP;
				}
				else
					std::cout << "Machine already in stop state!\n";
		}

		void play(StateBase **machine_states){      
			std::cout << "play event has been received\n";
			if(m_currentState != STATE_PLAYING){
				m_sbp = machine_states[STATE_PLAYING];
				m_sbp->play();
				m_currentState = STATE_PLAYING;
			}
			else
				std::cout << "Machine is already in playing state!\n";
		}

    void pause(StateBase **machine_states) {  
			std::cout << "pause event have been received\n";
			if(m_currentState != STATE_PAUSE && m_currentState != STATE_STOP){
				m_sbp = machine_states[STATE_PAUSE];
				m_sbp->pause();
				m_currentState = STATE_PAUSE;
			}
			else
				std::cout << "Machine already in pause state or Stop state!\n";
		}
		
    void backward(StateBase **machine_states){  // assume backward state can only entered from playing state
			std::cout << "backward event have been received\n";
			if(m_currentState == STATE_PLAYING){
				m_sbp = machine_states[STATE_BACKWARD];
				m_sbp->backward();
				m_currentState = STATE_BACKWARD;
			}
			else
				std::cout << " Backward state can not be entered from the current state!\n";
		}
		
    void forward(StateBase **machine_states){    // assume forward can only be entered from playing state
			std::cout << "forward event has been received\n";
			if(m_currentState == STATE_PLAYING){
				m_sbp = machine_states[STATE_FORWARD];
				m_sbp->forward();
				m_currentState = STATE_FORWARD;
			}
			else
				std::cout << " Forward can not be entered from current state!\n";
		}

};

int main() {
	
	StateStop stopState{};
	StatePlaying playingState{};
	StatePause pauseState{};
	StateForward forwardState{};
	StateBackward backwardState{};

	StateBase *machine_states[] = {&stopState, &playingState, &pauseState, &forwardState, &backwardState};
	void(Machine::*mfuncp[])(StateBase **) = {&Machine::stop, &Machine::play,     // waste memory, not necessary. Keep this here for lookup
											                      &Machine::pause, &Machine::forward, 
                                            &Machine::backward}; 
	Machine machine(machine_states[0]);

	int u_in;
	std::cout << "\nEnter an Event: \n";
	std::cout << "0: StopEvent, 1: PlayEvent, 2: PauseEvent, 3: ForwardEvent, 4: BackwardEvent, 999 to quit\n";
	std::cin >> u_in;

	while(1){
		std::cout << "You have entered: " << u_in << '\n';

		if(u_in == 999)
			break;

		if (u_in == STATE_STOP || u_in == STATE_PLAYING || u_in == STATE_PAUSE || u_in == STATE_FORWARD 
			|| u_in == STATE_BACKWARD) {
		
				switch(u_in){
					case STATE_STOP:
						(machine.*mfuncp[STATE_STOP])(machine_states);        // can directly use machine.stop(machine_states);
						break;
					case STATE_PLAYING:
						(machine.*mfuncp[STATE_PLAYING])(machine_states);     
						break;
					case STATE_PAUSE:
						(machine.*mfuncp[STATE_PAUSE])(machine_states);     
						break;
					case STATE_FORWARD:
						(machine.*mfuncp[STATE_FORWARD])(machine_states);    
						break;
					case STATE_BACKWARD:
						(machine.*mfuncp[STATE_BACKWARD])(machine_states);
						break;
					default:
						std::cout << "Error happend!\n";
				}
			}
			else
				std::cout << "You have typed in an invalid number! Try again!\n";
			std::cout << "\nEnter an Event:\n";
			std::cout << "0: StopEvent, 1: PlayEvent, 2: PauseEvent, 3: ForwardEvent, 4: BackwardEvent, 999 to quit\n";
			std::cin >> u_in;
	}

	return 0;

}

#elif defined ALT_2

#include <iostream>

enum STATES{
	STATE_STOP,         //  
	STATE_PLAYING,      // assume this state can be entered from any other state
	STATE_PAUSE,        // assume can pause play, forward and backward
	STATE_FORWARD,      // assume can only enter from play
	STATE_BACKWARD      // same as forward
};

class Machine;
class StateStop{
	public:                                                                                   
		void stop(Machine *mch) {
			std::cout << "Entered stop state!\n";
		}
};

class StatePlaying{
	public:
		void play(Machine *mch){
			std::cout << "Entered in playing state, do something.\n";
		}
};

class StatePause{
	public:
		void pause(Machine *mch){
			std::cout << "Entered in pause state, do something\n";
		}
};

class StateForward{
	public:
		void forward(Machine *mch){
			std::cout << "Entered forward state, do something\n";
		}
};

class StateBackward{
	public:
		void backward(Machine *mch){
			std::cout << "Entered backward state, do something.\n";
		}	
};

class Machine {
	private:
		int m_currentState = 0;
		int m_state_v1 = 0;
		int m_state_v2 = 0;
		int m_state_v3 = 0;

	public:
		void stop(){
			std::cout << "stop event has been received\n";
			if(m_currentState != STATE_STOP) {
				StateStop *sstp{nullptr};
				m_currentState = STATE_STOP;
				sstp->StateStop::stop(this);
			}
			else
				std::cout << "Machine already in stop state!\n";
		}
		void play(){
			std::cout << "play event has been received\n";
			if(m_currentState != STATE_PLAYING){
				StatePlaying *splp{nullptr};
				m_currentState = STATE_PLAYING;
				splp->StatePlaying::play(this);
			}
			else
				std::cout << "Machine is already in playing state!\n";
		}
		void pause() {  
			std::cout << "pause event have been received\n";
			if(m_currentState != STATE_PAUSE && m_currentState != STATE_STOP){
				StatePause *spp{nullptr};
				m_currentState = STATE_PAUSE;
				spp->StatePause::pause(this);
			}
			else
				std::cout << "Machine already in pause state or Stop state!\n";
		}
		void backward(){  // assume backward state can only entered from playing state
			std::cout << "backward event have been received\n";
			if(m_currentState == STATE_PLAYING){
				StateBackward *sbp{nullptr};
				m_currentState = STATE_BACKWARD;
				sbp->StateBackward::backward(this);
			}
			else
				std::cout << " Backward state can not be entered from the current state!\n";
		}
		void forward(){    // assume forward can only be entered from playing state
			std::cout << "forward event has been received\n";
			if(m_currentState == STATE_PLAYING){
				StateForward *sfp{nullptr};
				m_currentState = STATE_FORWARD;
				sfp->StateForward::forward(this);
			}
			else
				std::cout << " Forward can not be entered from current state!\n";
		}

};

int main() {

	Machine machine{};

	int u_in;
	std::cout << "\nEnter an Event: \n";
	std::cout << "0: StopEvent, 1: PlayEvent, 2: PauseEvent, 3: ForwardEvent, 4: BackwardEvent, 999 to quit\n";
	std::cin >> u_in;

	while(1){
		std::cout << "You have entered: " << u_in << '\n';

		if(u_in == 999)
			break;

		if (u_in == STATE_STOP || u_in == STATE_PLAYING || u_in == STATE_PAUSE || u_in == STATE_FORWARD 
			|| u_in == STATE_BACKWARD) {
		
				switch(u_in){
					case STATE_STOP:
						machine.stop();
						break;
					case STATE_PLAYING:
						machine.play();     
						break;
					case STATE_PAUSE:
						machine.pause();     
						break;
					case STATE_FORWARD:
						machine.forward();    
						break;
					case STATE_BACKWARD:
						machine.backward();
						break;
					default:
						std::cout << "Error happend!\n";
				}
			}
			else
				std::cout << "You have typed in an invalid number! Try again!\n";

			std::cout << "\nEnter an Event:\n";
			std::cout << "0: StopEvent, 1: PlayEvent, 2: PauseEvent, 3: ForwardEvent, 4: BackwardEvent, 999 to quit\n";
			std::cin >> u_in;
	}

	return 0;
}

#endif