#include "GameScreen.h"
#include <math.h>
double const GameScreen::DEG_TO_RAD = 3.14 * 180.0f;
double const GameScreen::RAD_TO_DEG = 57.295779513;

GameScreen::GameScreen(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
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
	
	m_trackSprite.setTexture(m_trackTexture);
	m_trackSprite.setPosition(0, 0);
}

GameScreen::~GameScreen()
{

}
void GameScreen::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(m_trackSprite);
	window.draw(player);
	window.display();

}

void GameScreen::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	double speed = 0;
	if (controller.m_currentState.LeftThumbStick.y != 0)
	{
		m_angle = atan(controller.m_currentState.LeftThumbStick.x / controller.m_currentState.LeftThumbStick.y);
		m_angle = m_angle * RAD_TO_DEG;
	}
	
	
		
			
		
		
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
			player.rotate(-2);
		}
		else if (distanceLeft > distanceRight)
		{
			player.rotate(2);
		}
}

void GameScreen::move()
{

}