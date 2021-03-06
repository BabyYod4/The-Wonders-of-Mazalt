/*
@file player_data.hpp
@author Arsalan Anwari
@brief This file contains the player_movement control class
*/
#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../ADT/tile_coordinate.hpp"
#include "../ADT/tile_data.hpp"
#include "../ADT/settings.hpp"
#include "game_map.hpp"
#include "camera.hpp"
#include "music_player.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML\Graphics.hpp>
#include "enemy.hpp"

/*
@brief This class is responsible for the player movement logic
@details a template is used to decide wether a playe can shoot or has an enemy
*/
template < int ROW, int COL, bool CAN_SHOOT=false, bool HAS_ENEMY=false >
class player_data{
private:
	sf::RenderWindow & window;
	camera & player_view;
	game_map<ROW, COL> & map;
	music_player & music;
	enemy & boss;
	settings::player::options settings;
	
	sf::Sprite player;
	sf::Texture player_texture;
	sf::Sprite weapon;
	sf::Texture weapon_texture;
	sf::Sprite _boss;
	sf::Texture _boss_texture;
	sf::Sprite boss_weapon;
	sf::Texture boss_weapon_texture;
	
	char side = 'u';
	std::string _side_ = "u";
	bool enemy_spotted = false;
	bool enemy_alive = true;
	int boss_move_counter = 10;

public:

	player_data(sf::RenderWindow & window , camera & player_view , game_map<ROW, COL> & map, music_player & music, enemy & boss ,settings::player::options settings ) :
		window(window),
		player_view(player_view),
		map(map),
		music(music),
		boss(boss),
		settings(settings)
	{

		player_texture.loadFromFile(TEXTURES + settings.player_sprite_map + "/" + _side_ + settings.player_sprite_file_extention);
		player.setTexture(player_texture);
		player.setPosition(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].pos);

		if (CAN_SHOOT) {
			weapon_texture.loadFromFile(TEXTURES + settings.weapon_sprite_map + "/" + _side_ + settings.weapon_sprite_file_extention);
			weapon.setTexture(weapon_texture);
		}

