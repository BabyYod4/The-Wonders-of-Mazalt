#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <Assets/Scripts/Boundary/map_tile.hpp>
#include <Assets/Scripts/Entity/map_tile_matrix.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

template< int ROW, int COL>
class game_map {
private:
	map_tile_matrix<ROW, COL> map_data;
	std::array< std::array< tile_data, COL>, ROW > matrix;
	sf::RenderWindow & window;
	map_tile tile;

public:
	game_map(sf::RenderWindow & window, const settings::tile_matrix::options & settings) :
		map_data(settings.data_folder, settings.sprite_folder, settings.tile_size, settings.file_name_prefix, settings.file_extention),
		matrix( map_data.get() ),
		window(window),
		tile(window)
	{}

	void draw() {
		window.clear();
		for (auto & row : matrix) { for (auto & elem : row) { tile.draw(elem); } }
		window.display();
	}

	void clear() {
		window.clear();
	}


	void remove_tile(const sf::Vector2i & tile_pos) {
		tile.remove(matrix[tile_pos.y][tile_pos.x]);
	}

	void remove_tile(tile_data & t) {
		tile.remove(t);
	}

	void redraw_tile(const sf::Vector2i & tile_pos) {
		tile.draw(matrix[tile_pos.y][tile_pos.x]);
	}

	void redraw_tile(tile_data & t) {
		tile.draw(t);
	}
	
};


#endif //GAME_MAP_HPP
