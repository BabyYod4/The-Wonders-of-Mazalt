#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <SFML/System/Vector2.hpp>
#include <Assets\Scripts\ADT\tile_coordinate.hpp>

namespace settings {

	namespace music_player {

		struct options {
			const std::string song;
			float volume = 100;
			float pitch = 1.0;
			bool loop = true;
		};

	};

	namespace tile_matrix {

		struct options {
			int data_id;
			std::string data_folder;
			std::string sprite_folder;
			sf::Vector2i tile_size;
			std::string file_name_prefix;
			std::string file_extention;
		};

	};

	namespace animations {

		namespace text_fade {

			struct options {
				int alpha_value;
				std::string background_path;
				std::string text_path;
				sf::Vector2f background_pos;
				sf::Vector2f text_pos;
				sf::Vector2f background_scale = sf::Vector2f(1, 1);
				sf::Vector2f text_scale = sf::Vector2f(1, 1);
			};

		};

	};

	namespace player {
	
		struct options {
			tile_coordinate player_pos;
			std::string player_sprite_map;
			std::string player_sprite_file_extention;
			std::string weapon_sprite_map = "";
			std::string weapon_sprite_file_extention = "";
		};
	
	
	};

};


#endif //SETTINGS_HPP

