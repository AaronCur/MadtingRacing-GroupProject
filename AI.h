#pragma once
#ifndef AI
#define AI	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"
#include "LevelLoader.h"
class Game;

class Ai
{
public:
	Ai(Game &game, std::vector<sf::CircleShape> & path);
	~Ai();
	void update(sf::Time deltaTime, Xbox360Controller& controller, Player & player);
	void render(sf::RenderWindow &window);
	sf::Vector2f seek();
	sf::Sprite m_aiSprite[4];
	std::vector<sf::CircleShape> & m_nodes;
private:
	float m_speed = 10.0f;
	Game *m_game;
	
	sf::Texture m_aiTexture;

	sf::Vector2f m_velocity;

	sf::Vector2f m_steering;

	sf::Vector2f m_ahead;

	sf::Vector2f m_halfAhead;

	sf::Vector2f m_position;
	sf::Vector2f m_position2;
	sf::Vector2f m_position3;
	sf::Vector2f m_position4;
	double m_rotation;
	double m_rotation2;
	double m_rotation3;
	double m_rotation4;

	int currentNode = 0;
	
	const float MAX_SEE_AHEAD = 50.0f;

	const float MAX_AVOID_FORCE = 50.0f;

	const float MAX_FORCE = 1.0f;

	float MAX_SPEED = 3.5f;

	PathData m_path;

	enum class AiBehaviour
	{
		PATH_FOLLOWING,
		SEEK_PLAYER,
		STOP,
		RETREAT
	} m_aiBehaviour;
};
#endif // !Ai

