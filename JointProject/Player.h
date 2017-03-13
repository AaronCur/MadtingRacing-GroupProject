#ifndef PLAYER
#define PLAYER	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;

class Player
{
public:
	Player(Game& Game);
	~Player();
	void update(sf::Time deltaTime, Xbox360Controller& controller);
	void render(sf::RenderWindow& window);
	void move();
	double m_angle;
	double m_currentAngle;
	sf::RectangleShape player;
private:

	Game *m_game;
	sf::Font m_font;
	sf::Texture m_trackTexture;
	sf::Sprite m_trackSprite;
	
	double static const RAD_TO_DEG;
	double static const DEG_TO_RAD;

	double distanceLeft = 0;
	double distanceRight = 0;

	double m_speed = 0;

	bool topRight = false;
	bool topLeft = false;
	bool bottomLeft = false;
	bool bottomRight = false;

	sf::Sprite carSprite;
	sf::Texture m_carSpriteSheet;

	bool found = false;

	double dt = 0;
	sf::Time m_time;
};
#endif // !Player