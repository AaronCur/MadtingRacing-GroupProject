#include "Pause.h"
#include <iostream>
/// <summary>
/// author Aaron Curry
/// time taken: 10:00 - 12:00
///				18:00 - 20:00
///             21:00 - 22:20
/// </summary>
Pause::Pause(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_resume("Resume", m_font, 30),
	m_options("Main Menu", m_font, 30),
	m_exit("Press B to exit to MAIN MENU", m_adventure, 30),
	m_paused("GAME PAUSED", m_font, 45),
	alpha(0),
	flip(false)
{
	if (!m_adventure.loadFromFile("./resources/images/Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	if (!m_buttonTexture.loadFromFile("./resources/images/button.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_selectTexture.loadFromFile("./resources/images/select.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_backgroundTexture.loadFromFile("./resources/images/background4.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	//Set the backdrop
	m_backgroundSprite.setTexture(m_backgroundTexture);


	m_selectBack.setTexture(m_selectTexture);
	m_selectBack.setPosition(385, 140);

	m_selectOptions.setTexture(m_selectTexture);
	m_selectOptions.setPosition(385, 360);


	m_buttonOne.setTexture(m_buttonTexture);
	m_buttonOne.setPosition(355, -150);

	m_buttonTwo.setTexture(m_buttonTexture);
	m_buttonTwo.setPosition(355, 700);




	//m_play.setPosition(320, 55);
	m_resume.setColor(sf::Color::White);
	m_resume.setScale(0.7, 1);
	m_resume.setPosition(3600, 140);
	m_options.setColor(sf::Color::White);
	m_options.setPosition(360, 360);
	m_paused.setColor(sf::Color::White);
	m_paused.setPosition(300, 250);
	m_paused.setStyle(sf::Text::Bold);

	//	m_exit.setFont(m_adventure);
	m_exit.setColor(sf::Color::Black);

	m_exit.setPosition(310, 510);


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


void Pause::update(sf::Time deltaTime, Xbox360Controller& controller, Player & player)
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
			//Initiates the out animations
			animaOut = true;
			selected = true;

		}
		//When animations are finished and the button was selected, then change gamestate
		if (animaOut == false && selected == true)
		{
			m_game->setGameState(GameState::GameScreen);
			selected = false;
		}
	}
	if (buttonTwoSelected == true)
	{

		if (controller.m_currentState.A && controller.m_previousState.A == false)
		{
			//initiates the out animations
			animaOut = true;

			selected = true;

		}
		//When the animations are done and the button was selected , then change game state
		if (animaOut == false && selected == true)
		{
			m_game->setGameState(GameState::MainMenu);
			selected = false;
		}
	}
	//When iniciated by the options / exit / b button presses the butttons animate off screen.
	//Also resets the bools so these animations are repeated when the player comes back to the screen.
	if (animaOut == true)
	{
		if (m_buttonOne.getPosition().y > -150)
		{
			m_buttonOne.move(0, -10);
		}
		if (m_buttonTwo.getPosition().y < 680)
		{
			m_buttonTwo.move(0, +10);
		}
		else
		{
			animaOut = false;
			animaIn = true;
		}
	}


	/*if (controller.m_currentState.B && controller.m_previousState.B == false)
	{
	animaOut = true;
	exit = true;

	}*/
	//Exits the game once the B button is pressed and after the animations going out are finished
	if (animaOut == false && exit == true)
	{
		player.restartGame = true;
		m_game->setGameState(GameState::MainMenu);
		exit = false;
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
	//When iniciated by the options / exit / b button presses the butttons animate off screen.
	//Also resets the bools so these animations are repeated when you come back to the screen.
	if (animaIn == true)
	{
		if (m_buttonOne.getPosition().y < 124)
		{
			m_buttonOne.move(0, 10);
		}
		if (m_buttonTwo.getPosition().y > 349)
		{
			m_buttonTwo.move(0, -10);

		}
		else
		{
			animaIn = false;
		}

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

	//Fades in the Game Paused text in time with the IN animations
	if (animaIn == true && alpha2 < 255)
	{
		alpha2 += 7.99;
		m_paused.setColor(sf::Color(255, 255, 255, alpha2));
	}
	//Fades in the Game Paused text in time with the OUT animations
	else if (animaOut == true && alpha2 > 0)
	{
		alpha2 -= 7;
		m_paused.setColor(sf::Color(255, 255, 255, alpha2));
	}


}

void Pause::render(sf::RenderWindow & window)
{



	window.setView(pause);
	window.draw(m_backgroundSprite);

	window.draw(m_buttonOne);
	window.draw(m_buttonTwo);
	//After the buttons are on screen the selector will appear
	if (animaIn == false && animaOut == false)
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
	//window.draw(m_exit);
	window.draw(m_paused);


}