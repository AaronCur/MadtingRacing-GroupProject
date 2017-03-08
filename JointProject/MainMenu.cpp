#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font)	
{
	if (!m_mainMenuTexture.loadFromFile("button.png"))
	{
		std::string main("Error Loading Texture");
		throw std::exception(main.c_str());
	}

	m_mainMenuSprite.setTexture(m_mainMenuTexture);
	m_mainMenuSprite.setPosition(-10, 30);

	m_mainMenuSpriteTwo.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteTwo.setPosition(590, 180);

	m_mainMenuSpriteThree.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteThree.setPosition(-10, 330);

	m_mainMenuSpriteFour.setTexture(m_mainMenuTexture);
	m_mainMenuSpriteFour.setPosition(590, 480);
}

MainMenu::~MainMenu()
{
	std::cout << "destructing Splash" << std::endl;
	
}


void MainMenu::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	if (m_mainMenuSprite.getPosition().x > -11)
	{
		if (m_mainMenuSprite.getPosition().x <= 180)
		{
			std::cout << m_mainMenuSpriteFour.getPosition().y << std::endl;
			//moving in from the right
			m_mainMenuSprite.move(10, 0);
			m_mainMenuSpriteThree.move(14, 0);

			//moving in from the left
			m_mainMenuSpriteTwo.move(-18, 0);
			m_mainMenuSpriteFour.move(-14, 0);
		}
	}

}

void MainMenu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	window.draw(m_mainMenuSprite);
	window.draw(m_mainMenuSpriteTwo);
	window.draw(m_mainMenuSpriteThree);
	window.draw(m_mainMenuSpriteFour);
	window.display();
}

