#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

class GameScreen
{
public:
	GameScreen(Game& game, sf::Font font);
	~GameScreen();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Font m_agentOrange;
	sf::Font m_font;
	sf::Time m_cumulativeTime;

	sf::Sprite m_trackSprite;
	sf::Texture m_trackTexture;

	sf::RectangleShape rec;
	sf::View follow;
};
#endif //GameScreen