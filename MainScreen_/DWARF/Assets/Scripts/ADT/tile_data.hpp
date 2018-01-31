#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include <SFML/System/Vector2.hpp>
#include <string>

struct tile_data {
	int id = -1;
	int level = 0;
	sf::Vector2i size;
	sf::Vector2f pos;
	sf::Vector2f mid;
	std::string texture;
};


#endif //TILE_DATA_HPP




