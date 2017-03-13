#include "Player.h"
#include <math.h>
double const Player::DEG_TO_RAD = 3.14 * 180.0f;
double const Player::RAD_TO_DEG = 57.295779513;

Player::Player(Game & game) :
	m_game(&game),

	m_angle(0)
	
{
	player.setSize(sf::Vector2f(40, 20));
	player.setFillColor(sf::Color::Red);
	player.setPosition(500, 325);
	player.setOrigin(20, 10);
	if (!m_trackTexture.loadFromFile("track3.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	
	if (!m_carSpriteSheet.loadFromFile("CarSprite.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	m_trackSprite.setTexture(m_trackTexture);
	m_trackSprite.setPosition(0, 0);

	carSprite.setTexture(m_carSpriteSheet);
	sf::IntRect carOneRect(15, 13, 73, 129);
	carSprite.setTextureRect(carOneRect);
	carSprite.setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	carSprite.rotate(270);
	carSprite.setPosition(player.getPosition().x, player.getPosition().y);

}

Player::~Player()
{

}
void Player::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(m_trackSprite);
	window.draw(player);
	window.draw(carSprite);
	window.display();

}

void Player::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	m_time += deltaTime;
	dt = m_time.asSeconds();
	double speed = 0;
	if (controller.m_currentState.LeftThumbStick.y != 0)
	{
		m_angle = atan(controller.m_currentState.LeftThumbStick.x / controller.m_currentState.LeftThumbStick.y);
		m_angle = m_angle * RAD_TO_DEG;
	}
	carSprite.setPosition(player.getPosition().x, player.getPosition().y);
	//carSprite.rotate(player.getRotation());
	
		
			
		
		
		if (controller.m_currentState.LeftThumbStick.x <= 100 && controller.m_currentState.LeftThumbStick.x >= 0 && controller.m_currentState.LeftThumbStick.y >= -100 && controller.m_currentState.LeftThumbStick.y <= 0)
		{
			topRight = true;
			topLeft = false;
			bottomRight = false;
			bottomLeft = false;
		}
		if (controller.m_currentState.LeftThumbStick.x >= -100 && controller.m_currentState.LeftThumbStick.x <= 0 && controller.m_currentState.LeftThumbStick.y >= -100 && controller.m_currentState.LeftThumbStick.y <= 0)
		{
			topLeft = true;
			topRight = false;
			bottomRight = false;
			bottomLeft = false;
		}
		if (controller.m_currentState.LeftThumbStick.x <= 100 && controller.m_currentState.LeftThumbStick.x >= 0 && controller.m_currentState.LeftThumbStick.y <= 100 && controller.m_currentState.LeftThumbStick.y >= 0)
		{
			bottomRight = true;
			topLeft = false;
			topRight = false;
			bottomLeft = false;
		}
		if (controller.m_currentState.LeftThumbStick.x >= -100 && controller.m_currentState.LeftThumbStick.x <= 0 && controller.m_currentState.LeftThumbStick.y <= 100 && controller.m_currentState.LeftThumbStick.y >= 0)
		{
			bottomLeft = true;
			topLeft = false;
			bottomRight = false;
			topRight = false;
		}
		if (topLeft == true)
		{
			m_angle = 270 - m_angle;
		}
		if (topRight == true)
		{
			m_angle = 270 - m_angle;
		}
		if (bottomLeft == true)
		{
			m_angle = 90 - m_angle;
		}
		if(bottomRight == true)
		{
			m_angle = 90 - m_angle;
		}
		distanceRight = m_angle - player.getRotation();
		distanceLeft = player.getRotation() - m_angle;

		if (distanceRight < 0)
		{
			distanceRight = distanceRight + 360;
		}
		if (distanceLeft < 0)
		{
			distanceLeft = distanceLeft + 360;
		}
	
			/*if (player.getRotation() <= (m_angle + 5) && player.getRotation() >= (m_angle - 5))
			{
				player.rotate(0);
			}
			else if (player.getRotation() < m_angle)
			{				
					player.rotate(1);			
			}
			else if (player.getRotation() > m_angle)
			{						
					player.rotate(-1);
			}*/
		if (player.getRotation() <= (m_angle + 5) && player.getRotation() >= (m_angle - 5))
		{
			player.rotate(0);
		}
		else if (distanceRight > distanceLeft)
		{
			if (m_speed != 0)
			{
				if (controller.m_currentState.X == true)
				{
					player.rotate(-4);
					carSprite.rotate(-4);
				}
				else
				{
					player.rotate(-1);
					carSprite.rotate(-1);
				}
			}
		}
		else if (distanceLeft > distanceRight)
		{
			if (m_speed != 0)
			{
				if (controller.m_currentState.X == true)
				{
					player.rotate(4);
					carSprite.rotate(4);
				}
				else
				{
					player.rotate(1);
					carSprite.rotate(1);
				}
			}
		}
		/*player.setPosition((player.getPosition().x + cos(player.getRotation() * DEG_TO_RAD) * m_speed * (dt / 1000)),
			(player.getPosition().y + sin(player.getRotation() * DEG_TO_RAD) * m_speed * (dt / 1000)));*/
		if (controller.m_currentState.RTrigger > 10)
		{
			if (m_speed < 40)
			{
				m_speed = m_speed + 0.1;
			}
		}
		if (controller.m_currentState.X == true)
		{
			if (m_speed > 0)
			{
				/*if (m_speed > -0.1 && m_speed < 0.1)
				{
					m_speed = 0;
				}*/
				m_speed = m_speed - 0.15;
			}
		}
		if (controller.m_currentState.LTrigger > 10)
		{
			if (m_speed > -1)
			{
				/*if (m_speed  -2)
				{
					m_speed = 0;
				}*/
				m_speed = m_speed - 0.1;
			}
		}
		if (controller.m_currentState.RTrigger < 10)
		{
			if (m_speed > 0)
			{
				m_speed = m_speed - 0.02;
			}
		}
		if (controller.m_currentState.LTrigger < 10)
		{
			if (m_speed < 0)
			{
				m_speed = m_speed + 0.02;
			}
		}
		if (m_speed > -0.1 && m_speed < 0.1)
		{
			m_speed = 0;
		}
		player.move(cos(player.getRotation()*3.14159265 / 180) * m_speed, sin(player.getRotation()*3.14159265 / 180)* m_speed);
		
}

void Player::move()
{

}