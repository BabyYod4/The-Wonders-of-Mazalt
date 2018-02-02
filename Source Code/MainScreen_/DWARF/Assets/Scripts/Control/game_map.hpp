/*
@page game_map.hpp
@author Arsalan Anwari
@brief This file contains the map render control class
*/

#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <Assets/Scripts/Entity/map_tile_matrix.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

/*
@brief This class is responsible for the map rendering logic
@details a template is used to determine the size of an 2d std::array
*/
template< int ROW, int COL>
class game_map{
private:
	map_tile_matrix<ROW, COL> map_data;
	sf::RenderWindow & window;
	sf::Sprite map;
	sf::Texture texture;
public:
	std::array< std::array< tile_data, COL>, ROW > matrix;

	game_map(sf::RenderWindow & window, const settings::tile_matrix::options & settings) :
		map_data(settings.data_id, settings.entrance_id, settings.data_folder, settings.sprite_folder, settings.tile_size, settings.file_name_prefix, settings.file_extention),
		matrix( map_data.get() ),
		window(window)
	{
		texture.loadFromFile(TEXTURES + settings.sprite_folder + "/" + settings.file_name_prefix + settings.file_extention);
		texture.setRepeated(false);
		map.setTexture(texture);
		map.setPosition(sf::Vector2f{ 0,0 });
	}

	/*
	@brief This function is used as a getter to retrive the 2d struct array
	@param void
	@return std::array< std::array< tile_data, COL>, ROW >
	*/
	std::array< std::array< tile_data, COL>, ROW > get() { return matrix; }

	/*
	@brief This function is used to update the map in display data but not to not draw it on the window
	@param void
	@return void
	*/
	void redraw() {
		window.clear();
		window.draw(map);
	}

	/*
	@brief This function is used to update the map in display data and to draw it on the window
	@param void 
	@return void
	*/
	void draw() {
		window.clear();
		window.draw(map);
		window.display();
	}

	/*
	@brief This function is used to clear the display data
	@param void 
	@return void
	*/
	void clear() {
		window.clear();
	}

	/*
	@brief This function is used to draw what is currently in display data
	@param void
	@return void
	*/
	void display() {
		window.display();
	}



};


#endif //GAME_MAP_HPP
