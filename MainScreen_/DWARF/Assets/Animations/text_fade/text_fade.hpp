#ifndef TEXT_FADE_HPP
#define TEXT_FADE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <Assets\Scripts\ADT\settings.hpp>


class text_fade {
private:
	const settings::animations::text_fade::options & opt;
	int alpha;
	sf::Texture background;
	sf::Texture text;
	sf::Sprite layer_one;
	sf::Sprite layer_two;

	void _init() {
		background.loadFromFile(opt.background_path);
		text.loadFromFile(opt.text_path);
		layer_one.setTexture(background);
		layer_two.setTexture(text);
		
		layer_one.setPosition(opt.background_pos);
		layer_two.setPosition(opt.text_pos);
		layer_one.setScale(opt.background_scale);
		layer_two.setScale(opt.text_scale);
	}

public:
	text_fade(
		const settings::animations::text_fade::options & opt
	) :
		opt(opt),
		alpha(opt.alpha_value)
	{
		_init();
	}

	void fade(sf::RenderWindow & window) {
		if (alpha < 0) { alpha = opt.alpha_value; }
		
		window.clear();
		layer_two.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(layer_one);
		window.draw(layer_two);
		window.display();
		--alpha;
	}

	


};


#endif // TEXT_FADE_HPP
