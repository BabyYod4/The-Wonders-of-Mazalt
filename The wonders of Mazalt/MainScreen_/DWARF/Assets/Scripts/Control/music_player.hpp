#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include <SFML/Audio.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <string>

class music_player {

protected:


public:

	sf::Music music;
	const settings::music_player::options & settings;
	bool active = false;

	music_player(const settings::music_player::options & settings) :
		settings(settings)
	{
		init();
	}

	void init() {
		music.openFromFile(settings.song);
		music.setVolume(settings.volume);
		music.setLoop(settings.loop);
	}

	void play() {
		active = true;
		music.play();
	}


	void resume() {
		active = true;
		play();
	}

	void pause() {
		music.pause();
		active = false;
	}

	void stop() {
		music.stop();
		active = false;
	}

	void change_track(const std::string & new_track_path) {
		stop();
		music.openFromFile(new_track_path);
		play();
	
	}

	bool getStatus() {
		return active;
	}

};

#endif //MUSIC_PLAYER



