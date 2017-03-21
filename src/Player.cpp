#include "Player.h"
#include <math.h>
double const Player::DEG_TO_RAD = 3.14 * 180.0f;
double const Player::RAD_TO_DEG = 57.295779513;

Player::Player(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_angle(0)
	
{
	// Variables for player cube.
	player.setSize(sf::Vector2f(40, 20));
	player.setFillColor(sf::Color::Red);
	player.setPosition(1390, 475);
	player.setOrigin(20, 10);
	if (!m_meatLoaf.loadFromFile("./resources/images/Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	circle = sf::CircleShape(30);
	circle.setPosition(player.getPosition().x - 30, player.getPosition().y - 30);
	halfwayCircle = sf::CircleShape(30);
	halfwayCircle.setPosition(2200, 2270);
	lapCircle = sf::CircleShape(30);
	lapCircle.setPosition(1576, 358);

	// Load in track.
	if (!m_trackTexture.loadFromFile("./resources/images/bigTrack.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	
	// Load in car.
	if (!m_carSpriteSheet.loadFromFile("./resources/images/CarSprite.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	// Load in fire.
	if (!m_carFireTexture.loadFromFile("./resources/images/fire.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	lapText.setFont(m_font);
	lapText.setString("Time: ");
	lapText.setStyle(sf::Text::Italic | sf::Text::Bold);
	lapText.setColor(sf::Color::White);
	lapText.setPosition(20, 40);
	lapText.setCharacterSize(23);

	lapOneText.setFont(m_font);
	lapOneText.setStyle(sf::Text::Bold);
	lapOneText.setColor(sf::Color::White);
	lapOneText.setPosition(player.getPosition().x - 300, player.getPosition().y - 150);
	lapOneText.setCharacterSize(15);

	lapTwoText.setFont(m_font);
	lapTwoText.setStyle(sf::Text::Bold);
	lapTwoText.setColor(sf::Color::White);
	lapTwoText.setPosition(player.getPosition().x - 300, player.getPosition().y - 130);
	lapTwoText.setCharacterSize(15);

	lapThreeText.setFont(m_font);
	lapThreeText.setStyle(sf::Text::Bold);
	lapThreeText.setColor(sf::Color::White);
	lapThreeText.setPosition(player.getPosition().x - 300, player.getPosition().y - 110);
	lapThreeText.setCharacterSize(15);

	noOfLaps.setFont(m_meatLoaf);
	noOfLaps.setString("Laps " + std::to_string(laps) + "/3");
	noOfLaps.setStyle(sf::Text::Italic | sf::Text::Bold);
	noOfLaps.setColor(sf::Color::Black);
	noOfLaps.setPosition(player.getPosition().x + 40 , player.getPosition().y - 80);
	noOfLaps.setCharacterSize(23);

	countdownTxt.setFont(m_meatLoaf);
	countdownTxt.setString(std::to_string(countdown));
	countdownTxt.setStyle(sf::Text::Bold);
	countdownTxt.setColor(sf::Color::White);
	countdownTxt.setPosition(player.getPosition().x - 40, player.getPosition().y - 120);
	countdownTxt.setCharacterSize(100);

	//follow.setCenter(500, 325);
	follow.setViewport(sf::FloatRect(0, 0, 1.5, 1.5));
	follow.setSize(1000, 650);
	follow.setCenter(player.getPosition().x , player.getPosition().y );
	lapText.setPosition(player.getPosition().x - 300, player.getPosition().y - 200);

	m_trackSprite.setTexture(m_trackTexture);
	m_trackSprite.setPosition(0, 0);

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

	window.setView(follow);
	window.draw(m_trackSprite);
	//window.draw(player)
	window.draw(circle);
	window.draw(halfwayCircle);
	window.draw(lapCircle);
	window.draw(carSprite);
	window.draw(noOfLaps);
	
	// Only draw when gear is changed
	if (gearChanged == true)
	{
		window.draw(m_carFireSprite);
	}
	window.draw(lapText);
	window.draw(lapOneText);
	window.draw(lapTwoText);
	window.draw(lapThreeText);
	if (countdown > 0)
	{
		window.draw(countdownTxt);
	}
	
}

void Player::carDraw(sf::RenderWindow& window)
{
	window.draw(carSprite);
}
void Player::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	circle.setPosition(player.getPosition().x - 30, player.getPosition().y - 30);
	noOfLaps.setPosition(player.getPosition().x + 180, player.getPosition().y - 80);
	lapOneText.setPosition(player.getPosition().x - 300, player.getPosition().y - 160);
	lapTwoText.setPosition(player.getPosition().x - 300, player.getPosition().y - 140);
	lapThreeText.setPosition(player.getPosition().x - 300, player.getPosition().y - 120);

	// Set up time for acceleration.
	countdownTime += deltaTime;
	if (countdownTime.asSeconds() > 1 && !start)
	{
		countdown--;
		countdownTime = sf::Time::Zero;
		countdownTxt.setString(std::to_string(countdown));
		countdownTxt.setPosition(player.getPosition().x - 40, player.getPosition().y - 120);
	}

	if (countdown <= 0)
	{
		start = true;
		countdown = 0;
	}

	follow.setCenter(player.getPosition().x + 170, player.getPosition().y + 120);
	if (start == true)
	{

		double speed = 0;
		lapText.setPosition(player.getPosition().x - 300, player.getPosition().y - 200);
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
		/*if (m_gear == 2)
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
		}*/



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
		if (!reset)
		{
			m_time += deltaTime;
			dt = m_time.asSeconds();
		}
		else
		{
			m_time += deltaTime;
			dt = m_time.asSeconds();
		}
		if (dt >= 60)
		{
			minute++;
			m_time = sf::Time::Zero;
			dt = m_time.asSeconds();
			reset = true;
		}
		if (dt >= 10)
		{
			lapText.setString("Time: " + std::to_string(minute) + ":" + std::to_string(dt));
		}
		else
		{
			lapText.setString("Time: " + std::to_string(minute) + ":0" + std::to_string(dt));
		}
	}

	/*std::cout << player.getPosition().x << ", " << player.getPosition().y << std::endl;*/
	int x1 = circle.getPosition().x;
	int y1 = circle.getPosition().y;
	int x2 = halfwayCircle.getPosition().x;
	int y2 = halfwayCircle.getPosition().y;
	int x3 = lapCircle.getPosition().x;
	int y3 = lapCircle.getPosition().y;
	int radius1 = 30;
	int radius2 = 30;

	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (radius1 + radius2))
	{
		halfway = true;
		std::cout << "HALFWAY";
	}

	if (halfway && !lap)
	{
		if (sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) < (radius1 + radius2))
		{
			lap = true;
			halfway = false;
			std::cout << "LAP";
			laps = 1;
			noOfLaps.setString("Laps " + std::to_string(laps) + "/3");
			firstLap = dt;
			lapOneText.setString("1st Lap: " + std::to_string(minute) + ":" + std::to_string(firstLap));
		}
	}
	else if (halfway && lap && !lap2)
	{
		if (sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) < (radius1 + radius2))
		{
			lap2 = true;
			halfway = false;
			std::cout << "LAP2";
			laps = 2;
			noOfLaps.setString("Laps " + std::to_string(laps) + "/3");
			secondLap = dt;
			lapTwoText.setString("2nd Lap: " + std::to_string(minute) + ":" + std::to_string(secondLap));
		}
	}
	else if (halfway && lap && lap2 && !lap3)
	{
		if (sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) < (radius1 + radius2))
		{
			lap3 = true;
			halfway = false;
			std::cout << "LAP3";
			laps = 3;
			noOfLaps.setString("Laps " + std::to_string(laps) + "/3");
			thridLap = dt;
			lapThreeText.setString("3rd Lap: " + std::to_string(minute) + ":" + std::to_string(thridLap));
		}
	}
	
}

void Player::move()
{
	/*1606, 388*/
}