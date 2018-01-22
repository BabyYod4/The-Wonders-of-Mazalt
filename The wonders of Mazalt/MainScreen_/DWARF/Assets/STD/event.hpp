#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>

struct _event_{
	std::function< bool() > condition;
	const int next_state = -1;
};

#endif // EVENT_HPP

