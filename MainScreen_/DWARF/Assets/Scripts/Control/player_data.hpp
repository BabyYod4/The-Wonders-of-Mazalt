#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../ADT/tile_coordinate.hpp"
#include "../ADT/tile_data.hpp"
#include "../ADT/settings.hpp"
#include "game_map.hpp"
#include "camera.hpp"
#include <iostream>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML/System.hpp>
#include <SFML\Graphics.hpp>

template < int ROW, int COL >
class player_data{
private:
	sf::RenderWindow & window;
	camera & player_view;
	game_map<ROW, COL> & map;
	settings::player::options settings;
	sf::Sprite player;
	sf::Texture player_texture;
	sf::Sprite weapon;
	sf::Texture weapon_texture;
	char side;

	void _place() {

		window.clear();
		
		player.setPosition(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].pos);
		player_view.set_center(sf::Vector2f{ map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].mid });
		
		map.redraw();
		window.draw(player);
		window.display();
		sf::sleep(sf::milliseconds(50));


	}

public:
	


	player_data(sf::RenderWindow & window , camera & player_view , game_map<ROW, COL> & map, settings::player::options settings) :
		window(window),
		player_view(player_view),
		map(map),
		settings(settings)
	{
		player_texture.loadFromFile(TEXTURES + "green.png");
		player.setTexture(player_texture);
		player.setPosition(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].pos);

		weapon_texture.loadFromFile(TEXTURES + "red.png");
		weapon.setTexture(weapon_texture);

		player_view.set_center(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].mid);

		map.redraw();
		window.draw(player);
		window.display();

	}


	void move_up() {
		if (!is_collision('u', 1) ) {
			--settings.player_pos.pos_y;
			_place();
			side = 'u';
		}
	}

	void move_down() {
		if (!is_collision('d', 1) ) {
			++settings.player_pos.pos_y;
			_place();
			side = 'd';
		}
	}

	void move_left() {
		if (!is_collision('l', 1) ) {
			--settings.player_pos.pos_x;
			_place();
			side = 'l';
		}
	}
	
	void move_right() {
		if (!is_collision('r', 1) ) {
			++settings.player_pos.pos_x;
			_place();
			side = 'r';
		}
	}

	bool is_collision(const char & _side, const int & level, const int & range = 1) {
		int x = 0, y = 0;
		switch (_side) {
			case 'l':
				y = settings.player_pos.pos_y;
				x = settings.player_pos.pos_x -range ;
				break;
			case 'r':
				y = settings.player_pos.pos_y;
				x = settings.player_pos.pos_x + range;
				break;
			case 'u':
				y = settings.player_pos.pos_y -range;
				x = settings.player_pos.pos_x;
				break;
			case 'd':
				y = settings.player_pos.pos_y +range;
				x = settings.player_pos.pos_x;
				break;
		};
	
		const tile_data & data = map.matrix[y][x];
		if (data.level == level) { 
			return true; 
		}
		return false;
		
	}

	void draw_weapon(const int & range) {
		int x = 0;
		int y = 0;
		switch (side) {
		case 'l':
			y = settings.player_pos.pos_y;
			x = settings.player_pos.pos_x - range;
			break;
		case 'r':
			y = settings.player_pos.pos_y;
			x = settings.player_pos.pos_x + range;
			break;
		case 'u':
			y = settings.player_pos.pos_y - range;
			x = settings.player_pos.pos_x;
			break;
		case 'd':
			y = settings.player_pos.pos_y + range;
			x = settings.player_pos.pos_x;
			break;
		};

		sf::Vector2f & weapon_pos = map.matrix[y][x].pos;
		weapon.setPosition(weapon_pos);
		map.clear();
		map.redraw();
		window.draw(weapon);
		window.draw(player);
		window.display();
	}

	bool is_target_hit(const char & side, const int & range) {
		
		for (int i = 1; i <= range; ++i) {
			if (is_collision(side, 1, i)) { return true; }
			draw_weapon(i);
		}
		return false;
	}

	

	void fire_weapon() {
		if ( is_target_hit(side, 10) ) {
			std::cout << "BOOM HEADSHOT! \n";
		}
		std::cout << "\n";

	}

	void start() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move_up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move_down();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			move_left();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move_right();
		}
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
			fire_weapon();
		}

	}


};



#endif // PLAYER_DATA_HPP