		if (HAS_ENEMY) {
			_boss_texture.loadFromFile(TEXTURES + "Ossas.png");
			_boss.setTexture(_boss_texture);
			_boss.setPosition(map.matrix[boss.pos.pos_y][boss.pos.pos_x].pos);

			boss_weapon_texture.loadFromFile(TEXTURES + "magic_bolt.png");
			boss_weapon.setTexture(boss_weapon_texture);
		}


	}

	/*
	@brief This function is used to show an endgame screen and to end the game
	@param file_path: std::string
	@return void
	*/
	void end_game(std::string file_path) {
		sf::Texture _bg;
		_bg.loadFromFile(file_path);
		sf::Sprite bg(_bg);
		window.setView(window.getDefaultView());
		window.clear();
		window.draw(bg);
		window.display();

		music.stop();

		sf::sleep(sf::seconds(5));
		
		window.close();
	
	}

	/*
	@brief This function is used to put the player in the map without camera alignment
	@param void
	@return void
	*/
	void _pack() {
		window.clear();

		player_texture.loadFromFile(TEXTURES + settings.player_sprite_map + "/" + _side_ + settings.player_sprite_file_extention);
		player.setTexture(player_texture);
		player.setPosition(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].pos);

		map.redraw();
		window.draw(player);
		sf::sleep(sf::milliseconds(70));
	
	}

	/*
	@brief This function is used to put the player in the map with camera alignment
	@param void
	@return void
	*/
	void _place() {

		window.clear();

		player_texture.loadFromFile(TEXTURES + settings.player_sprite_map + "/" + _side_ + settings.player_sprite_file_extention);
		player.setTexture(player_texture);
		player.setPosition(map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].pos);
		player_view.set_center(sf::Vector2f{ map.matrix[settings.player_pos.pos_y][settings.player_pos.pos_x].mid });

		map.redraw();
		window.draw(player);

		if (HAS_ENEMY && enemy_alive) {
			_boss.setPosition(map.matrix[boss.pos.pos_y][boss.pos.pos_x].pos);
			window.draw(_boss);
		}

		window.display();
		sf::sleep(sf::milliseconds(50));
	}


	/*
	@brief This function is used to move the player on the map without camera alignment
	@param dir: &const char
	@return void
	*/
	void move_hard(const char & dir) {
		switch (dir) {
		case 'l':
			--settings.player_pos.pos_x;
			_side_ = "l";
			_pack();
			window.display();
			break;
		case 'r':
			++settings.player_pos.pos_x;
			_side_ = "r";
			_pack();
			window.display();
			break;
		case 'u':
			--settings.player_pos.pos_y;
			_side_ = "u";
			_pack();
			window.display();
			break;
		case 'd':
			++settings.player_pos.pos_y;
			_side_ = "d";
			_pack();
			window.display();
			break;
		};
	
	}

	/*
	@brief This function is used to move the player up
	@param void
	@return void
	*/
	void move_up() {
		if (!is_collision('u', 1) ) {
			--settings.player_pos.pos_y;
			side = 'u';
			_side_ = "u";
			_place();
		}
	}

	/*
	@brief This function is used to move the player down
	@param void
	@return void
	*/
	void move_down() {
		if (!is_collision('d', 1) ) {
			++settings.player_pos.pos_y;
			side = 'd';
			_side_ = "d";
			_place();
		}
	}

	/*
	@brief This function is used to move the player left
	@param void
	@return void
	*/
	void move_left() {
		if (!is_collision('l', 1) ) {
			--settings.player_pos.pos_x;
			side = 'l';
			_side_ = "l";
			_place();
		}
	}
	
	/*
	@brief This function is used to move the player right
	@param void
	@return void
	*/
	void move_right() {
		if (!is_collision('r', 1) ) {
			++settings.player_pos.pos_x;
			side = 'r';
			_side_ = "r";
			_place();
		}
	}

	/*
	@brief This function is used to check wether a player entered an entrance
	@param void
	@return void
	*/
	bool is_entrace() {
		int x = settings.player_pos.pos_x;
		int y = settings.player_pos.pos_y;
		const tile_data & data = map.matrix[y][x];
		if (data.level == 2) { return true; }
		return false;
	}

	/*
	@brief This function is used to check which entrance has been entered
	@param void
	@return int
	*/
	int show_entrance_id() {
		int x = settings.player_pos.pos_x;
		int y = settings.player_pos.pos_y;
		const tile_data & data = map.matrix[y][x];
		return data.id;
	}

	/*
	@brief This function is used to check wether an object from an certain range has collision from the player position
	@param _side: &const char, level: &const int, range: &const int
	@return bool
	*/
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

	/*
	@brief This function is used to check wether an object from an certain range has collision from the enemy position
	@param _side: &const char, level: &const int, range: &const int
	@return bool
	*/
	bool is_collision2(const char & _side, const int & level, const int & range = 1) {
		int x = 0, y = 0;
		switch (_side) {
		case 'l':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x - range;
			break;
		case 'r':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x + range;
			break;
		case 'u':
			y = boss.pos.pos_y - range;
			x = boss.pos.pos_x;
			break;
		case 'd':
			y = boss.pos.pos_y + range;
			x = boss.pos.pos_x;
			break;
		};

		const tile_data & data = map.matrix[y][x];
		if (data.level == level) {
			return true;
		}
		return false;

	}

	/*
	@brief This function is used to check wether the player weapon has collision the enemy
	@param _side: &const char, range: &const int
	@return bool
	*/
	bool enemy_is_hit(const char & _side, const int & range = 1) {
		int x = 0, y = 0;
		switch (_side) {
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

		return (x == boss.pos.pos_x && y == boss.pos.pos_y);
	
	
	}

	/*
	@brief This function is used to check wether the enemy weapon has collision the player
	@param _side: &const char, range: &const int
	@return bool
	*/
	bool player_is_hit(const char & _side, const int & range = 1) {
		int x = 0, y = 0;
		switch (_side) {
		case 'l':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x - range;
			break;
		case 'r':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x + range;
			break;
		case 'u':
			y = boss.pos.pos_y - range;
			x = boss.pos.pos_x;
			break;
		case 'd':
			y = boss.pos.pos_y + range;
			x = boss.pos.pos_x;
			break;
		};

		return (x == settings.player_pos.pos_x && y == settings.player_pos.pos_y);


	}

	/*
	@brief This function is used to draw the player weapon
	@param range: &const int
	@return void
	*/
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
		window.draw(player);
		window.draw(weapon);
		window.draw(_boss);
		window.display();
	}

	/*
	@brief This function is used to draw the enemy weapon
	@param _side: &const char, range: &const int
	@return void
	*/
	void draw_enemy_weapon(const char & _side, const int & range) {
		int x = 0;
		int y = 0;
		switch (_side) {
		case 'l':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x - range;
			break;
		case 'r':
			y = boss.pos.pos_y;
			x = boss.pos.pos_x + range;
			break;
		case 'u':
			y = boss.pos.pos_y - range;
			x = boss.pos.pos_x;
			break;
		case 'd':
			y = boss.pos.pos_y + range;
			x = boss.pos.pos_x;
			break;
		};

		sf::Vector2f & weapon_pos = map.matrix[y][x].pos;
		boss_weapon.setPosition(weapon_pos);

		map.clear();
		map.redraw();
		window.draw(_boss);
		window.draw(boss_weapon);
		window.draw(player);
		window.display();
	}

	/*
	@brief This function is used by the enemy to attack the player
	@param void
	@return void
	*/
	void attack_player() {
		int x_delta = rand_range(-3, 3);
		int y_delta = rand_range(-3, 3);

		if (x_delta == 0 || y_delta == 0) { x_delta = 3; y_delta = 3; }

		int new_pos_x = settings.player_pos.pos_x + x_delta;
		int new_pos_y = settings.player_pos.pos_y + y_delta;
		if (new_pos_x < 0 || new_pos_x > COL || new_pos_y < 0 || new_pos_y > ROW) { return; }

		boss.set_pos(new_pos_x, new_pos_y);

		char r_side = check_fire_side(new_pos_x, new_pos_y);

		music.play_sfx(AUDIO + "SFX/magic_shot.ogg");

		if (is_player_hit(r_side, 10)) {
			music.play_sfx(AUDIO + "SFX/game_over.wav");
			end_game(IMAGES + "game_over.png");
		}

	}

	/*
	@brief This function is used to check if the player has hit an enemy or other object
	@param side: &const char, range: &const int
	@return bool
	*/
	bool is_target_hit(const char & side, const int & range) {
		
		for (int i = 1; i <= range; ++i) {

			if (enemy_is_hit(side, i) && enemy_alive) { --boss.health; attack_player(); _place(); return true; }
			if (is_collision(side, 1, i)) { return true; }
			draw_weapon(i);
		}
		return false;
	}

	/*
	@brief This function is used to check if the enmy has hit the player or other object
	@param side: &const char, range: &const int
	@return bool
	*/
	bool is_player_hit(const char & side, const int & range) {

		for (int i = 1; i <= range; ++i) {

			if (player_is_hit(side, i)) { return true; }
			if (is_collision2(side, 1, i)) { return false; }
			draw_enemy_weapon(side, i);
		}
		return false;
	}

	/*
	@brief This function is used by the enemy to fire his weapon
	@param void
	@return void
	*/
	void fire_weapon() {
		weapon_texture.loadFromFile(TEXTURES + settings.weapon_sprite_map + "/" + _side_ + settings.weapon_sprite_file_extention);
		weapon.setTexture(weapon_texture);

		if ( is_target_hit(side, 10) ) {
			music.play_sfx(AUDIO + "SFX/enemy_hit.wav");
		}

	}

	/*
	@brief This function is used to generate a random nummer between a range
	@param void
	@return void
	*/
	int rand_range(const int & min, const int & max) {
		int output = min + (std::rand() % static_cast<int>(max - min + 1));
		return output;
	}

	/*
	@brief This function is used to decide which side the enemy has to fire his weapon
	@param pos_x: &const int, pos_y: &const int
	@return char
	*/
	char check_fire_side(const int & pos_x, const int & pos_y) {
		int player_pos_x = settings.player_pos.pos_x;
		int player_pos_y = settings.player_pos.pos_y;

		if (pos_x == player_pos_x) {
			if (pos_y < player_pos_y) { return 'd'; }
			if (pos_y > player_pos_y) { return 'u'; }
		}

		if (pos_y == player_pos_y) {
			if (pos_x < player_pos_x) { return 'r'; }
			if (pos_x > player_pos_x) { return 'l'; }
		}

		if (pos_x < player_pos_x ) { return 'r'; }
		if (pos_x > player_pos_x ) { return 'l'; }

		return 'd';
	}

	/*
	@brief This function is used to start the player movement with collsion and enemy movement
	@param void
	@return void
	*/
	void start() {

		if (enemy_alive) {

			if (HAS_ENEMY) {
				if (settings.player_pos.pos_x == boss.pos.pos_x && settings.player_pos.pos_y == boss.pos.pos_y) { music.play_sfx(AUDIO + "SFX/game_over.wav"); end_game(IMAGES + "game_over.png");}

				if (boss.health <= 0) { enemy_alive = false; music.play_sfx(AUDIO + "SFX/boss_dying.wav"); end_game(IMAGES + "victory.png"); }

				if (!enemy_spotted) {
					if (boss.player_detected(settings.player_pos)) { enemy_spotted = true; }
				}
				else {
					if (boss_move_counter <= 0) {
						attack_player();
						boss_move_counter = 10;
					}
				}

			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move_up();
			--boss_move_counter;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move_down();
			--boss_move_counter;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			move_left();
			--boss_move_counter;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move_right();
			--boss_move_counter;
		}
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
			if (CAN_SHOOT) {
				music.play_sfx(AUDIO + "SFX/shoot.wav");
				_place();
				fire_weapon();
			}
		}

	}

	/*
	@brief This function is used to start the player movement with collsion and enemy movement. it also returns the action that has currently been taken
	@param void
	@return char
	*/
	char start_indicator() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move_up();
			return 'u';
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move_down();
			return 'd';
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			move_left();
			return 'l';
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move_right();
			return 'r';
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (CAN_SHOOT) {
				music.play_sfx(AUDIO + "SFX/shoot.wav");
				fire_weapon();
				return 's';
			}
		}

	}

	/*
	@brief This function is used to get the player position
	@param void
	@return tile_coordinate
	*/
	tile_coordinate & get_player_pos(){
		return settings.player_pos;
	}

	/*
	@brief This function is used to set the player position
	@param x: &const int, y:&const int
	@return void
	*/
	void set_player_pos(const int & x, const int & y) {
		settings.player_pos.pos_x = x;
		settings.player_pos.pos_y = y;
	}

};



#endif // PLAYER_DATA_HPP

