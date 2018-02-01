#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../ADT/tile_coordinate.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class enemy {
private:

	void _calc() {
		begin = sf::Vector2i{
			pos.pos_x - (sight_range.x / 2),
			pos.pos_y - (sight_range.y / 2)
		};

		end = sf::Vector2i{
			pos.pos_x + (sight_range.x / 2),
			pos.pos_y + (sight_range.y / 2)
		};
	
	
	}

public:

	tile_coordinate pos;
	int health;
	const sf::Vector2i & sight_range;
	sf::Vector2i begin;
	sf::Vector2i end;

	enemy(tile_coordinate pos, int health, const sf::Vector2i & sight_range):
		pos(pos),
		health(health),
		sight_range(sight_range)
	{
		_calc();
	}

	void set_pos(const int & x, const int & y) {
		pos.pos_x = x;
		pos.pos_y = y;
	}

	bool player_detected(const tile_coordinate & player_pos) {
		if ((player_pos.pos_x >= begin.x && player_pos.pos_x <= (begin.x + sight_range.x)) && (player_pos.pos_y >= begin.y && player_pos.pos_y <= end.y)) {
			return true;
		}
		return false;
	}

};



#endif // ENEMY_HPP
