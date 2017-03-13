#include "GameScreen.h"
#include <iostream>

//Jake Comiskey
//worked on for an hour

GameScreen::GameScreen(Game & game, sf::Font font) :
m_game(&game),
m_agentOrange(font)
{
	if (!m_trackTexture.loadFromFile("track3.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	m_trackSprite.setTexture(m_trackTexture);
}

GameScreen::~GameScreen()
{
	std::cout << "destructing GameScreen " << std::endl;
}


void GameScreen::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;

	follow.setCenter(rec.getPosition()); //put in player postion where rec is.
	
}


void GameScreen::render(sf::RenderWindow & window)
{
	window.clear();
	window.setView(follow);
	window.display();

	
}