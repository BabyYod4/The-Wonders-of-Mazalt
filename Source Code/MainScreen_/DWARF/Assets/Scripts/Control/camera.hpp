/*
@file camera.hpp
@author Arsalan Anwari
@author Leon Zhang
@brief This file contains a control class named camera
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

/*
@brief This class is responsible for the camera movement logic by the player
@details A viewport is used, with a certain size en start position
*/
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

	/*
		@brief This function is used to initialize settings of the viewport with the class parameters
		@param void
		@return void
	*/
	void init() {
		viewport.setSize(size);
		viewport.setCenter(pos);
		window.setView(viewport);
	}

	/*
	@brief This function is used to redefine what the center point of the viewport is with a given value
	@param new_center: &const sf::Vector2f
	@return void
	*/
	void set_center(const sf::Vector2f & new_center) {
		viewport.setCenter(new_center);
		window.setView(viewport);
	}


};



#endif //CAMERA_HPP
