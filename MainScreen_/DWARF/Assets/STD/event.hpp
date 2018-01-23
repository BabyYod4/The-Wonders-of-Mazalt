#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <string>

std::function< bool() > NO_CONDITION = [=]()->bool { return false; };

struct _event_{
	const int next_state = -1;
	std::string name = "";
	std::function< bool() > condition = NO_CONDITION;
	std::function< void() > action = [=]()->void {};
};

#endif // EVENT_HPP

