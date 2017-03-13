#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

/// <summary>
/// MiniMap author Aaron Curry
/// time taken: 9:00 - 13:50

class Game;

class GameScreen
{
public:
	GameScreen(Game& game, sf::Font font);
	~GameScreen();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Font m_comicSans;
	sf::Font m_font;
	sf::Time m_cumulativeTime;
	sf::Text m_R1;
	sf::Text m_R2;
	sf::Text m_L1;
	sf::Text m_L2;
	sf::Text m_A;
	sf::Text m_X;
	sf::Text m_Y;
	sf::Text m_B;
	sf::Text m_rightAnalog;
	sf::Text m_leftAnalog;
	sf::Text m_dPad;
	sf::Text m_start;
	sf::Text m_helpText;

	sf::Texture trackTexture;
	sf::Sprite trackSprite;
	sf::Texture miniMapTexture;
	sf::Sprite miniMapSprite;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Sprite explosion;

	sf::View gameView;
	sf::View miniMapView;

	/*sf::RenderWindow gameWindow;
	sf::RenderWindow miniMapWindow;*/

	double alpha;
	double alphaText;
};

#endif // !Help

