#include <iostream>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Settings\folder_paths.hpp>
#include <Assets\Animations\text_fade\text_fade.hpp>
#include <Assets\Scripts\Control\music_player.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <Assets\Scripts\Control\game_map.hpp>
#include <Assets\STD\include.hpp>
#include <Assets\Scripts\Control\player_data.hpp>
#include <Assets\Scripts\ADT\tile_coordinate.hpp>
#include <Assets\Scripts\Control\camera.hpp>
#include <Scene\scene_engine.hpp>
#include <Assets\Scripts\ADT\scene.hpp>
#include <Scene\tutorial.hpp>

int main(void) {
	sf::RenderWindow window{ sf::VideoMode{ 640, 360 }, "Wonders of Mazalt" };
	camera cam(window, sf::Vector2f{ 640, 360 });

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::Event event;

	text_fade intro(
		settings::animations::text_fade::options{
			200,
			(UI + "main_screen/mainscreen_.png"),
			(UI + "main_screen/Press.png"),
			sf::Vector2f(0 , 0),
			sf::Vector2f(640 / 4, 250),
		}
	);

	music_player music(
		settings::music_player::options{
			AUDIO + "music/Opening.ogg" , 50, 1.0, true
		}
	);



	game_map<20, 20> tut_level(
		window,
		settings::tile_matrix::options{
			14949,
			std::string("tutorial_map/data.csv"),	   // data map
			std::string("tutorial_map_data"),          // naam sprite map
			sf::Vector2i{ 16, 16 },                // tegel grote
			std::string("oofroom"),   // spritenaam prefix
			std::string(".png")				       // optioneel file extention
		}
	);

	game_map<60, 60> level(
		window,
		settings::tile_matrix::options{
			14949,
			std::string("test_map/data.csv"),	   // data map
			std::string("test_map_data"),          // naam sprite map
			sf::Vector2i{ 16, 16 },                // tegel grote
			std::string("wonders_of_mazalt_v3"),   // spritenaam prefix
			std::string(".png")				       // optioneel file extention
		}
	);

	player_data< 20, 20, true > player0(
		window,
		cam,
		tut_level,
		music,
		settings::player::options{
			tile_coordinate{ 3,5 },
			std::string("main_character"),
			std::string(".png")
		}

	);

	player_data< 60, 60 > player1(
		window, 
		cam, 
		level, 
		music,
		settings::player::options{
			tile_coordinate{12,42},
			std::string("main_character"),
			std::string(".png"),
			std::string("arrow"),
			std::string(".png")
		}
	
	);

	tutorial _tutorial(window, cam, player0, tut_level, player1, level);

	std::vector<_scene> scenes = {
		_scene{ std::string(IMAGES + "Prologue/text1.png"), 8000 },
		_scene{ std::string(IMAGES + "Prologue/scene1.png"), 4000 },
		_scene{ std::string(IMAGES + "Prologue/text2.png"), 8000 },
		_scene{ std::string(IMAGES + "Prologue/scene2.png"), 4000 },
		_scene{ std::string(IMAGES + "Prologue/text3.png"), 8000 },
		_scene{ std::string(IMAGES + "Prologue/scene3.png"), 4000 },
		_scene{ std::string(IMAGES + "Prologue/text4.png"), 8000 },
		_scene{ std::string(IMAGES + "Prologue/scene4.png"), 4000 },
		_scene{ std::string(IMAGES + "Prologue/text5.png"), 8000 },
		_scene{ std::string(IMAGES + "Prologue/scene5.png"), 4000 }
	};

	scene_engine prologue{ window, scenes };


	std::vector<state> states = {
		state{
			0, 1, 
			std::string("Play intro Music"),
			std::vector<_event_>{ _event_{} },
			[&music]()->void { music.play(); }
		},
		
		state{
			1, 1, 
			std::string("Showing intro scene"),
			std::vector<_event_>{
				_event_{
					2, std::string("Enter is pressed"),
					[]()->bool { return sf::Keyboard::isKeyPressed(sf::Keyboard::Return); }
				}
			},
			[&intro, &window]()->void { intro.fade(window); }
		},

		state{
			2, 3, 
			std::string("Showing prologue"), 
			std::vector<_event_>{ _event_{} },
			[&prologue,&music]()->void { music.change_track(AUDIO + "Music/Field.ogg");  prologue.start(); }
		},

		state{
			3, 4, 
			std::string("Starting Tutorial"), 
			std::vector<_event_>{ _event_{} },
			[&_tutorial]()->void { _tutorial.start(); }
		},

		state{
			4, 5, 
			std::string("Showing map"), 
			std::vector<_event_>{ _event_{} },
			[&level, &music, &player1, &cam]()->void { cam.init(); music.change_track(AUDIO + "Music/Field.ogg"); level.draw(); player1._place(); }
		},

		state{
			5, 5, 
			std::string("Game state"), 
			std::vector<_event_>{ _event_{} },
			[&player1]()->void { player1.start();  }
		}
	
	
	};

	game_state_engine engine{ states };

	while (window.isOpen()) {

		engine.check_state();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

	


	}

	return 0;
}