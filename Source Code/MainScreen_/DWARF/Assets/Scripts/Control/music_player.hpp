/*
@file music_player.hpp
@author Arsalan Anwari
@author Diego Nijboer
@brief This file contains the music player control class
*/

#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include <SFML/Audio.hpp>
#include <Assets\Scripts\ADT\settings.hpp>
#include <string>

/*
@brief This class is responsible for the music playing logic
@details Both sound effect and background music can be player together 
*/
class music_player {

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

	/*
	@brief This function is used as an initialization process to set the music player settings
	@param void
	@return void
	*/
	void init() {
		music.openFromFile(settings.song);
		music.setVolume(settings.volume);
		music.setLoop(settings.loop);
		sfx.setLoop(false);
	}

	/*
	@brief This function is used to play background music
	@param void 
	@return void 
	*/
	void play() {
		active = true;
		music.play();
	}

	/*
	@brief This function is used to resume background music
	@param void
	@return void
	*/
	void resume() {
		active = true;
		play();
	}

	/*
	@brief This function is used to pause background music
	@param void
	@return void
	*/
	void pause() {
		music.pause();
		active = false;
	}

	/*
	@brief This function is used stop background music
	@param void
	@return void
	*/
	void stop() {
		music.stop();
		active = false;
	}

	/*
	@brief This function is used to change the track of the background music
	@param new_track_path: &std::string
	@return void
	*/
	void change_track(const std::string & new_track_path) {
		stop();
		music.openFromFile(new_track_path);
		play();
	}

	/*
	@brief This function is used to play a sound effect along side the background music
	@param new_track_path: &std::string
	@return void
	*/
	void play_sfx(const std::string & new_track_path) {
		buffer.loadFromFile(new_track_path);
		sfx.setBuffer(buffer);
		sfx.play();
	}

	/*
	@brief This function is used to get the status of the music player
	@param void
	@return bool
	*/
	bool getStatus() {
		return active;
	}

};

#endif //MUSIC_PLAYER



