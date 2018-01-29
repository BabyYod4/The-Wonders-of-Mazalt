#ifndef GAME_STATE_ENGINE_HPP
#define GAME_STATE_ENGINE_HPP

#include "state.hpp"
#include <vector>
#include <string>

class game_state_engine{
private: 
	std::vector< state > & states;
	int current = 0;

public:
	game_state_engine(std::vector< state > & states):
		states(states)
	{}

	
	void check_state() {
		state & data = states[current];

		for (auto & evt : data.events) {
			if (evt.condition()) {
				if (evt.next_state > 0) { current = evt.next_state; }
				evt.action();
				return;
			}
		}

		data.task();
		current = data.next_state;

	}

};


#endif //GAME_STATE_ENGINE_HPP

