#include<iostream>
#include"Help.h"

Help::Help(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)
{
	m_textMessage.setPosition(-100, 180);
	m_textMessage.setColor(sf::Color::White);
	m_by.setPosition(-100, 220);
	m_by.setColor(sf::Color::White);
	m_name.setPosition(-100, 260);
	m_name.setColor(sf::Color::White);

	if (!logoTexture.loadFromFile("help.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(0, 420);


}

Help::~Help()
{
	std::cout << "destructing Help" << std::endl;
}

void Help::update(sf::Time dt, Xbox360Controller&controller)
{
	m_cumulativeTime += dt;

	/*if (m_cumulativeTime.asSeconds() > 1)
	{
	m_game->setGameState(State::Splash);
	}*/

	if (logoSprite.getPosition().y > -421 && logoSprite.getPosition().y > 0)
	{
		alpha = alpha + 2.8;
		logoSprite.move(0, -5);
		logoSprite.setColor(sf::Color(255, 255, 255, alpha));
	}

	if (logoSprite.getPosition().y == 0)
	{
		logoSprite.move(0, 0);
		logoSprite.setColor(sf::Color(255, 255, 255, 255));
	}
	// Button to go back to previous menu
	if (controller.m_currentState.Y)
	{
		m_game->setGameState(GameState::Splash);
	}
}

void Help::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Green);
	window.draw(m_textMessage);
	window.draw(m_by);
	window.draw(logoSprite);
	window.draw(m_name);
	window.display();
}