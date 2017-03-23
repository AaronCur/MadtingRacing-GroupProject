#pragma once
#ifndef ENDGAME
#define ENDGAME

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

class Game;
class Upgrade;
class Ai;

class EndGame
{
public:
	EndGame(Game& game, sf::Font font);
	~EndGame();
	void update(sf::Time dt, Xbox360Controller& controller, Player& player, Ai & ai, Upgrade & upgrade);
	void render(sf::RenderWindow& window);

private:

	Game *m_game;
	sf::Font m_font;
	sf::Time m_cumulativeTime;

	sf::Texture m_backGroundTexture;
	sf::Sprite m_backGroundSprite;

	sf::Text m_endGame;
	sf::Text m_place;
	sf::Text m_money;
	sf::Text m_firstPlace;
	sf::Text m_notFirst;
	sf::Text m_goUpgrade;

	sf::Text m_firstPlacePrize;
	sf::Text m_otherPrize;

	sf::Font m_meatLoaf;

	sf::View m_endGameView;

	int alpha;
	int alpha2;
	bool flip;

	bool playerWin = false;
	bool playerLose = false;

	bool asign = true;
};


#endif // !ENDGAME

