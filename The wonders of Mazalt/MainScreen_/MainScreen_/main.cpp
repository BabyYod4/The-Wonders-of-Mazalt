#include <iostream>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Settings\folder_paths.hpp>
#include <Assets\Animations\text_fade\text_fade.hpp>
#include <Assets\Scripts\Control\music_player.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <Assets\Scripts\Boundary\map_tile.hpp>
#include <Assets\Scripts\Control\game_map.hpp>
#include <Assets\STD\include.hpp>


bool no_condition() {
	return false;
}

int main(void) {
	sf::RenderWindow window{ sf::VideoMode{ 640, 360 }, "Wonders of Mazalt" };
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);
	sf::Event event;

	text_fade intro(
		settings::animations::text_fade::options{
			100,
			(UI + "main_screen/mainscreen_.png"),
			(UI + "main_screen/Press.png"),
			sf::Vector2f(0 , 0),
			sf::Vector2f(640 / 4, 250),
		}
	);

	music_player player(
		settings::music_player::options{
			AUDIO + "music/opening.ogg" , 50, 1.0, true
		}
	);

	game_map<20, 20> level(
		window,
		settings::tile_matrix::options{
			std::string("desert/data.csv"), // data map
			std::string("desert"),          // naam sprite map
			sf::Vector2i{ 16, 16 },         // tegel grote
			std::string("desert"),           // spritenaam prefix
			std::string(".png")				// optioneel file extention
		}
	);

	std::vector<state> states = {
		state{
			0, 1,
			std::string("play_intro_music"),
			std::vector<_event_>{ _event_{ no_condition } },
			[&player]()->void { player.play();  }
		},

		state{
			1, 1,
			std::string("wait_for_enter_key"),
			std::vector<_event_>{ _event_{ []()->bool { return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);  }, 2 } },
			[&intro, &window]()->void { intro.fade(window);  }
		},

		
		state{
			2, 3,
			std::string("change_music"),
			std::vector<_event_>{ _event_{ no_condition } },
		},

		state{
			3, 4,
			std::string("show_map"),
			std::vector<_event_>{ _event_{ no_condition } },
			[&level]()->void { level.draw();  }
		},

		state{
			4, 4,
			std::string("idle"),
			std::vector<_event_>{ _event_{ no_condition } },
			[]()->void { std::cout << "in idle mode\n"; }
		},



	};

	std::vector< std::string > special_states{
		std::string("change_music")
	};

	game_state_engine engine(window, states, special_states);

	while (window.isOpen()) {

		std::string state = engine.check_state();
		if (state == std::string("change_music")) { 
			player.stop();
			player.change_track(AUDIO + "Music/Field.ogg"); 
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

	


	}

	return 0;
}