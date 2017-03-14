#pragma once
#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

class CarSelect
{
public:
	CarSelect(Game& game, sf::Font font);
	~CarSelect();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Font m_agentOrange;
	sf::Font m_font;
	sf::Time m_cumulativeTime;

	sf::Sprite m_carSelectOne;
	sf::Sprite m_carSelectOneBig;

	sf::Sprite m_carSelectTwo;
	sf::Sprite m_carSelectTwoBig;

	sf::Sprite m_selectSprite;
	sf::Texture m_selectTexture;

	sf::Texture m_carSheetTexture;
};
