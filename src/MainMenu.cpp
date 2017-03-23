#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_play("Play", m_font),
	m_upgrades("Upgrades", m_font),
	m_options("Options", m_font),
	m_exit("Exit", m_font),
	m_mainMenuTxt("Main Menu", m_meatLoaf, 70)
{
	if (!m_mainMenuTexture.loadFromFile("./resources/images/button.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_selectTex.loadFromFile("./resources/images/select.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_backgroundTexture.loadFromFile("./resources/images/background.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	m_meatLoaf.loadFromFile("./resources/images/Meatloaf.ttf");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_mainMenuTxt.setPosition(740, -10);
	if (!buffer.loadFromFile("./resources/images/button.wav"))
	{
		std::string main("Error Loading sound");
		throw std::exception(main.c_str());
	}
	buttonPress.setBuffer(buffer);
	m_backgroundSprite.setPosition(0, 0);


	m_select.setTexture(m_selectTex);
	m_select.setPosition(-11, 50);
	
	m_selectUpgrade.setTexture(m_selectTex);
	m_selectUpgrade.setPosition(381, 200);

	m_selectOptions.setTexture(m_selectTex);
	m_selectOptions.setPosition(421, 350);
	
	m_selectExit.setTexture(m_selectTex);
	m_selectExit.setPosition(461, 500);

	m_mainMenuSprite.setTexture(m_mainMenuTexture);
	m_mainMenuSprite.setPosition(-10, 30);

	m_mainMenuSpriteTwo.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteTwo.setPosition(590, 180);

	m_mainMenuSpriteThree.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteThree.setPosition(-10, 330);

	m_mainMenuSpriteFour.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteFour.setPosition(590, 480);

	//m_play.setPosition(320, 55);
	m_play.setColor(sf::Color::White);
	m_options.setScale(0.7, 1);
	m_upgrades.setScale(0.6, 1);

	m_blankTexture.loadFromFile("./resources/images/blank.png");
	m_blankSprite.setTexture(m_blankTexture);

	if (!m_shader.loadFromFile("firstShader.txt", sf::Shader::Fragment))
	{
		std::cout << "Shader is not available" << std::endl;
	}

	m_shader.setParameter("time", 0);
	m_shader.setParameter("resolution", 1000, 650);

	m_blankSprite.setPosition(0, 0);
}

MainMenu::~MainMenu()
{
	std::cout << "destructing Splash" << std::endl;
	
}


void MainMenu::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	time += deltaTime;
	updateShader = time.asSeconds();

	m_shader.setParameter("time", updateShader);

	if (buttonCounter == 1)
	{
		buttonOneSelected = true;
		buttonTwoSelected = false;
		buttonThreeSelected = false;
		buttonFourSelected = false;
	}
	if (buttonCounter == 2)
	{
		buttonOneSelected = false;
		buttonTwoSelected = true;
		buttonThreeSelected = false;
		buttonFourSelected = false;
	}
	if (buttonCounter == 3)
	{
		buttonOneSelected = false;
		buttonTwoSelected = false;
		buttonThreeSelected = true;
		buttonFourSelected = false;
	}
	if (buttonCounter == 4)
	{
		buttonOneSelected = false;
		buttonTwoSelected = false;
		buttonThreeSelected = false;
		buttonFourSelected = true;
	}
	if (buttonOneSelected == true)
	{
		
			if (controller.m_currentState.A&& controller.m_previousState.A == false && buttonOneSelected)
			{
				buttonPress.play();
				m_game->setGameState(GameState::CarSelect);
			}
		
	}
	if (buttonTwoSelected == true)
	{

		if (controller.m_currentState.A)
		{
			buttonPress.play();
			m_game->setGameState(GameState::Upgrade);
		}
	}
	if (buttonThreeSelected == true)
	{
		if (controller.m_currentState.A)
		{
			buttonPress.play();
			m_game->setGameState(GameState::Options);

		}
	}
	if (buttonFourSelected == true)
	{
		if (controller.m_previousState.A)
		{
			buttonPress.play();
			close = true;

		}
	}
	/*if (buttonOneSelected == false)
	{
		m_playGame.setColor(sf::Color::Blue);
	}
	if (buttonTwoSelected == false)
	{
		m_options.setColor(sf::Color::Green);
	}
	if (buttonThreeSelected == false)
	{
		m_exit.setColor(sf::Color::Red);
	}*/


	// Set position of text so it moves with button
	m_play.setPosition(m_mainMenuSprite.getPosition().x + 130, 55);
	m_upgrades.setPosition(m_mainMenuSpriteTwo.getPosition().x + 120, 205);
	m_options.setPosition(m_mainMenuSpriteThree.getPosition().x + 120, 355);
	m_exit.setPosition(m_mainMenuSpriteFour.getPosition().x + 140, 505);

	if (controller.m_currentState.DpadDown == false && controller.m_currentState.DpadUp == false)
	{
		pressed = false;
	}
	if (controller.m_currentState.DpadDown && pressed == false)
	{
		buttonCounter = buttonCounter + 1;
		if (buttonCounter == 5)
		{
			buttonCounter = 1;
		}
		pressed = true;
	}
	if (controller.m_currentState.DpadUp && pressed == false)
	{
		buttonCounter = buttonCounter - 1;
		if (buttonCounter == 0)
		{
			buttonCounter = 4;
		}
		if (buttonCounter == -1)
		{
			buttonCounter = 4;
		}

		pressed = true;
	}
	
	if (buttonCounter == 1 && alphaCount == true)
	{
		alpha += 5;
		m_play.setColor(sf::Color(255, 255, 255, alpha));
	}

	else
	{
		m_play.setColor(sf::Color(255, 255, 255, 255));
	}


	if (buttonCounter == 2)
	{
		alpha += 5;
		m_upgrades.setColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		m_upgrades.setColor(sf::Color(255, 255, 255, 255));
	}

	if (buttonCounter == 3)
	{
		alpha += 5;
		m_options.setColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		m_options.setColor(sf::Color(255, 255, 255, 255));
	}

	if (buttonCounter == 4)
	{
		alpha += 5;
		m_exit.setColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		m_exit.setColor(sf::Color(255, 255, 255, 255));
	}

	if (m_mainMenuSprite.getPosition().x > -11)
	{
		if (m_mainMenuSprite.getPosition().x <= 300)
		{
			
			//moving in from the right
			m_mainMenuSprite.move(10, 0); //PLAY
			m_select.move(11, 0);//OPTIONS
			m_mainMenuSpriteThree.move(12.5, 0);

			//moving in from the left
			m_mainMenuSpriteTwo.move(-7.5, 0);//UP
			
			m_mainMenuSpriteFour.move(-5, 0);//EXIT
		}

	}

	//Check to see what button is pressed
	
	
	


}

void MainMenu::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	window.draw(m_blankSprite, &m_shader);
	window.draw(m_carOne);
	window.draw(m_carTwo);



	window.draw(m_mainMenuSprite);
	window.draw(m_mainMenuSpriteTwo);
	window.draw(m_mainMenuSpriteThree);
	window.draw(m_mainMenuSpriteFour);
	window.draw(m_mainMenuTxt);
	if(buttonCounter == 1)
	{
		window.draw(m_select);
	}
	if (buttonCounter == 2)
	{
		window.draw(m_selectUpgrade);
	}
	if (buttonCounter == 3)
	{
		window.draw(m_selectOptions);
	}
	if (buttonCounter == 4)
	{
		window.draw(m_selectExit);
	}
	
	window.draw(m_play);
	window.draw(m_upgrades);
	window.draw(m_options);
	window.draw(m_exit);
}

