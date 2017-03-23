#include "Player.h"
#include <iostream>
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
	// Load in skid.
	if (!m_skidTexture.loadFromFile("./resources/images/skid.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	for (int i = 0; i < 1000; i++)
	{
		m_skidSprite[i].setTexture(m_skidTexture);
		m_skidSprite[i].setScale(0.13, 0.13);
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
	follow.setCenter(player.getPosition().x , player.getPosition().y);
	lapText.setPosition(player.getPosition().x - 300, player.getPosition().y - 200);

	m_trackSprite.setTexture(m_trackTexture);
	m_trackSprite.setPosition(0, 0);

	// Set fire sprite initial position
	m_carFireSprite.setTexture(m_carFireTexture);
	m_carFireSprite.setPosition(carSprite.getPosition());

	// Car sprite variables.
	carSprite.setTexture(m_carSpriteSheet);
	carSprite.rotate(270);

	if (!mapSprite.loadFromFile("./resources/images/MapTexture.png"))
	{

	}

	//sets the texture  for each of the sprites in the arrary
	for (int i = 0; i < 16; i++)
	{
		mapTiles[i].setTexture(mapSprite);
		mapTiles[i].setOrigin(mapTiles[i].getOrigin().x / 2, mapTiles[i].getOrigin().y / 2);
	}
	
	//sets postion of each tile 
	sf::IntRect mapRecOne(15, 15, 1000, 650);
	mapTiles[0].setTextureRect(mapRecOne);
	mapTiles[0].setPosition(0, 0);

	sf::IntRect mapRecTwo(1105, 15, 1000, 650);
	mapTiles[1].setTextureRect(mapRecTwo);
	mapTiles[1].setPosition(1000, 0);

	sf::IntRect mapRecThree(2254, 15, 1000, 650);
	mapTiles[2].setTextureRect(mapRecThree);
	mapTiles[2].setPosition(2000, 0);

	sf::IntRect mapRecFour(3364, 23, 1000, 650);
	mapTiles[3].setTextureRect(mapRecFour);
	mapTiles[3].setPosition(3000, 0);
	//
	sf::IntRect mapRecFive(19, 714, 1000, 650);
	mapTiles[4].setTextureRect(mapRecFive);
	mapTiles[4].setPosition(0, 650);

	sf::IntRect mapRecSix(1105, 714, 1000, 650);
	mapTiles[5].setTextureRect(mapRecSix);
	mapTiles[5].setPosition(1000, 650);

	sf::IntRect mapRecSeven(2239, 706, 1000, 650);
	mapTiles[6].setTextureRect(mapRecSeven);
	mapTiles[6].setPosition(2000, 650);

	sf::IntRect mapRecEight(3360, 710, 1000, 650);
	mapTiles[7].setTextureRect(mapRecEight);
	mapTiles[7].setPosition(3000, 650);
	//
	sf::IntRect mapRecNine(14, 1408, 1000, 650);
	mapTiles[8].setTextureRect(mapRecNine);
	mapTiles[8].setPosition(0, 1300);

	sf::IntRect mapRecTen(1113, 1412, 1000, 650);
	mapTiles[9].setTextureRect(mapRecTen);
	mapTiles[9].setPosition(1000, 1300);

	sf::IntRect mapRecEleven(2254, 1404, 1000, 650);
	mapTiles[10].setTextureRect(mapRecEleven);
	mapTiles[10].setPosition(2000, 1300);

	sf::IntRect mapRecTweleve(3368, 1412, 1000, 650);
	mapTiles[11].setTextureRect(mapRecTweleve);
	mapTiles[11].setPosition(3000, 1300);

	sf::IntRect mapRecThirteen(7, 2099, 1000, 650);
	mapTiles[12].setTextureRect(mapRecThirteen);
	mapTiles[12].setPosition(0, 1950);
	//
	sf::IntRect mapRecFourteen(1109, 2103, 1000, 650);
	mapTiles[13].setTextureRect(mapRecFourteen);
	mapTiles[13].setPosition(1000, 1950);

	sf::IntRect mapRecFithteen(2262, 2111, 1000, 650);
	mapTiles[14].setTextureRect(mapRecFithteen);
	mapTiles[14].setPosition(2000, 1950);

	sf::IntRect mapRecSixteen(3380, 2119, 1000, 650);
	mapTiles[15].setTextureRect(mapRecSixteen);
	mapTiles[15].setPosition(3000, 1950);
}

Player::~Player()
{

}
void Player::render(sf::RenderWindow& window)
{

	window.setView(follow);
	for (int x = 0; x < 16; x++)
	{
		if (player.getPosition().x + 400 > mapTiles[x].getPosition().x && player.getPosition().y + 350 > mapTiles[x].getPosition().y)
		{
			window.draw(mapTiles[x]);
		}
	}
	//window.draw(player)
	/*window.draw(circle);
	window.draw(halfwayCircle);*/
	window.draw(lapCircle);
	for (int i = 0; i < 1000; i++)
	{
		window.draw(m_skidSprite[i]);
	}
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
void Player::update(sf::Time deltaTime, Xbox360Controller& controller, CarSelect & CarSelect)
{
	offTrackDetection();
	circle.setPosition(player.getPosition().x - 30, player.getPosition().y - 30);
	noOfLaps.setPosition(player.getPosition().x + 180, player.getPosition().y - 80);
	lapOneText.setPosition(player.getPosition().x - 300, player.getPosition().y - 160);
	lapTwoText.setPosition(player.getPosition().x - 300, player.getPosition().y - 140);
	lapThreeText.setPosition(player.getPosition().x - 300, player.getPosition().y - 120);

	//draws rectangle around the car that can be used.
	sf::IntRect carOneRect(35, 30, 178, 313);
	sf::IntRect carTwoRect(399, 30, 176, 316);
	sf::IntRect carThreeRect(363, 551, 178, 308);

	if (CarSelect.carOnePicked == true)
	{
		carSprite.setTextureRect(carOneRect);
	}
	if (CarSelect.carTwoPicked == true)
	{
		carSprite.setTextureRect(carTwoRect);
	}
	if (CarSelect.carThreePicked == true)
	{
		carSprite.setTextureRect(carThreeRect);
	}
	//carSprite.setTextureRect(carTwoRect);
	carSprite.setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	carSprite.setPosition(player.getPosition().x, player.getPosition().y);
	carSprite.setScale(0.13, 0.13);

	dt = m_time.asSeconds();
	double speed = 0;

	skidTime += deltaTime;
	// Set up time for acceleration.
	countdownTime += deltaTime;
	double laperTime = 0;
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
	if (player.getPosition().x > 1000)
	{
		follow.setCenter(player.getPosition().x + 170, player.getPosition().y + 120);
	}
	
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
		// If statement for dead zone
		if (controller.m_currentState.LeftThumbStick.x > 20 || controller.m_currentState.LeftThumbStick.x < -20 || controller.m_currentState.LeftThumbStick.y < -20 || controller.m_currentState.LeftThumbStick.y > 20)
		{
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
						player.rotate((-1 - m_handlingUpgrade));
						carSprite.rotate(-1 - m_handlingUpgrade);
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
						player.rotate(1 + m_handlingUpgrade);
						carSprite.rotate(1 + m_handlingUpgrade);
					}
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
			// For loop too quick, needed a delay bud :P
			if (m_time.asSeconds() >= 0.01)
			{
				m_skidSprite[counter].setOrigin(carSprite.getOrigin());
				m_skidSprite[counter].setPosition(carSprite.getPosition());
				m_skidSprite[counter].setRotation(carSprite.getRotation());
				skidTime = sf::Time::Zero;
				if (counter < 999)
				{
					counter = counter + 1;
				}
				else
				{
					counter = 0;
				}
			}




			skiding = true;
			// Effect spead appropriatly due to direction of travel.
			/*if (m_speed > 0)
			{
				m_speed = m_speed - 0.15;
			}
			if (m_speed < 0)
			{
				m_speed = m_speed + 0.15;
			}*/
		}
		else
		{
			skiding = false;
		}

		// Brake when left triger is pressed.
		if (controller.m_currentState.LTrigger > 10)
		{
			// Effect spead appropriatly due to direction of travel.
			if (m_speed > -1)
			{
				m_speed = m_speed - (m_acceleration + m_brakingUpgrade);
			}
			if (m_speed < 0)
			{
				m_speed = m_speed + (m_acceleration - m_brakingUpgrade);
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
		if (CarSelect.carOnePicked == true)
		{
			m_brakingUpgrade = m_carOneBraking;
			m_handlingUpgrade = m_carOneHandling;
			player.move(cos(player.getRotation()*3.14159265 / 180) * (m_speed * m_carOneSpeedMax), sin(player.getRotation()*3.14159265 / 180)* (m_speed * m_carOneSpeedMax));
		}

		if (CarSelect.carTwoPicked == true)
		{
			m_brakingUpgrade = m_carTwoBraking;
			m_handlingUpgrade = m_carTwoHandling;
			player.move(cos(player.getRotation()*3.14159265 / 180) * (m_speed * m_carTwoSpeedMax), sin(player.getRotation()*3.14159265 / 180)* (m_speed * m_carTwoSpeedMax));
		}

		if (CarSelect.carThreePicked == true)
		{
			m_brakingUpgrade = m_carThreeBraking;
			m_handlingUpgrade = m_carThreeHandling;
			player.move(cos(player.getRotation()*3.14159265 / 180) * (m_speed * m_carThreeSpeedMax), sin(player.getRotation()*3.14159265 / 180)* (m_speed * m_carThreeSpeedMax));
		}

		follow.setCenter(player.getPosition().x + 170, player.getPosition().y + 120);

		/*std::cout << player.getPosition().x << " , " << player.getPosition().y << std::endl;*/


		

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
			currentTime += deltaTime;
			laperTime = currentTime.asSeconds();
			dt = m_time.asSeconds();
		}
		else
		{
			m_time += deltaTime;
			currentTime += deltaTime;
			laperTime = currentTime.asSeconds();
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
			
			firstLap = laperTime;
			lapOneText.setString("1st Lap: " + std::to_string(firstLap));
			
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
			
			secondLap = laperTime - firstLap;
			lapTwoText.setString("2nd Lap: " + std::to_string(secondLap));
			
			
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
				

			thridLap = laperTime - secondLap;
			lapThreeText.setString("3rd Lap: " + std::to_string(thridLap));
			
		}
	}
	std::cout << player.getPosition().x << ", " << player.getPosition().y << std::endl;
}


void Player::move()
{
	/*1606, 388*/
}

void Player::offTrackDetection()
{
	////Get the colour of the pixel at the players co-ordinate
	//sf::Color color = image.getPixel(player.getPosition().x, player.getPosition().y);

	//if (color.r > color.b)
	//{
	//	//Friction when car is off track
	//	m_friction = 0.8;

	//}
	//else
	//{
	//	//friction whe ncar is on track
	//	m_friction = 0.995;
	//}
	//std::cout << "off circuit";
}