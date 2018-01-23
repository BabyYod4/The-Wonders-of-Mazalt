#ifndef MAP_TILE_HPP
#define MAP_TILE_HPP

#include <SFML/Graphics.hpp>
#include <Assets/Scripts/ADT/tile_data.hpp>
#include <Settings\folder_paths.hpp>

class map_tile {

private:	
	sf::RenderWindow & window;
public:
	sf::Sprite sprite;
	sf::Texture texture;
	map_tile(sf::RenderWindow & window):
		window(window)
	{}

	void draw(tile_data & data) {
		if ( !texture.loadFromFile(data.texture) ) {
			throw std::invalid_argument("Could not load one or more Texture(s)! Please check if your map_tile_matrix object is setup correctly");
		}
	
		sprite.setTexture(texture);
		sprite.setPosition( data.pos );
		window.draw(sprite);
	
	}

	void remove(tile_data & data) {
		texture.loadFromFile(data.texture + "no_texture_found.png");
		sprite.setTexture(texture);
		sprite.setPosition(data.pos);
		window.draw(sprite);

	}

};


#endif //MAP_TILE_HPP



