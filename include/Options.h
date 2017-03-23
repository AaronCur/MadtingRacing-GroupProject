#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"
#include "SFML\Audio.hpp"
class Game;

class Options
{
public:
	Options(Game& Game, sf::Font font);
	~Options();
	void setPosition();
	void buttonUpdate();
	void update(sf::Time deltaTime, Xbox360Controller &controller);
	void render(sf::RenderWindow& window);
	void increaseVolume();
	void decreaseVolume();

private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Font m_comicSans;
	sf::Texture m_buttonTexture;
	sf::Texture m_arrowTexture;
	sf::Texture m_checkBoxTexture[2];
	sf::Texture m_sliderTexture;
	sf::Sprite m_buttonSprite[2];
	sf::Sprite m_songSprite[3];
	sf::Texture m_songTextures[3];
	sf::Sprite m_arrowSprite;
	sf::Texture m_markerTexture;
	sf::Sprite m_markerSprite;
	sf::Sprite m_sliderSprite;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	sf::Font m_font;
	sf::Font m_meatLoaf;
	sf::Text m_helpText;
	sf::Text m_highscoreText;
	sf::Text m_songtxt;;
	sf::Text m_optionsTxt;
	sf::Music song1;
	sf::Music song2;
	sf::Music song3;
	sf::Text currentSongtext;
	float volume = 50.0f;
	bool ready = false;
	int value = 370;
	bool onHelp = true;
	bool onHighScores = false;
	bool onSong1 = false;
	bool onSong2 = false;
	bool onSong3 = false;
	bool onSlider = false;

	sf::Shader m_shader;
	float updateShader = 0;
	sf::Texture m_blankTexture;
	sf::Sprite m_blankSprite;

	bool onMute = false;
	bool changed = false;
	sf::Sprite m_muteSprite;
	sf::Texture m_muteTexture[2];

	sf::Sound buttonPress;
	sf::SoundBuffer buffer;
};
#endif // !Options
