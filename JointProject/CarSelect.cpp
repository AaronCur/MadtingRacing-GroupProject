#include "CarSelect.h"
#include <iostream>


CarSelect::CarSelect(Game & game, sf::Font font) :
	m_game(&game),
	m_agentOrange(font),
	m_speed("Speed:", m_agentOrange),
	m_brake("Brake:", m_agentOrange)
{
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

	m_selectSpriteCarOne.setTexture(m_selectTexture);
	m_selectSpriteCarOne.setPosition(170, 130);
	m_selectSpriteCarOne.rotate(180);

	m_selectSpriteCarTwo.setTexture(m_selectTexture);
	m_selectSpriteCarTwo.setPosition(170, 330);
	m_selectSpriteCarTwo.rotate(180);

	m_selectSpriteCarThree.setTexture(m_selectTexture);
	m_selectSpriteCarThree.setPosition(170, 530 );
	m_selectSpriteCarThree.rotate(180);

	m_carSelectOne.setTexture(m_carSheetTexture);
	sf::IntRect carOneRect(35, 30, 178, 313);
	m_carSelectOne.setTextureRect(carOneRect);
	m_carSelectOne.setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_carSelectOne.setPosition(70, 100);
	m_carSelectOne.setScale(.5, .5);

	m_carSelectOneBig.setTexture(m_carSheetTexture);
	m_carSelectOneBig.setTextureRect(carOneRect);
	m_carSelectOneBig.setPosition(400, 100);
	m_carSelectOneBig.setScale(1.5, 1.5);


	m_carSelectTwo.setTexture(m_carSheetTexture);
	sf::IntRect carTwoRec(399, 30, 176, 316);
	m_carSelectTwo.setTextureRect(carTwoRec);
	m_carSelectTwo.setPosition(30, 220);
	m_carSelectTwo.setScale(.5, .5);

	m_carSelectTwoBig.setTexture(m_carSheetTexture);
	m_carSelectTwoBig.setTextureRect(carTwoRec);
	m_carSelectTwoBig.setPosition(400, 100);
	m_carSelectTwoBig.setScale(1.5, 1.5);

	m_carSelectThree.setTexture(m_carSheetTexture);
	sf::IntRect carThreeRec(363, 551, 178, 308);
	m_carSelectThree.setTextureRect(carThreeRec);
	m_carSelectThree.setPosition(30, 430);
	m_carSelectThree.setScale(.5, .5);

	m_carSelectThreeBig.setTexture(m_carSheetTexture);
	m_carSelectThreeBig.setTextureRect(carThreeRec);
	m_carSelectThreeBig.setPosition(400, 100);
	m_carSelectThreeBig.setScale(1.5, 1.5);

	m_speed.setPosition(660, 400);
	m_brake.setPosition(660, 450);
}
	

CarSelect::~CarSelect()
{
	std::cout << "destructing CarSelect " << std::endl;
}


void CarSelect::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;


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

	if (controller.m_currentState.B)
	{
		m_game->setGameState(GameState::MainMenu);
	}

	if (buttonCount == 1 && controller.m_currentState.A)
	{
		m_carSelectOneBig.scale(.5, .5);
	}
}


void CarSelect::render(sf::RenderWindow & window)
{
	window.clear();

	window.draw(m_carSelectOne);
	window.draw(m_carSelectTwo);
	window.draw(m_carSelectThree);
	window.draw(m_speed);
	window.draw(m_brake);
	
	if (buttonCount == 1 && buttonOneSelected == true)
	{
		window.draw(m_selectSpriteCarOne);
		window.draw(m_carSelectOneBig);
	}

	else if (buttonCount == 2 && buttonTwoSelected == true)
	{
		window.draw(m_selectSpriteCarTwo);
		window.draw(m_carSelectTwoBig);
	}
	
	else if (buttonCount == 3 && buttonThreeSelected == true)
	{
		window.draw(m_selectSpriteCarThree);
		window.draw(m_carSelectThreeBig);
	}
	
	
	window.display();


}