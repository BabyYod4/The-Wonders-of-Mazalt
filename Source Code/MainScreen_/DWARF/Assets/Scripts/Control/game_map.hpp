#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <Assets/Scripts/Entity/map_tile_matrix.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

template< int ROW, int COL>
class game_map {
private:
	map_tile_matrix<ROW, COL> map_data;
	sf::RenderWindow & window;
	sf::Sprite map;
	sf::Texture texture;
public:
	std::array< std::array< tile_data, COL>, ROW > matrix;

	game_map(sf::RenderWindow & window, const settings::tile_matrix::options & settings) :
		map_data(settings.data_id, settings.data_folder, settings.sprite_folder, settings.tile_size, settings.file_name_prefix, settings.file_extention),
		matrix( map_data.get() ),
		window(window)
	{
		texture.loadFromFile(TEXTURES + settings.sprite_folder + "/" + settings.file_name_prefix + settings.file_extention);
		texture.setRepeated(false);
		map.setTexture(texture);
		map.setPosition(sf::Vector2f{ 0,0 });
	}

	std::array< std::array< tile_data, COL>, ROW > get() { return matrix; }

	void redraw() {
		window.clear();
		window.draw(map);
	}

	void draw() {
		window.clear();
		window.draw(map);
		window.display();
	}

	void clear() {
		window.clear();
	}

	void display() {
		window.display();
	}



};


#endif //GAME_MAP_HPP
