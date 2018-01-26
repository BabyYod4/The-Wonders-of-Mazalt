#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../ADT/tile_coordinate.hpp"
#include "../ADT/tile_data.hpp"
#include "game_map.hpp"
#include "camera.hpp"
#include <iostream>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

template < int ROW, int COL >
class player_data{
private:
	sf::RenderWindow & window;
	camera & player_view;
	game_map<ROW, COL> & map;
	tile_coordinate player_pos;
	sf::Sprite player;
	sf::Texture player_texture;

	void _place() {
		window.clear();
		
		player.setPosition(map.matrix[player_pos.pos_y][player_pos.pos_x].pos);
		player_view.set_center(sf::Vector2f{ map.matrix[player_pos.pos_y][player_pos.pos_x].mid });
		
		map.redraw();
		window.draw(player);
		window.display();
		sf::sleep(sf::milliseconds(50));

	}

public:

	player_data(sf::RenderWindow & window , camera & player_view , game_map<ROW, COL> & map, tile_coordinate player_pos) :
		window(window),
		player_view(player_view),
		map(map),
		player_pos(player_pos)
	{
		player_texture.loadFromFile(TEXTURES + "green.png");
		player.setTexture(player_texture);
		player.setPosition(map.matrix[player_pos.pos_y][player_pos.pos_x].pos);

		player_view.set_center(map.matrix[player_pos.pos_y][player_pos.pos_x].mid);

		map.redraw();
		window.draw(player);
		window.display();

	}


	void move_up() {
		if (!is_collision('u') ) {
			--player_pos.pos_y;
			_place();
		}
	}

	void move_down() {
		if (!is_collision('d')) {
			++player_pos.pos_y;
			_place();
		}
	}

	void move_left() {
		if (!is_collision('l')) {
			--player_pos.pos_x;
			_place();
		}
	}
	
	void move_right() {
		if (!is_collision('r')) {
			++player_pos.pos_x;
			_place();
		}
	}

	bool is_collision(const char & side) {
		int x = 0, y = 0;
		switch (side) {
			case 'l':
				y = player_pos.pos_y;
				x = player_pos.pos_x -1 ;
				break;
			case 'r':
				y = player_pos.pos_y;
				x = player_pos.pos_x + 1;
				break;
			case 'u':
				y = player_pos.pos_y -1;
				x = player_pos.pos_x;
				break;
			case 'd':
				y = player_pos.pos_y + 1;
				x = player_pos.pos_x;
				break;
		};
	
		const tile_data & data = map.matrix[y][x];
		if (data.level == 0) { 
			return false; 
		}
		return true;
		
	}




};



#endif // PLAYER_DATA_HPP

