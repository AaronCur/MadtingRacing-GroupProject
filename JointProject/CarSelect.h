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

	bool carOnePicked = false;
	bool carTwoPicked = false;
	bool carThreePicked = false;
	
	bool carOne = false;
	bool carTwo = false;
	bool carThree = false;

	int buttonCount = 0;
private:
	Game *m_game;
	sf::Font m_agentOrange;
	sf::Font m_font;
	sf::Time m_cumulativeTime;

	sf::Sprite m_carSelectOne;
	sf::Sprite m_carSelectOneBig;

	sf::Sprite m_carSelectTwo;
	sf::Sprite m_carSelectTwoBig;

	sf::Sprite m_carSelectThree;
	sf::Sprite m_carSelectThreeBig;

	sf::Sprite m_selectSpriteCarOne;
	sf::Sprite m_selectSpriteCarTwo;
	sf::Sprite m_selectSpriteCarThree;
	sf::Texture m_selectTexture;

	sf::Texture m_carSheetTexture;

	sf::Texture m_speedTexture;
	sf::Sprite m_speedSprite[6];
	sf::Sprite m_brakeSprite[6];

	sf::Texture m_garageTexture;
	sf::Sprite m_garageSprite;

	sf::Text m_speed;
	sf::Text m_brake;

	
	int alpha = 0;
	//variable for single press
	bool pressed = false;
	bool up = true;
	bool down = false;

	bool buttonOneSelected = false;
	bool buttonTwoSelected = false;
	bool buttonThreeSelected = false;

};
