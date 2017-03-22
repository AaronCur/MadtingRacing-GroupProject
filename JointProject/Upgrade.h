#pragma once
#ifndef UPGRADE
#define UPGRADE
#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"
#include <sstream>
#include <string.h>

class Game;

class Upgrade
{
public:
	Upgrade(Game& game, sf::Font font);
	~Upgrade();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Font m_comicSans;
	sf::Font m_font;
	sf::Time m_cumulativeTime;
	sf::Text m_SpeedText;
	sf::Text m_BrakeText;
	sf::Text m_HandlingText;
	sf::Text m_L2;
	sf::Text m_A;
	sf::Text m_X;
	sf::Text m_Y;
	sf::Text m_moneyText;
	sf::Text m_fundText;
	sf::Text m_priceTag;
	sf::Text m_cost;
	sf::Text m_upgradeText;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;
	// Variables for upgrade icons
	sf::Texture handlingTexture;
	sf::Sprite handlingSprite;
	sf::Texture speedGaugeTexture;
	sf::Sprite speedGaugeSprite;
	sf::Texture brakeTexture;
	sf::Sprite brakeSprite;

	sf::Texture m_selectTexture;
	sf::Sprite m_selectSprite;


	sf::Sprite explosion;

	sf::Texture m_speedTexture;
	sf::Sprite m_speedSprite[6];
	sf::Sprite m_brakeSprite[6];
	sf::Sprite m_handlingSprite[6];

	sf::Sprite carSprite;
	sf::Sprite carSprite2;
	sf::Sprite carSprite3;

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;

	sf::Texture m_carSpriteSheet;

	bool buttonOneSelected = false;
	bool buttonTwoSelected = false;
	bool buttonThreeSelected = false;
	int buttonCount = 0;

	double m_speedCount = 0;
	double m_brakeCount = 0;
	double m_handlingCount = 0;

	double m_price = 0;
	double m_funds = 420;
	std::stringstream m_priceStream;
	std::stringstream m_fundStream;

	double m_moveLimit = 340;
	double m_moveLimit2 = -400;
	double m_moveLimit3 = -400;

	bool oneSelected = true;
	bool twoSelected = false;
	bool threeSelected = false;

	// Variables for different car specs

	int m_oneSpeed = 6;
	int m_oneBrake = 1;
	int m_oneHandling = 1;

	int m_twoSpeed = 2;
	int m_twoBrake = 2;
	int m_twoHandling = 2;

	int m_threeSpeed = 3;
	int m_threeBrake = 1;
	int m_threeHandling = 2;

	bool pressed = false;
	double alpha;
	double alphaText;

	sf::Time m_time;
};

#endif // !Upgrade
