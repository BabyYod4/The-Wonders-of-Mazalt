/*
@page enemy.hpp
@author Arsalan Anwari
@brief This file contains the enemy controll class
*/

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../ADT/tile_coordinate.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
@brief This class is (partialy) responsible for the enemy logic
*/
class enemy {
private:
	
	/*
	@brief This function is used to calculate the area of view of the enemy 
	@details The area of view means the range an enmy can spot a player to start an attack
	@param void
	@return void
	*/
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

	/*
	@brief This function is used to change the position of the enemy
	@param x: & const int, y: & const int
	@return void
	*/
	void set_pos(const int & x, const int & y) {
		pos.pos_x = x;
		pos.pos_y = y;
	}

	/*
	@brief This function is used to decided wether a player has been spotted
	@detail It does this, by checking if the player is within the area of view
	@param player_pos: &const tile_coordinate
	@return bool
	*/
	bool player_detected(const tile_coordinate & player_pos) {
		if ((player_pos.pos_x >= begin.x && player_pos.pos_x <= (begin.x + sight_range.x)) && (player_pos.pos_y >= begin.y && player_pos.pos_y <= end.y)) {
			return true;
		}
		return false;
	}

};



#endif // ENEMY_HPP
