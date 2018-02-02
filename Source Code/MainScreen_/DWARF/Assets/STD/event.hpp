/*
@file event.hpp
@author Arsalan Anwari
@author Coen Schoof
@brief This is an abstract data type used in by a state
*/

#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <string>

struct _event_{
	const int next_state = -1;
	std::string name = "";
	std::function< bool() > condition = [=]()->bool { return false; };
	std::function< void() > action = [=]()->void {};
};

#endif // EVENT_HPP

