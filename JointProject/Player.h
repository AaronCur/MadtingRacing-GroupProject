#pragma once
#ifndef PLAYER
#define PLAYER	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;
class CarSelect;

class Player
{
public:
	Player(Game & Game, CarSelect & CarSelect);
	~Player();
	void update(sf::Time deltaTime, Xbox360Controller& controller, CarSelect & CarSelect);
	void render(sf::RenderWindow& window);
	void carDraw(sf::RenderWindow& window);
	void move();
	double m_angle;
	double m_currentAngle;

	sf::RectangleShape player;
	sf::Sprite carSprite;
private:

	Game *m_game;
	sf::Font m_font;
	sf::Texture m_trackTexture;
	sf::Sprite m_trackSprite;
	sf::Texture m_carFireTexture;
	sf::Sprite m_carFireSprite;

	sf::Texture mapSprite;
	sf::Sprite mapTiles[16];

	double m_acceleration = 0.1;
	double m_friction = 0.02;
	double m_maxSpeed = 1;
	double m_gear = 0;

	double m_carOneSpeedMax;
	
	double m_carTwoSpeedMax;
	
	double m_carThreeSpeedMax;

	double static const RAD_TO_DEG;
	double static const DEG_TO_RAD;

	double distanceLeft = 0;
	double distanceRight = 0;

	double m_speed = 0;

	bool topRight = false;
	bool topLeft = false;
	bool bottomLeft = false;
	bool bottomRight = false;

	bool gearChanged = false;

	double fireCount = 0;

	sf::Vector2f m_centre;
	sf::Texture m_carSpriteSheet;

	bool found = false;

	double dt = 0;
	sf::Time m_time;



	sf::View follow;

};
#endif // !Player