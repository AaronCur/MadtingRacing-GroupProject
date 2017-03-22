#include<iostream>
#include"Upgrade.h"

Upgrade::Upgrade(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)                                                                                                                                                                                                               
{
	if (!m_speedTexture.loadFromFile("Speed.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	//an array of sprites for the speed
	for (int i = 0; i < 6; i++)
	{
		m_speedSprite[i].setTexture(m_speedTexture);
	}
	m_speedSprite[0].setPosition(400, 335);
	m_speedSprite[1].setPosition(430, 335);
	m_speedSprite[2].setPosition(460, 335);
	m_speedSprite[3].setPosition(490, 335);
	m_speedSprite[4].setPosition(520, 335);
	m_speedSprite[5].setPosition(550, 335);

	//an array of sprites of the brake speed
	for (int i = 0; i < 6; i++)
	{
		m_brakeSprite[i].setTexture(m_speedTexture);
	}
	m_brakeSprite[0].setPosition(400, 432);
	m_brakeSprite[1].setPosition(430, 432);
	m_brakeSprite[2].setPosition(460, 432);
	m_brakeSprite[3].setPosition(490, 432);
	m_brakeSprite[4].setPosition(520, 432);
	m_brakeSprite[5].setPosition(550, 432);

	//an array of sprites of the handling
	for (int i = 0; i < 6; i++)
	{
		m_handlingSprite[i].setTexture(m_speedTexture);
	}
	m_handlingSprite[0].setPosition(400, 535);
	m_handlingSprite[1].setPosition(430, 535);
	m_handlingSprite[2].setPosition(460, 535);
	m_handlingSprite[3].setPosition(490, 535);
	m_handlingSprite[4].setPosition(520, 535);
	m_handlingSprite[5].setPosition(550, 535);

	m_font.loadFromFile("AGENTORANGE.TTF");

	m_SpeedText.setFont(m_font);
	m_SpeedText.setString("Speed");
	m_SpeedText.setColor(sf::Color(255, 255, 255, 0));
	m_SpeedText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_SpeedText.setCharacterSize(26);
	m_SpeedText.setPosition(160, 325);

	m_BrakeText.setFont(m_font);
	m_BrakeText.setString("Brakes");
	m_BrakeText.setColor(sf::Color(255, 255, 255, 0));
	m_BrakeText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_BrakeText.setCharacterSize(26);
	m_BrakeText.setPosition(160, 422);

	m_HandlingText.setFont(m_font);
	m_HandlingText.setString("Handling");
	m_HandlingText.setColor(sf::Color(255, 255, 255, 0));
	m_HandlingText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_HandlingText.setCharacterSize(26);
	m_HandlingText.setPosition(160, 525);

	m_L2.setFont(m_font);
	m_L2.setString("Decelerate");
	m_L2.setColor(sf::Color(255, 255, 255, 0));
	m_L2.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_L2.setCharacterSize(22);
	m_L2.setPosition(280, 140);

	m_A.setFont(m_font);
	m_A.setString("Select");
	m_A.setColor(sf::Color(255, 255, 255, 0));
	m_A.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_A.setCharacterSize(22);
	m_A.setPosition(770, 420);

	m_X.setFont(m_font);
	m_X.setString("Shoot");
	m_X.setColor(sf::Color(255, 255, 255, 0));
	m_X.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_X.setCharacterSize(22);
	m_X.setPosition(770, 375);

	m_Y.setFont(m_font);
	m_Y.setString("Boost");
	m_Y.setColor(sf::Color(255, 255, 255, 0));
	m_Y.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_Y.setCharacterSize(22);
	m_Y.setPosition(700, 250);

	m_moneyText.setFont(m_font);
	m_moneyText.setString("Cash:");
	m_moneyText.setColor(sf::Color(255, 255, 255, 0));
	m_moneyText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_moneyText.setCharacterSize(36);
	m_moneyText.setPosition(700, 40);

	m_fundText.setFont(m_font);
	m_fundText.setColor(sf::Color(255, 255, 255, 0));
	m_fundText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_fundText.setCharacterSize(36);
	m_fundText.setPosition(850, 40);

	m_priceTag.setFont(m_font);
	m_priceTag.setColor(sf::Color(255, 255, 255, 0));
	m_priceTag.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_priceTag.setCharacterSize(36);
	m_priceTag.setPosition(700, 440);	

	m_cost.setFont(m_font);
	m_cost.setString("Cost:");
	m_cost.setColor(sf::Color(255, 255, 255, 0));
	m_cost.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_cost.setCharacterSize(36);
	m_cost.setPosition(700, 360);

	m_upgradeText.setFont(m_font);
	m_upgradeText.setString("UPGRADES");
	m_upgradeText.setColor(sf::Color::White);
	m_upgradeText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_upgradeText.setCharacterSize(50);
	m_upgradeText.setPosition(290, 10);

	if (!logoTexture.loadFromFile("help.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	// Load textures for upgrade icons
	if (!handlingTexture.loadFromFile("handling.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	if (!brakeTexture.loadFromFile("brake.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	if (!speedGaugeTexture.loadFromFile("speedGauge.png"))
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

	if (!m_selectTexture.loadFromFile("select.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_backgroundTexture.loadFromFile("mechanicBackground.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0, 0);

	m_selectSprite.setTexture(m_selectTexture);
	m_selectSprite.setPosition(-100, -100);

	// Car sprite variables.
	carSprite.setTexture(m_carSpriteSheet);
	sf::IntRect carOneRect(35, 30, 178, 313);
	carSprite.setTextureRect(carOneRect);
	carSprite.rotate(270);
	carSprite.setPosition(-300, 280);
	/*carSprite.setScale();*/

	carSprite2.setTexture(m_carSpriteSheet);
	sf::IntRect carTwoRect(399, 30, 176, 316);
	carSprite2.setTextureRect(carTwoRect);
	carSprite2.rotate(270);
	carSprite2.setPosition(-350, 280);

	carSprite3.setTexture(m_carSpriteSheet);
	sf::IntRect carThreeRect(363, 551, 178, 308);
	carSprite3.setTextureRect(carThreeRect);
	carSprite3.rotate(270);
	carSprite3.setPosition(-350, 280);

	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(100, 420);

	// Set texture and positions of upgrades
	handlingSprite.setTexture(handlingTexture);
	handlingSprite.setPosition(50, 500);

	speedGaugeSprite.setTexture(speedGaugeTexture);
	speedGaugeSprite.setPosition(50, 300);

	brakeSprite.setTexture(brakeTexture);
	brakeSprite.setPosition(50, 400);

}

Upgrade::~Upgrade()
{
	std::cout << "destructing Help" << std::endl;
}

void Upgrade::update(sf::Time dt, Xbox360Controller&controller)
{
	// Set initial values for each car
	if (oneSelected == true)
	{
		m_speedCount = m_oneSpeed;
		m_brakeCount = m_oneBrake;
		m_handlingCount = m_oneHandling;
	}
	if (twoSelected == true)
	{
		m_speedCount = m_twoSpeed;
		m_brakeCount = m_twoBrake;
		m_handlingCount = m_twoHandling;
	}
	if (threeSelected == true)
	{
		m_speedCount = m_threeSpeed;
		m_brakeCount = m_threeBrake;
		m_handlingCount = m_threeHandling;
	}

	m_cumulativeTime += dt;

	if (logoSprite.getPosition().y > -421 && logoSprite.getPosition().y > 0)
	{
		alpha = alpha + 2.8;
		logoSprite.move(0, -5);
		logoSprite.setColor(sf::Color(255, 255, 255, alpha));
	}

	if (logoSprite.getPosition().y == 0 && alphaText <= 252)
	{
		logoSprite.move(0, 0);
		logoSprite.setColor(sf::Color(255, 255, 255, 255));

		alphaText = alphaText + 2;
		m_BrakeText.setColor(sf::Color(255, 255, 255, alphaText));
		m_SpeedText.setColor(sf::Color(255, 255, 255, alphaText));
		m_L2.setColor(sf::Color(255, 255, 255, alphaText));
		m_HandlingText.setColor(sf::Color(255, 255, 255, alphaText));
		m_X.setColor(sf::Color(255, 255, 255, alphaText));
		m_Y.setColor(sf::Color(255, 255, 255, alphaText));
		m_moneyText.setColor(sf::Color(255, 255, 255, alphaText));
		m_A.setColor(sf::Color(255, 255, 255, alphaText));
		m_fundText.setColor(sf::Color(255, 255, 255, alphaText));
		m_priceTag.setColor(sf::Color(255, 255, 255, alphaText));
		m_cost.setColor(sf::Color(255, 255, 255, alphaText));


	}
	if (carSprite.getPosition().x <= m_moveLimit)
	{
		carSprite.move(3.5, 0);
	}
	if (carSprite2.getPosition().x <= m_moveLimit2)
	{
		carSprite2.move(3.5, 0);
	}
	if (carSprite3.getPosition().x <= m_moveLimit3)
	{
		carSprite3.move(3.5, 0);
	}
	// Button to go back to previous menu
	if (controller.m_currentState.B)
	{

		m_game->setGameState(GameState::Options);

	}
	// Check which button is pressed.
	if (buttonCount == 1)
	{
		buttonOneSelected = true;
		buttonTwoSelected = false;
		buttonThreeSelected = false;
	}
	if (buttonCount == 2)
	{
		buttonOneSelected = false;
		buttonTwoSelected = true;
		buttonThreeSelected = false;
	}
	if (buttonCount == 3)
	{
		buttonOneSelected = false;
		buttonTwoSelected = false;
		buttonThreeSelected = true;
	}

	// Set select position according to button.
	if (buttonCount == 1)
	{
		m_selectSprite.setPosition(8, 310);
	}
	if (buttonCount == 2)
	{
		m_selectSprite.setPosition(8, 420);
	}
	if (buttonCount == 3)
	{
		m_selectSprite.setPosition(8, 520);
	}

	// Code to make pressed false.
	if (controller.m_currentState.DpadDown == false && controller.m_currentState.DpadUp == false && controller.m_currentState.A == false && controller.m_currentState.RB == false) 
	{
		pressed = false;
	}
	if (controller.m_currentState.A && pressed == false)
	{
		if (m_funds >= m_price)
		{
			if (buttonCount == 1)
			{
				if (m_speedCount < 6)
				{
					if (oneSelected == true)
					{

						m_oneSpeed = m_oneSpeed + 1;

					}
					if (twoSelected == true)
					{

						m_twoSpeed = m_twoSpeed + 1;

					}
					if (threeSelected == true)
					{

						m_threeSpeed = m_threeSpeed + 1;

					}
				}
				pressed = true;
			}
			else if (buttonCount == 2)
			{
				if (m_brakeCount < 6)
				{
					if (oneSelected == true)
					{
						m_oneBrake = m_oneBrake + 1;
					}
					if (twoSelected == true)
					{
						m_twoBrake = m_twoBrake + 1;
					}
					if (threeSelected == true)
					{
						m_threeBrake = m_threeBrake + 1;
					}
				}
				pressed = true;
			}
			else if (buttonCount == 3)
			{
				if (m_handlingCount < 6)
				{
					if (oneSelected == true)
					{
						m_oneHandling = m_oneHandling + 1;
					}
					if (twoSelected == true)
					{
						m_twoHandling = m_twoHandling + 1;
					}
					if (oneSelected == true)
					{
						m_threeHandling = m_threeHandling + 1;
					}
				}
				pressed = true;
			}
		}
	}

	m_time += dt;
	// Switch car with RB
	if (controller.m_currentState.RB == true && pressed == false && m_time.asSeconds() > 3)
	{
		m_time = sf::Time::Zero;
		if (m_moveLimit == 340)
		{
			m_moveLimit = 1200;
			m_moveLimit2 = 340;
			twoSelected = true;
			oneSelected = false;
			threeSelected = false;
		}
		else if (m_moveLimit2 == 340)
		{
			threeSelected = true;
			twoSelected = false;
			oneSelected = false;
			m_moveLimit2 = 1200;
			m_moveLimit3 = 340;
			
		}
		
		else if (m_moveLimit3 == 340)
		{
			oneSelected = true;
			twoSelected = false;
			threeSelected = false;
			m_moveLimit3 = 1200;
			m_moveLimit = 340;
		}
		
		pressed = true;
	}
	if (carSprite3.getPosition().x >= 1100)
	{
		carSprite3.setPosition(-400, 280);
		m_moveLimit3 = -400;
	}
	if (carSprite2.getPosition().x >= 1100)
	{
		carSprite2.setPosition(-400, 280);
		m_moveLimit2 = -400;
	}
	if (carSprite.getPosition().x >= 1100)
	{
		carSprite.setPosition(-400, 280);
		m_moveLimit = -400;
	}
	//allows player to navigate through the menu
	if (controller.m_currentState.DpadDown && pressed == false)
	{
		buttonCount = buttonCount + 1;
		if (buttonCount == 4)
		{
			buttonCount = 1;
		}
		pressed = true;
	}
	if (controller.m_currentState.DpadUp && pressed == false)
	{
		buttonCount = buttonCount - 1;
		if (buttonCount == 0)
		{
			buttonCount = 3;
		}
		if (buttonCount == -1)
		{
			buttonCount = 3;
		}

		pressed = true;
	}
	// Pay required amount
	if (controller.m_currentState.A == true)
	{
		if (m_funds >= m_price)
		{
			m_funds = m_funds - m_price;
		}
	}
	// Set price according to button
	if (buttonCount == 1)
	{
		// Change the price of speed upgrade for each car and each level
		if (oneSelected == true)
		{
			if (m_oneSpeed == 1)
			{
				m_price = 200;
			}
			else if (m_oneSpeed == 2)
			{
				m_price = 300;
			}
			else if (m_oneSpeed == 3)
			{
				m_price = 400;
			}
			else if (m_oneSpeed == 4)
			{
				m_price = 500;
			}
			else if (m_oneSpeed == 5)
			{
				m_price = 600;
			}
			else if (m_oneSpeed == 6)
			{
				m_price = 000;
			}
		}
		else if (twoSelected == true)
		{
			if (m_twoSpeed == 1)
			{
				m_price = 200;
			}
			else if (m_twoSpeed == 2)
			{
				m_price = 300;
			}
			else if (m_twoSpeed == 3)
			{
				m_price = 400;
			}
			else if (m_twoSpeed == 4)
			{
				m_price = 500;
			}
			else if (m_twoSpeed == 5)
			{
				m_price = 600;
			}
			else if (m_twoSpeed == 6)
			{
				m_price = 000;
			}
		}
	    else if (threeSelected == true)
		{
			if (m_threeSpeed == 1)
			{
				m_price = 200;
			}
			else if (m_threeSpeed == 2)
			{
				m_price = 300;
			}
			else if (m_threeSpeed == 3)
			{
				m_price = 400;
			}
			else if (m_threeSpeed == 4)
			{
				m_price = 500;
			}
			else if (m_threeSpeed == 5)
			{
				m_price = 600;
			}
			else if (m_threeSpeed == 6)
			{
				m_price = 000;
			}
		}
	}
	// Change the price of brake upgrade for each car and each level
	if (buttonCount == 2)
	{
		if (oneSelected == true)
		{
			if (m_oneBrake == 1)
			{
				m_price = 200;
			}
			else if (m_oneBrake == 2)
			{
				m_price = 300;
			}
			else if (m_oneBrake == 3)
			{
				m_price = 400;
			}
			else if (m_oneBrake == 4)
			{
				m_price = 500;
			}
			else if (m_oneBrake == 5)
			{
				m_price = 600;
			}
			else if (m_oneBrake == 6)
			{
				m_price = 000;
			}
		}
		else if (twoSelected == true)
		{
			if (m_twoBrake == 1)
			{
				m_price = 200;
			}
			else if (m_twoBrake == 2)
			{
				m_price = 300;
			}
			else if (m_twoBrake == 3)
			{
				m_price = 400;
			}
			else if (m_twoBrake == 4)
			{
				m_price = 500;
			}
			else if (m_twoBrake == 5)
			{
				m_price = 600;
			}
			else if (m_twoBrake == 6)
			{
				m_price = 000;
			}
		}
		else if (threeSelected == true)
		{
			if (m_threeSpeed == 1)
			{
				m_price = 200;
			}
			else if (m_threeSpeed == 2)
			{
				m_price = 300;
			}
			else if (m_threeSpeed == 3)
			{
				m_price = 400;
			}
			else if (m_threeSpeed == 4)
			{
				m_price = 500;
			}
			else if (m_threeSpeed == 5)
			{
				m_price = 600;
			}
			else if (m_threeSpeed == 6)
			{
				m_price = 000;
			}
		}
	}
	// Change the price of handling upgrade for each car and each level

	if (buttonCount == 3)
	{
		if (oneSelected == true)
		{
			if (m_oneHandling == 1)
			{
				m_price = 200;
			}
			else if (m_oneHandling == 2)
			{
				m_price = 300;
			}
			else if (m_oneHandling == 3)
			{
				m_price = 400;
			}
			else if (m_oneHandling == 4)
			{
				m_price = 500;
			}
			else if (m_oneHandling == 5)
			{
				m_price = 600;
			}
			else if (m_oneHandling == 6)
			{
				m_price = 000;
			}
		}
		if (twoSelected == true)
		{
			if (m_twoHandling == 1)
			{
				m_price = 200;
			}
			else if (m_twoHandling == 2)
			{
				m_price = 300;
			}
			else if (m_twoHandling == 3)
			{
				m_price = 400;
			}
			else if (m_twoHandling == 4)
			{
				m_price = 500;
			}
			else if (m_twoHandling == 5)
			{
				m_price = 600;
			}
			else if (m_twoHandling == 6)
			{
				m_price = 000;
			}
		}
		if (threeSelected == true)
		{
			if (m_threeHandling == 1)
			{
				m_price = 200;
			}
			else if (m_threeHandling == 2)
			{
				m_price = 300;
			}
			else if (m_threeHandling == 3)
			{
				m_price = 400;
			}
			else if (m_threeHandling == 4)
			{
				m_price = 500;
			}
			else if (m_threeHandling == 5)
			{
				m_price = 600;
			}
			else if (m_threeHandling == 6)
			{
				m_price = 000;
			}
		}
	}

	// Assign price to price text
	
	m_priceStream.str("");
	m_priceStream << m_price;
	m_priceTag.setString(m_priceStream.str().c_str());

	// Assign funds to fund text

	m_fundStream.str("");
	m_fundStream << m_funds;
	m_fundText.setString(m_fundStream.str().c_str());
}

void Upgrade::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	for (int i = 0; i < m_speedCount; i ++)
	{
		window.draw(m_speedSprite[i]);
	}
	for (int x = 0; x < m_brakeCount; x++)
	{
		window.draw(m_brakeSprite[x]);
	}
	for (int y = 0; y < m_handlingCount; y++)
	{
		window.draw(m_handlingSprite[y]);
	}
	
	window.draw(m_SpeedText);

	window.draw(m_BrakeText);

	window.draw(m_HandlingText);
	
	// draw upgrade icons

	window.draw(handlingSprite);
	window.draw(brakeSprite);
	window.draw(speedGaugeSprite);

	window.draw(m_selectSprite);


	/*window.draw(backgroundSprite);
	window.draw(logoSprite);
	window.draw(m_R1);
	window.draw(m_R2);
	window.draw(m_L1);
	window.draw(m_L2);
	window.draw(m_A);
	window.draw(m_X);
	window.draw(m_Y);
	window.draw(m_B);
	window.draw(m_rightAnalog);
	window.draw(m_leftAnalog);
	window.draw(m_dPad);*/
	window.draw(m_moneyText);
	window.draw(m_fundText);
	window.draw(m_priceTag);
	window.draw(m_cost);
	window.draw(m_upgradeText);
	window.draw(carSprite);
	window.draw(carSprite2);
	window.draw(carSprite3);

}