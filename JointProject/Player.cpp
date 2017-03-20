#include <SFML/Graphics.hpp>
#include "Player.h"
#include <math.h>
#include <iostream>
double const Player::DEG_TO_RAD = 3.14 * 180.0f;
double const Player::RAD_TO_DEG = 57.295779513;

Player::Player(Game & game) :
	m_game(&game),
	m_angle(0)
	
	
{
	// Variables for player cube.
	player.setSize(sf::Vector2f(40, 20));
	player.setFillColor(sf::Color::Red);
	player.setPosition(200, 200);
	player.setOrigin(20, 10);

	// Load in track.
	if (!m_trackTexture.loadFromFile("bigTrack.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

 
	
	// Load in car.
	if (!m_carSpriteSheet.loadFromFile("CarSprite.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	// Load in fire.
	if (!m_carFireTexture.loadFromFile("fire.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	//follow.setCenter(500, 325);
	follow.setViewport(sf::FloatRect(0, 0, 1.5, 1.5));
	follow.setSize(1000, 650);
	follow.setCenter(player.getPosition().x , player.getPosition().y );


	m_trackSprite.setTexture(m_trackTexture);
	m_trackSprite.setPosition(0, 0);
	m_renderTexture.create(1000, 650);
	image = m_renderTexture.getTexture().copyToImage();
	

	// Set fire sprite initial position
	m_carFireSprite.setTexture(m_carFireTexture);
	m_carFireSprite.setPosition(carSprite.getPosition());

	// Car sprite variables.
	carSprite.setTexture(m_carSpriteSheet);
	sf::IntRect carOneRect(15, 13, 73, 129);
	carSprite.setTextureRect(carOneRect);
	carSprite.setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	carSprite.rotate(270);
	carSprite.setPosition(player.getPosition().x, player.getPosition().y);
	carSprite.setScale(0.3, 0.3);
	
}

Player::~Player()
{

}
void Player::render(sf::RenderWindow& window)
{
	//auto image = m_renderTexture.getTexture().copyToImage();
	//auto pixel = image.getPixel(follow.getCenter().x, follow.getCenter().y);
	
	/*m_renderTexture.clear(sf::Color::White);
	m_renderTexture.draw(m_trackSprite);
	m_renderTexture.display();*/

	window.setView(follow);
	//window.draw(player)
	window.draw(m_trackSprite);
	window.draw(carSprite);
	// Only draw when gear is changed
	if (gearChanged == true)
	{
		window.draw(m_carFireSprite);
	}

}

void Player::carDraw(sf::RenderWindow& window)
{
	window.draw(carSprite);
}
void Player::update(sf::Time deltaTime, Xbox360Controller& controller, sf::RenderWindow& window)
{
	// Set up time for acceleration.
	m_time += deltaTime;
	dt = m_time.asSeconds();
	double speed = 0;

	
	offTrackDetection();


	//if (pixel.r >= 80 && pixel.g >= 80 && pixel.b >= 80
	//	&& pixel.r <= 150 && pixel.g <= 150 && pixel.b <= 150)
	//{
	//	m_friction = 0.8;
	//}
	//else
	//{
	//	m_friction = 0.02;
	//}

	// Check for left thumb stick input.
	if (controller.m_currentState.LeftThumbStick.y != 0)
	{
		// Convert thumbstick x and y value into an angle.
		m_angle = atan(controller.m_currentState.LeftThumbStick.x / controller.m_currentState.LeftThumbStick.y);
		m_angle = m_angle * RAD_TO_DEG;
	}

	// Set car sprite to ontop of plater cube.
	carSprite.setPosition(player.getPosition().x, player.getPosition().y);

	/*m_carFireSprite.setPosition(carSprite.getPosition().x - 30, carSprite.getPosition().y + 5);*/

	m_centre.x = player.getPosition().x + player.getTextureRect().width / 2;
	m_centre.y = player.getPosition().y + player.getTextureRect().height / 2;

	m_carFireSprite.setPosition(m_centre.x, m_centre.y);
	m_carFireSprite.setOrigin(4, +32);

	m_carFireSprite.setRotation(carSprite.getRotation());

	//carSprite.rotate(player.getRotation());




	// Code for checking which quadrant the left thumb stick points into. X and y cords checked.
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

	// Manipulate angle that the thumb stick points to given its current quadrant.
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
	if (bottomRight == true)
	{
		m_angle = 90 - m_angle;
	}
	// Work out the distance to the right and left.
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

	// Stop the player rotating if it is withing a certain rotation of desired angle.
	if (player.getRotation() <= (m_angle + 5) && player.getRotation() >= (m_angle - 5))
	{
		player.rotate(0);
	}
	// Rotate left or right depending on the distance to the desired angle.
	else if (distanceRight > distanceLeft)
	{
		// Only allow rotation when car is moving
		if (m_speed != 0)
		{
			// Rotate more if handbrake is pulled.
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
		// Only allow rotation when car is moving
		if (m_speed != 0)
		{
			// Rotate more if handbrake is pulled.
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

	// Check what gear car is in and change max speed.
	if (m_gear == -1)
	{
		m_maxSpeed = -1;
	}
	if (m_gear == 0)
	{
		m_maxSpeed = 0;
	}
	else if (m_gear == 1)
	{
		m_maxSpeed = 1;
	}
	else if (m_gear == 2)
	{
		m_maxSpeed = 3;
	}
	else if (m_gear == 3)
	{
		m_maxSpeed = 6;
	}

	// Car stalls when too low speed
	if (m_gear == 2)
	{
		if (m_speed <= 0.9)
		{
			m_gear = 0;
		}
	}
	else if (m_gear == 3)
	{
		if (m_speed <= 2.9)
		{
			m_gear = 0;
		}
	}



	// Gear up when RB is hit.
	if (controller.m_currentState.RB == true)
	{
		if (m_gear == -1 && m_speed == 0)
		{
			m_gear = m_gear + 1;
			gearChanged = true;
		}
		else if (m_gear == 0 && m_speed == 0)
		{
			m_gear = m_gear + 1;
			gearChanged = true;
		}
		else if (m_gear == 1 && m_speed >= 0.8)
		{
			m_gear = m_gear + 1;
			gearChanged = true;
		}
		else if (m_gear == 2 && m_speed >= 2.8)
		{
			m_gear = m_gear + 1;
			gearChanged = true;
		}
	}
	// Gear down when LB is hit.
	if (controller.m_currentState.LB == true)
	{
		if (m_gear == 4 && m_speed <= 4)
		{
			m_gear = m_gear - 1;
			gearChanged = true;
		}
		else if (m_gear == 3 && m_speed <= 2)
		{
			m_gear = m_gear - 1;
			gearChanged = true;
		}
		else if (m_gear == 2 && m_speed <= 1)
		{
			m_gear = m_gear - 1;
			gearChanged = true;
		}
		else if (m_gear == 1 && m_speed <= 0.5)
		{
			m_gear = m_gear - 1;
			gearChanged = true;
		}
		else if (m_gear == 0 && m_speed == 0)
		{
			m_gear = m_gear - 1;
			gearChanged = true;
		}
	}

	// Accelerate car when right trigger is pressed.
	if (controller.m_currentState.RTrigger > 10)
	{
		// Going forward.
		if (m_speed < m_maxSpeed)
		{
			if (m_gear >= 0)
			{
				m_speed = m_speed + m_acceleration;
			}
			if (m_gear == -1)
			{

			}
		}
		// Going in reverse.
		else if (m_speed > m_maxSpeed)
		{
			if (m_gear == -1)
			{
				m_speed = m_speed - m_acceleration;
			}
		}
	}

	// Handbrake when X is pressed.
	if (controller.m_currentState.X == true)
	{
		// Effect spead appropriatly due to direction of travel.
		if (m_speed > 0)
		{
			m_speed = m_speed - 0.15;
		}
		if (m_speed < 0)
		{
			m_speed = m_speed + 0.15;
		}
	}

	// Brake when left triger is pressed.
	if (controller.m_currentState.LTrigger > 10)
	{
		// Effect spead appropriatly due to direction of travel.
		if (m_speed > -1)
		{
			m_speed = m_speed - m_acceleration;
		}
		if (m_speed < 0)
		{
			m_speed = m_speed + m_acceleration;
		}
	}

	// Friction for slowing down car.
	if (m_speed > 0.1)
	{
		m_speed = m_speed - m_friction;
		pixel = image.getPixel(follow.getCenter().x, follow.getCenter().y);
	}
	if (m_speed < -0.1)
	{
		m_speed = m_speed + m_friction;
	}

	// Stop car completly.
	if (m_speed > -0.1 && m_speed < 0.1)
	{
		m_speed = 0;
	}

	// Move car in correct direction with given speed.
	player.move(cos(player.getRotation()*3.14159265 / 180) * m_speed, sin(player.getRotation()*3.14159265 / 180)* m_speed);

	follow.setCenter(player.getPosition().x + 170, player.getPosition().y + 120);

	if (gearChanged == true)
	{
		fireCount = fireCount + 1;
		if (fireCount == 3)
		{
			gearChanged = false;
			fireCount = 0;
			gearChanged = false;
		}
	}

		
}

void Player::move()
{

}

void Player::offTrackDetection()
{
 pixel = image.getPixel(follow.getCenter().x, follow.getCenter().y );


	/*if (pixel.r >= 80 && pixel.g >= 80 && pixel.b >= 80
		&& pixel.r <= 150 && pixel.g <= 150 && pixel.b <= 150)
	{
		m_friction = 0.8;
	}
	else
	{
		m_friction = 0.02;
	}*/
}
