#pragma once
#ifndef PAUSE
#define PAUSE	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;
class Player;
//class Pause;
class Pause
{
public:
	Pause(Game& Game, sf::Font font);
	~Pause();
	void update(sf::Time deltaTime, Xbox360Controller& controller, Player & player);
	void render(sf::RenderWindow& window);
	bool close = false;

private:
	Game *m_game;//pointer to games class 
	sf::Time m_cumulativeTime;//the time 
	sf::Font m_font;
	sf::Font m_adventure;
	sf::Window m_window;
	sf::Sprite m_mainMe;
	sf::Texture m_buttonTexture;
	sf::Sprite m_buttonOne;
	sf::Sprite m_buttonTwo;
	sf::Sprite m_buttonThree;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Sprite m_selectBack;
	sf::Sprite m_selectOptions;
	sf::Sprite m_selectExit;
	sf::Texture m_selectTexture;

	sf::Text m_resume;
	sf::Text m_options;
	sf::Text m_exit;
	sf::Text m_paused;



	sf::View pause;

	bool buttonOneSelected = false;
	bool buttonTwoSelected = false;
	bool buttonThreeSelected = false;
	bool buttonFourSelected = false;
	int buttonCounter = 0;
	//variable for single press
	bool pressed = false;
	int alpha;
	int alpha2;
	bool alphaCount = true;
	//	bool alpha = 0;
	bool flip;
	bool animaIn = true;
	bool animaOut = false;
	bool selected = false;
	bool exit = false;


	Options *m_optionScreen;
};
#endif // !

