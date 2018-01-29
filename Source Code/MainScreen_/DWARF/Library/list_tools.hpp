#ifndef LIST_TOOLS_HPP
#define LIST_TOOLS_HPP

template < typename T>
bool contains(T item, vector<T> & list) {
	for (auto & e : list) {
		if (e == item) {
			return true;
		}
	}
	return false;
}

#endif //LIST_TOOLS_HPP



