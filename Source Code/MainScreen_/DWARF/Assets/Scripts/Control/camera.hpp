#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class camera {
private:	
	sf::RenderWindow & window;
	const sf::Vector2f & pos;
	
	sf::View viewport;

public: 
	const sf::Vector2f & size;

	camera(
		sf::RenderWindow & window,
		const sf::Vector2f & size,
		const sf::Vector2f & pos = {0,0}
	):
		window(window),
		size(size),
		pos(pos)
	{}

	void init() {
		viewport.setSize(size);
		viewport.setCenter(pos);
		window.setView(viewport);
	}

	void set_center(const sf::Vector2f & new_center) {
		viewport.setCenter(new_center);
		window.setView(viewport);
	}


};



#endif //CAMERA_HPP
