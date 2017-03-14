#include "Splash.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_globeText("prestige", m_font, 40),
	m_globeTextTwo("worldwide", m_font, 40)
{
	m_globeTexture.loadFromFile("./resources/images/globe.png");
	m_globeSprite.setTexture(m_globeTexture);
	m_globeSprite.setPosition(-250, 300);
	m_globeText.setPosition(390, 200);
	m_globeText.setFont(m_font);
	m_globeTextTwo.setPosition(355, 300);
	m_globeTextTwo.setFont(m_font);
	
}

Splash::~Splash()
{
	std::cout << "destructing Splash" << std::endl;
}

void Splash::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;
	if (m_cumulativeTime.asSeconds() > 8)
	{
		m_game->setGameState(GameState::License);

	}
	if (m_globeSprite.getPosition().x < 500)
	{
		m_globeSprite.move(4, 0);
	}
	if (m_cumulativeTime.asSeconds() > 5)
	{
		m_globeSprite.move(4, 0);
	}
	m_globeSprite.rotate(2);
	m_globeSprite.setOrigin(250, 250);
	
}
//Switches the gamestate when this method is called
void Splash::anyKeyPress()
{
	m_game->setGameState(GameState::Help);
}

void Splash::render(sf::RenderWindow & window)
{
	window.draw(m_globeSprite);
	window.draw(m_globeText);
	window.draw(m_globeTextTwo);
}