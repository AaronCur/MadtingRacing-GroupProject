#include "Pause.h"
#include <iostream>
/// <summary>
/// author Aaron Curry
/// time taken: 10:00 - 12:00
///				18:00 - 20:00
/// </summary>
Pause::Pause(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_resume("Resume", m_font, 30),
	m_options("Options", m_font, 30),
	m_exit("Press B to exit to MAIN MENU", m_adventure, 30),
	alpha(0),
	flip(false)
{
	if (!m_adventure.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	if (!m_buttonTexture.loadFromFile("button.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_selectTexture.loadFromFile("select.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_backgroundTexture.loadFromFile("background4.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	//Set the backdrop
	m_backgroundSprite.setTexture(m_backgroundTexture);


	m_selectBack.setTexture(m_selectTexture);
	m_selectBack.setPosition( 385, 140);

	m_selectOptions .setTexture(m_selectTexture);
	m_selectOptions.setPosition(385, 360);


	m_buttonOne.setTexture(m_buttonTexture);
	m_buttonOne.setPosition(355, -50);

	m_buttonTwo.setTexture(m_buttonTexture);
	m_buttonTwo.setPosition(355, 700);




	//m_play.setPosition(320, 55);
	m_resume.setColor(sf::Color::White);
	m_resume.setScale(0.7, 1);
	m_resume.setPosition(3600, 140);
	m_options.setColor(sf::Color::White);
	m_options.setPosition(360, 360);


//	m_exit.setFont(m_adventure);
	m_exit.setColor(sf::Color::Black);
	
	m_exit.setPosition(320, 510);


	m_options.setScale(0.7, 1);

	//Set up the game view so its 1 to 1 scale with game window
	pause.setViewport(sf::FloatRect(0, 0, 1, 1));
	//Set the view size
	pause.setSize(1000, 650);
	//Set the origin to the center
	pause.setCenter(500, 325);

	//Initialise selector position
	buttonCounter = 1;
	
}

Pause::~Pause()
{
	std::cout << "destructing Pause" << std::endl;

}


void Pause::update(sf::Time deltaTime, Xbox360Controller& controller)
{

	m_cumulativeTime += deltaTime;


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

	//When the buttons are pressed the gamestate will be changed to the corresponding game screen
	if (buttonOneSelected == true)
	{
		if (controller.m_currentState.A&& controller.m_previousState.A == false)
		{
			m_game->setGameState(GameState::GameScreen);
		}
	}
	if (buttonTwoSelected == true)
	{

		if (controller.m_currentState.A && controller.m_previousState.A == false)
		{
			m_game->setGameState(GameState::PauseOptions);
		}
	}
	
	if (controller.m_currentState.B && controller.m_previousState.B == false)
	{
		m_game->setGameState(GameState::MainMenu);
	}

	//// Set position of text so it moves with button
	m_resume.setPosition(m_buttonOne.getPosition().x + 120, m_buttonOne.getPosition().y + 15);
	m_options.setPosition(m_buttonTwo.getPosition().x + 120, m_buttonTwo.getPosition().y + 15);
	

	if (controller.m_currentState.DpadDown == false && controller.m_currentState.DpadUp == false)
	{
		pressed = false;
	}
	//when the selector is at the bottom button and you press doen the selector goes back to the top
	if (controller.m_currentState.DpadDown && pressed == false)
	{
		buttonCounter = buttonCounter + 1;
		if (buttonCounter == 3)
		{
			buttonCounter = 1;
		}
		pressed = true;
	}
	//When the selector is at the top button and you press up the selector goes to the bottom button
	if (controller.m_currentState.DpadUp && pressed == false)
	{
		buttonCounter = buttonCounter - 1;
		if (buttonCounter == 0)
		{
			buttonCounter = 2;
		}
		if (buttonCounter == -1)
		{
			buttonCounter = 2;
		}

		pressed = true;
	}


	//Translate buttons onto screen until they reach a point
	if (m_buttonOne.getPosition().y < 124)
	{
		m_buttonOne.move(0, 10);
	}
	if (m_buttonTwo.getPosition().y > 349)
	{
		m_buttonTwo.move(0, -10);
	}

	//To get the text to pulse 
	if (m_cumulativeTime.asSeconds() > 1)
	{
		//Decides which way the alpha will be incremented ( negative or possitive)
		if (alpha >= 254)
		{
			flip = true;
		}
		else if (alpha <= 1)
		{
			flip = false;
		}
		//Increments the alpha value
		if (flip == false)
		{
			alpha += 2;
			m_exit.setColor(sf::Color(0, 0, 102, alpha));
		}
		else if (flip == true)
		{
			alpha -= 2;
			m_exit.setColor(sf::Color(0, 0, 102, alpha));
		}

	}
	


}

void Pause::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);


	window.setView(pause);
	window.draw(m_backgroundSprite);

	window.draw(m_buttonOne);
	window.draw(m_buttonTwo);
	//After the buttons are on screen the selector will appear
	if (m_cumulativeTime.asSeconds() > 1)
	{
		if (buttonCounter == 1)
		{
			window.draw(m_selectBack);
		}
		if (buttonCounter == 2)
		{
			window.draw(m_selectOptions);
		}
		if (buttonCounter == 3)
		{
			window.draw(m_selectExit);
		}

	}
	
	

	window.draw(m_resume);
	window.draw(m_options);
	window.draw(m_exit);

	window.display();
}
