#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "..//Assets/Scripts/Control/player_data.hpp"
#include "..//Assets/Scripts/Control/game_map.hpp"
#include "..//Settings/folder_paths.hpp"
#include <SFML/Graphics.hpp>

class tutorial {
private:
	sf::RenderWindow & window;
	camera & cam;
	player_data<20, 20> & oof_inside;
	game_map<20, 20> & tut_map;
	player_data<60, 60, true, true> & oof_outside;
	game_map<60, 60> & map;

	sf::Texture texture_subs;
	sf::Sprite sprite_subs;

	sf::Texture texture_ossas;
	sf::Sprite sprite_ossas;
	
public:
	tutorial( 
		sf::RenderWindow & window,
		camera & cam,
		player_data<20, 20> & oof_inside,
		game_map<20, 20> & tut_map,
		player_data<60, 60, true, true> & oof_outside,
		game_map<60, 60> & map
	):
		window(window),
		cam(cam),
		oof_inside(oof_inside),
		tut_map(tut_map),
		oof_outside(oof_outside),
		map(map)
	{
		texture_subs.setRepeated(false);
		texture_ossas.setRepeated(false);
		texture_ossas.loadFromFile(TEXTURES + "green.png");

		sprite_subs.setPosition(sf::Vector2f{ 0, 20 * 16 });
		sprite_ossas.setTexture(texture_ossas);
	}

	void calculate_sub_pos() {
		tile_coordinate & pos = oof_outside.get_player_pos();
		sprite_subs.setPosition(sf::Vector2f{ ((float)pos.pos_x - 13) * 16, ((float)pos.pos_y - 10) * 16 });
	}

	void show_sub_title(char * path, bool inside = true) {
		if (inside) {
			oof_inside._pack();
		} else {
			calculate_sub_pos();
			oof_outside._pack();
			window.draw(sprite_ossas);
		}
		
		texture_subs.loadFromFile(IMAGES + path);
		sprite_subs.setTexture(texture_subs);
		window.draw(sprite_subs);
		window.display();
		sf::sleep(sf::milliseconds(2500));
	}

	void show_instruction(char * path) {
		calculate_sub_pos();
		oof_outside._pack();
		window.draw(sprite_ossas);

		texture_subs.loadFromFile(IMAGES + path);
		sprite_subs.setTexture(texture_subs);
		window.draw(sprite_subs);
		window.display();
		sf::sleep(sf::milliseconds(500));
	}

	void walk_pattern(const std::vector<char> & pattern, bool inside = true) {
		if (inside) {
			for (const char dir : pattern) { oof_inside.move_hard(dir); }
		} else { 
			for (const char dir : pattern) { oof_outside.move_hard(dir); } 
		}
	
	}

	
	void start() {
		oof_inside._pack();
		window.display();
		sf::sleep(sf::milliseconds(1000));

		show_sub_title("Tutorial/ossastext1.png");
		show_sub_title("Tutorial/ossastext2.png");
		show_sub_title("Tutorial/ossastext3.png");
		
		walk_pattern(std::vector<char> { 
			'd', 'd', 'd', 'd', 
			'r', 'r', 'r', 'r', 'r',
			'd', 'd', 'd', 'd', 'd', 'd', 'd',
			'r', 'r', 'r', 'r', 'r', 'r',
			'd', 'd'
		});

		window.clear();

		calculate_sub_pos();
		sprite_ossas.setPosition(sf::Vector2f{ 14 * 16, 42 * 16 }  );

		cam.init();
		oof_outside._place();
		oof_outside.move_hard('r');


		oof_outside._pack();
		window.draw(sprite_ossas);
		window.display();

		show_sub_title("Tutorial/ossasoutside1.png", false);
		show_sub_title("Tutorial/ossasoutside2.png", false);
		show_sub_title("Tutorial/ossasoutside3.png", false);
		show_sub_title("Tutorial/ossasoutside4.png", false);
		show_sub_title("Tutorial/ossasoutside5.png", false);
		show_sub_title("Tutorial/ossasoutside6.png", false);
		show_sub_title("Tutorial/ossasoutside7.png", false);
		show_sub_title("Tutorial/ossasoutside8.png", false);
		show_sub_title("Tutorial/ossasoutside9.png", false);
		show_sub_title("Tutorial/ossasoutside10.png", false);
		show_instruction("Tutorial/tut1.png");

		int up_count = 0;
		int down_count = 0;
		int left_count = 0;
		int right_count = 0;

		for(;;) {
			char key_pressed = oof_outside.start_indicator();

			if (up_count > 0  && down_count > 0 && left_count > 0 && right_count > 0) {
				show_sub_title("Tutorial/tut2.png", false);
				show_sub_title("Tutorial/tut4.png", false);
				show_instruction("Tutorial/tut5.png");
				for (;;) {
					char key_pressed2 = oof_outside.start_indicator();
					if (key_pressed2 == 's') {
						show_sub_title("Tutorial/tut5success.png", false);
						show_sub_title("Tutorial/tut6.png", false);
						show_sub_title("Tutorial/tut7.png", false);
						show_sub_title("Tutorial/tut8.png", false);
						return;
					}

				}
			
			}

			switch (key_pressed)
			{
			case 'u':
				++up_count;
				break;
			case 'd':
				++down_count;
				break;
			case 'l':
				++left_count;
				break;
			case 'r':
				++right_count;
				break;
			};
			
	
		}


	}





};




#endif // !TUTORIAL_HPP

