#ifndef GAME_STATE_ENGINE_HPP
#define GAME_STATE_ENGINE_HPP

#include "state.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <Library\list_tools.hpp>

class game_state_engine{
private: 
	sf::RenderWindow & window;
	std::vector< state > & states;
	std::vector< std::string > & special_states;
	int current = 0;

	std::string _check() {
		state & data = states[current];

		if (contains< std::string >(data.state_name, special_states)) {
				current = data.next_state;
				return data.state_name;
		}

		for (auto & evt : data.events) {
			if (evt.condition()) {
				if (evt.next_state > 0) { current = evt.next_state; }
				return std::string("");
			}
		}

		data.task();
		current = data.next_state;

		return std::string("");

	}


public:
	game_state_engine(sf::RenderWindow & window, std::vector< state > & states, std::vector< std::string > & special_states ):
		window(window),
		states(states),
		special_states(special_states)
	{}

	
	std::string check_state() {
		return _check();
	}

};


#endif //GAME_STATE_ENGINE_HPP


//template<typename T, typename P>
//class action {
//private:
//	std::function< T(P) > func;
//public:
//	action(std::function< T(P) > func) :
//		func(func)
//	{}
//
//	void operator()() {
//		func();
//	}
//};