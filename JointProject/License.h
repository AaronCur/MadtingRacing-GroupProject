#pragma once
#ifndef LICENSE
#define LICENSE
#include <SFML\Graphics.hpp>
#include "Game.h"


class Game;

class License
{
public:
	License(Game& Game, sf::Font font);
	~License();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void checkButtonPress();

private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Font m_comicSans;
	sf::Font m_adventure;
	sf::Font m_meatLoaf;
	sf::Text m_madTing;
	sf::Text m_racing;
	sf::Text m_continue;

	sf::Texture m_track;
	sf::Sprite m_trackSprite;
	sf::Texture m_dial;
	sf::Sprite m_dialSprite;

	int alpha;
	int alpha2;
	bool flip;
	bool m_pressed = false;

};
#endif // !License
