/*
	@file scene.hpp
	@author Arsalan Anwari
	@brief This is an abstract data type used for the scene engine
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

struct _scene {
	std::string scene_image_name;
	const int delay_ms;
};


#endif //SCENE_HPP
