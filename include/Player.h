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
	Player(Game& Game, sf::Font font);
	~Player();
	void update(sf::Time deltaTime, Xbox360Controller& controller, CarSelect & CarSelect);
	void render(sf::RenderWindow& window);
	void carDraw(sf::RenderWindow& window);
	void offTrackDetection();
	void move();
	double m_angle;
	double m_currentAngle;
	bool start = false;
	sf::RectangleShape player;
	sf::Sprite carSprite;

	double m_carOneSpeedMax = 1.8;
	double m_carTwoSpeedMax = 0.6;
	double m_carThreeSpeedMax = 0.9;

	double m_carOneHandling = 0.2;
	double m_carTwoHandling = 0.4;
	double m_carThreeHandling = 0.6;

	double m_carOneBraking = 0.1;
	double m_carTwoBraking = 0.2;
	double m_carThreeBraking = 0.1;

private:
	bool skiding = false;
	sf::CircleShape circle;
	sf::CircleShape halfwayCircle;
	sf::CircleShape lapCircle;
	Game *m_game;
	sf::Font m_font;
	sf::Texture m_trackTexture;
	sf::Sprite m_trackSprite;
	sf::Texture m_carFireTexture;
	sf::Sprite m_carFireSprite;

	sf::RenderTexture m_renderTexture;
	sf::Image image;

	sf::Texture m_skidTexture;
	sf::Sprite m_skidSprite[1000];

	sf::Texture mapSprite;
	sf::Sprite mapTiles[16];

	sf::Text noOfLaps;
    sf::Text lapText;
	sf::Text countdownTxt;
	sf::Time countdownTime;
	sf::Time currentTime;
	sf::Text lapOneText;
	sf::Text lapTwoText;
	sf::Text lapThreeText;
	sf::Font m_meatLoaf;
	double m_acceleration = 0.1;
	double m_friction = 0.02;
	double m_maxSpeed = 1;
	double m_gear = 1;

	double m_handlingUpgrade = 0;
	double m_brakingUpgrade = 0;

	int minute = 0;
	int laps = 0;
	double static const RAD_TO_DEG;
	double static const DEG_TO_RAD;
	bool reset = false;
	int countdown = 3;
	double distanceLeft = 0;
	double distanceRight = 0;

	double m_speed = 0;
	sf::Time skidTime;
	bool topRight = false;
	bool topLeft = false;
	bool bottomLeft = false;
	bool bottomRight = false;

	int counter = 0;

	bool gearChanged = false;

	double fireCount = 0;

	double firstLap = 0;
	double secondLap = 0;
	double thridLap = 0;
	sf::Vector2f m_centre;
	sf::Texture m_carSpriteSheet;

	bool found = false;
	bool halfway = false;
	bool lap = false;
	bool lap2 = false;
	bool lap3 = false;
	double dt = 0;
	sf::Time m_time;

	sf::View follow;
};
#endif // !Player