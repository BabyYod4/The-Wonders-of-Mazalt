#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include <SFML/Audio.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <string>

class music_player {

protected:


public:

	sf::Music music;
	sf::Sound sfx;
	sf::SoundBuffer buffer;
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
		sfx.setLoop(false);
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

	void play_sfx(const std::string & new_track_path) {
		buffer.loadFromFile(new_track_path);
		sfx.setBuffer(buffer);
		sfx.play();
	}

	bool getStatus() {
		return active;
	}

};

#endif //MUSIC_PLAYER



