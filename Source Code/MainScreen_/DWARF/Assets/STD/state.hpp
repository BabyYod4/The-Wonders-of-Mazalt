#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <string>
#include <functional>
#include "event.hpp"

struct state {
	const int id;
	const int next_state;
	const std::string state_name;
	std::vector<_event_> events = { _event_ {} };
	std::function< void(void) > task = [=]()->void {};
};


#endif //STATE_HPP
