#ifndef TILE_DATA_HPP
#define TILE_DATA_HPP

#include <SFML/System/Vector2.hpp>
#include <string>

struct tile_data {
	int id;
	sf::Vector2i size;
	sf::Vector2f pos;
	std::string texture;
};


#endif //TILE_DATA_HPP




