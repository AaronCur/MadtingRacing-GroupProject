#pragma once
#ifndef PLAYER
#define PLAYER	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"
// #include <assert.h>
class Game;

class Player
{
public:
	Player(Game& Game);
	~Player();
	void update(sf::Time deltaTime, Xbox360Controller& controller, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void carDraw(sf::RenderWindow& window);
	void move();
	void offTrackDetection();
	double m_angle;
	double m_currentAngle;
	//bool collision(Player p);
	
	sf::RectangleShape player;
	sf::Sprite carSprite;
private:

	Game *m_game;
	sf::Font m_font;
	sf::Texture m_trackTexture;
	sf::Texture texture;
	sf::RenderTexture m_renderTexture;
	sf::Image image;
	sf::RectangleShape rect;
	sf::RectangleShape tempRect;
	float bottom, left, right, top;
	std::vector<std::vector<bool>> mask;
	sf::Sprite m_trackSprite;
	sf::Texture m_carFireTexture;
	sf::Sprite m_carFireSprite;
	sf::Color pixel;
	
	double m_acceleration = 0.1;
	double m_friction = 0.02;
	double m_maxSpeed = 1;
	double m_gear = 0;

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