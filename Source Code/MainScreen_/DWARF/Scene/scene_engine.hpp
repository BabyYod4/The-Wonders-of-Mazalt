#ifndef SCENE_ENGINE
#define SCENE_ENGINE

#include <Assets/Scripts/ADT/scene.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class scene_engine {
private:
	sf::RenderWindow & window;
	std::vector<_scene> & scenes;
	sf::Texture texture;
	sf::Sprite scene;
public:
	scene_engine(sf::RenderWindow & window, std::vector<_scene> & scenes):
		window(window),
		scenes(scenes)
	{}


	void start() {
		for (auto & s : scenes) {
			window.clear();
			texture.loadFromFile(s.scene_image_name);
			scene.setTexture(texture);
			window.draw(scene);
			window.display();
			sf::sleep(sf::milliseconds(s.delay_ms));
		}
	}

};


#endif // !SCENE_ENGINE

