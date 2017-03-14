#include "CarSelect.h"
#include <iostream>


CarSelect::CarSelect(Game & game, sf::Font font) :
	m_game(&game),
	m_agentOrange(font)
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

	m_selectSprite.setTexture(m_selectTexture);

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
	m_carSelectTwo.setPosition(30, 250);
	m_carSelectTwo.setScale(.5, .5);
}
	

CarSelect::~CarSelect()
{
	std::cout << "destructing CarSelect " << std::endl;
}


void CarSelect::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;


}


void CarSelect::render(sf::RenderWindow & window)
{
	/*window.clear();*/

	window.draw(m_carSelectOne);
	window.draw(m_carSelectOneBig);
	window.draw(m_carSelectTwo);
	window.display();


}