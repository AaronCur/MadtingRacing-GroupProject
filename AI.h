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
	Ai(Game &game, std::vector<sf::CircleShape> & path, std::vector<sf::CircleShape> & pathTwo,
		std::vector<sf::CircleShape> & pathThree, std::vector<sf::CircleShape> & pathFour);
	~Ai();
	void update(sf::Time deltaTime, Xbox360Controller& controller, Player & player);
	void render(sf::RenderWindow &window);
	sf::Vector2f seek();
	sf::Vector2f seekTwo();
	sf::Vector2f seekThree();
	sf::Vector2f seekFour();
	sf::Sprite m_aiSprite[4];
	std::vector<sf::CircleShape> & m_nodes;
	std::vector<sf::CircleShape> & m_nodesTwo;
	std::vector<sf::CircleShape> & m_nodesThree;
	std::vector<sf::CircleShape> & m_nodesFour;
	float randomFloat(float a, float b);
private:

	float m_speed = 10.0f;
	float m_speedTwo = 10.0f;
	float m_speedThree = 10.0f;
	float m_speedFour = 10.0f;
	Game *m_game;

	sf::Vector2f m_ahead;
	sf::Vector2f m_halfAhead;

	sf::Texture m_aiTexture;
	//car one 
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_steering;
	int currentNode = 0;
	double m_rotation;
	//car two 
	sf::Vector2f m_position2;
	sf::Vector2f m_velocityTwo;
	sf::Vector2f m_steeringTwo;
	int currentNodeTwo = 0;
	double m_rotation2;
	//car three
	sf::Vector2f m_position3;
	sf::Vector2f m_velocityThree;
	sf::Vector2f m_steeringThree;
	int currentNodeThree = 0;
	double m_rotation3;
	//car four 
	sf::Vector2f m_position4;
	sf::Vector2f m_velocityFour;
	sf::Vector2f m_steeringFour;
	int currentNodeFour = 0;
	double m_rotation4;


	
	const float MAX_SEE_AHEAD = 50.0f;

	const float MAX_AVOID_FORCE = 50.0f;

	const float MAX_FORCE = 4.0f;

	float MAX_SPEED = 5.6f;
	float MAX_SPEED2 = 5.6f;;
	float MAX_SPEED3 = 5.6f;;
	float MAX_SPEED4 = 5.6f;;

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

