#pragma once
#ifndef HELP
#define HELP

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

class Game;

class Help
{
public:
	Help(Game& game, sf::Font font);
	~Help();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Font m_comicSans;
	sf::Text m_textMessage;
	sf::Text m_name;
	sf::Text m_by;
	sf::Texture logoTexture;
	sf::Sprite logoSprite;
	sf::Sprite explosion;

	double alpha;
};

#endif // !Help
