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
			AUDIO + "music/opening.ogg" , 50, 1.0, true
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


	player_data< 60, 60 > player1(window, cam, level, tile_coordinate{ 2, 6 });
	while (window.isOpen()) {

		/*engine.check_state();*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player1.move_up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.move_down();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player1.move_left();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player1.move_right();
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

	


	}

	return 0;
}

//#include <SFML/System.hpp>
//#include <iostream>
//
//void func()
//{
//	// this function is started when thread.launch() is called
//
//	for (int i = 0; i < 10; ++i)
//		std::cout << "I'm thread number one" << std::endl;
//}
//
//void func2()
//{
//	// this function is started when thread.launch() is called
//
//	for (int i = 0; i < 10; ++i)
//		std::cout << "I'm thread number two" << std::endl;
//}
//
//void test()
//{
//	// create a thread with func() as entry point
//	sf::Thread thread(&func);
//	sf::Thread thread2(&func2);
//	// run it
//	thread.launch();
//	thread2.launch();
//	thread.wait();
//	thread2.wait();
//
//}
//
//int main()
//{
//	test();
//
//
//
//	// the main thread continues to run...
//
//	for (int i = 0; i < 10; ++i)
//		std::cout << "I'm the main thread" << std::endl;
//
//	return 0;
//}