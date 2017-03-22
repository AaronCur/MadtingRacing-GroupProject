/// <summary>
/// Worked on my Jake Comiskey
/// Time worked on : 
/// </summary>

#include "CarSelect.h"
#include <iostream>


CarSelect::CarSelect(Game & game, sf::Font font) :
	m_game(&game),
	m_agentOrange(font),
	m_speed("Speed:", m_agentOrange),
	m_brake("Brake:", m_agentOrange)
{

	//loading texture from file
	if (!m_carSheetTexture.loadFromFile("CarSprite.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	if (!m_selectTexture.loadFromFile("arrow.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}
	if (!m_speedTexture.loadFromFile("Speed.png"))
	{

	}

	if (!m_garageTexture.loadFromFile("garage.png"))
	{

	}



	//an array of sprites for the speed
	for (int i = 0; i < 6; i++)
	{
		m_speedSprite[i].setTexture(m_speedTexture);
	}
	m_speedSprite[0].setPosition(800, 410);
	m_speedSprite[1].setPosition(830, 410);
	m_speedSprite[2].setPosition(860, 410);
	m_speedSprite[3].setPosition(890, 410);
	m_speedSprite[4].setPosition(920, 410);
	m_speedSprite[5].setPosition(950, 410);

	//an array of sprites of the brake speed
	for (int i = 0; i < 6; i++)
	{
		m_brakeSprite[i].setTexture(m_speedTexture);
	}
	m_brakeSprite[0].setPosition(800, 465);
	m_brakeSprite[1].setPosition(830, 465);
	m_brakeSprite[2].setPosition(860, 465);
	m_brakeSprite[3].setPosition(890, 465);
	m_brakeSprite[4].setPosition(920, 465);
	m_brakeSprite[5].setPosition(950, 465);

	
	m_selectSpriteCarOne.setTexture(m_selectTexture);
	m_selectSpriteCarOne.setPosition(170, 130);
	m_selectSpriteCarOne.rotate(180);

	
	m_selectSpriteCarTwo.setTexture(m_selectTexture);
	m_selectSpriteCarTwo.setPosition(170, 330);
	m_selectSpriteCarTwo.rotate(180);

	
	m_selectSpriteCarThree.setTexture(m_selectTexture);
	m_selectSpriteCarThree.setPosition(170, 530 );
	m_selectSpriteCarThree.rotate(180);
	
	
	//pos of the first small car 
	m_carSelectOne.setTexture(m_carSheetTexture);
	sf::IntRect carOneRect(35, 30, 178, 313);
	m_carSelectOne.setTextureRect(carOneRect);
	m_carSelectOne.setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_carSelectOne.setPosition(70, 100);
	m_carSelectOne.setScale(.5, .5);

	//Big car one sprite
	m_carSelectOneBig.setTexture(m_carSheetTexture);
	m_carSelectOneBig.setTextureRect(carOneRect);
	m_carSelectOneBig.setPosition(400, 100);
	m_carSelectOneBig.setScale(1.5, 1.5);

	//pos of the second small car
	m_carSelectTwo.setTexture(m_carSheetTexture);
	sf::IntRect carTwoRec(399, 30, 176, 316);
	m_carSelectTwo.setTextureRect(carTwoRec);
	m_carSelectTwo.setPosition(30, 220);
	m_carSelectTwo.setScale(.5, .5);
	

	//the big car two sprite
	m_carSelectTwoBig.setTexture(m_carSheetTexture);
	m_carSelectTwoBig.setTextureRect(carTwoRec);
	m_carSelectTwoBig.setPosition(400, 100);
	m_carSelectTwoBig.setScale(1.5, 1.5);
	
	
	//pos of the third small car
	m_carSelectThree.setTexture(m_carSheetTexture);
	sf::IntRect carThreeRec(363, 551, 178, 308);
	m_carSelectThree.setTextureRect(carThreeRec);
	m_carSelectThree.setPosition(30, 430);
	m_carSelectThree.setScale(.5, .5);
	

	//the big car three sprite
	m_carSelectThreeBig.setTexture(m_carSheetTexture);
	m_carSelectThreeBig.setTextureRect(carThreeRec);
	m_carSelectThreeBig.setPosition(400, 100);
	m_carSelectThreeBig.setScale(1.5, 1.5);

	//background sprite
	m_garageSprite.setTexture(m_garageTexture);

	//text for screen
	m_speed.setPosition(660, 400);
	m_speed.setColor(sf::Color::Black);
	m_brake.setPosition(660, 450);
	m_brake.setColor(sf::Color::Black);
}
	

CarSelect::~CarSelect()
{
	std::cout << "destructing CarSelect " << std::endl;
}


void CarSelect::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;

	//check to see which car the user is over
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

	
	if (controller.m_currentState.DpadDown == false && controller.m_currentState.DpadUp == false)
	{
		pressed = false;
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

	//when b is pressed the player and button count to 0 so the user starts at the top again
	if (controller.m_currentState.B)
	{
		m_game->setGameState(GameState::MainMenu);
		buttonCount = 0;
	}

	if (buttonCount == 1)
	{
		carOne = true;
		carTwo = false;
		carThree = false;
		if (controller.m_currentState.A)
		{
			carOnePicked = true;
			m_game->setGameState(GameState::GameScreen);
		}

	}

	if (buttonCount == 2)
	{
		carOne = false;
		carTwo = true;
		carThree = false;
		if (controller.m_currentState.A)
		{
			carTwoPicked = true;
			m_game->setGameState(GameState::GameScreen);
		}
	}

	if (buttonCount == 3)
	{
		carOne = false;
		carTwo = false;
		carThree = true;
		if (controller.m_currentState.A)
		{
			carThreePicked = true;
			m_game->setGameState(GameState::GameScreen);
		}

	}
}


void CarSelect::render(sf::RenderWindow & window)
{


	window.draw(m_garageSprite);

	window.draw(m_carSelectOne);
	window.draw(m_carSelectTwo);
	window.draw(m_carSelectThree);
	window.draw(m_speed);
	window.draw(m_brake);
	

	//Draws first car and all its speed and break speed, when user is on it
	if (buttonCount == 1 && buttonOneSelected == true)
	{
		window.draw(m_selectSpriteCarOne);
		window.draw(m_carSelectOneBig);
		window.draw(m_speedSprite[0]);
		window.draw(m_speedSprite[1]); 
		window.draw(m_speedSprite[2]);
		window.draw(m_speedSprite[3]);
		window.draw(m_speedSprite[4]);
		window.draw(m_speedSprite[5]);


		window.draw(m_brakeSprite[0]);
		window.draw(m_brakeSprite[1]);
		window.draw(m_brakeSprite[2]);
	}
	//draws car two, when user is on it
	else if (buttonCount == 2 && buttonTwoSelected == true)
	{
		window.draw(m_selectSpriteCarTwo);
		window.draw(m_carSelectTwoBig);
		window.draw(m_speedSprite[0]);
		window.draw(m_speedSprite[1]);

		window.draw(m_brakeSprite[0]); 
		window.draw(m_brakeSprite[1]);
		window.draw(m_brakeSprite[2]);
		window.draw(m_brakeSprite[3]);
	}
	
	//draws car three, the big one when user is on it
	else if (buttonCount == 3 && buttonThreeSelected == true)
	{
		window.draw(m_selectSpriteCarThree);
		window.draw(m_carSelectThreeBig);
		window.draw(m_speedSprite[0]);
		window.draw(m_speedSprite[1]);
		window.draw(m_speedSprite[2]);

		window.draw(m_brakeSprite[0]);
		window.draw(m_brakeSprite[1]);
		window.draw(m_brakeSprite[2]);
		window.draw(m_brakeSprite[3]);
		window.draw(m_brakeSprite[4]);
	}
	
	
	
	


}