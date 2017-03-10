#include "License.h"
#include <iostream>

License::License(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font),
	m_madTing("MADTING", m_meatLoaf, 170),
	m_racing("Racing", m_adventure, 70),
	m_continue("Press A To Continue", m_adventure, 50),
	alpha(0),
	alpha2(0),
	flip(false)

{
	if (!m_meatLoaf.loadFromFile("Meatloaf.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	if (!m_adventure.loadFromFile("c:/windows/fonts/Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	if (!m_track.loadFromFile("track2.png"))
	{
		std::cout << "problem loading texture" << std::endl;
	}

	m_trackSprite.setTexture(m_track);
	m_trackSprite.setPosition(0, 0);


	m_madTing.setPosition(255.0f, -600.0f);
	m_madTing.setColor(sf::Color::Black);
	//m_madTing.setFont(m_meatLoaf);

	m_racing.setPosition(400.0f, -100.0f);
	m_racing.setColor(sf::Color(255, 255, 255, alpha));
	//m_racing.setFont(m_adventure);

	m_continue.setPosition(300.0f, 590.0f);
	m_continue.setColor(sf::Color::White);
}

License::~License()
{
	std::cout << "destructing License " << std::endl;
}
void License::checkButtonPress()
{

	if (m_cumulativeTime.asSeconds() >= 6.5)
	{
		m_game->setGameState(GameState::MainMenu);

	}

}
void License::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;




	if (m_cumulativeTime.asSeconds() < 1.90)
	{

		m_madTing.move(0, 5);

	}
	else if (m_cumulativeTime.asSeconds() < 2.2)
	{
		m_madTing.move(0, -1);

	}
	else if (m_cumulativeTime.asSeconds() < 2.55)
	{
		m_madTing.move(0, 1);
	}
	else if (m_cumulativeTime.asSeconds() < 2.9)
	{
		m_madTing.move(0, -0.2);
	}
	else if (m_cumulativeTime.asSeconds() < 3.15)
	{
		m_madTing.move(0, 0.2);
	}



	if (m_racing.getPosition().y < 135)
	{
		m_racing.move(0, 5);
	}

	if (m_cumulativeTime.asSeconds() > 3 && alpha < 255)
	{
		alpha++;
		m_racing.setColor(sf::Color(0, 0, 0, alpha));

	}
	if (m_cumulativeTime.asSeconds() >= 6)
	{
		if (alpha2 >= 254)
		{
			flip = true;
		}
		else if (alpha2 <= 1)
		{
			flip = false;
		}

		if (flip == false)
		{
			alpha2 += 2;
			m_continue.setColor(sf::Color(255, 255, 255, alpha2));
		}
		else if (flip == true)
		{
			alpha2 -= 2;
			m_continue.setColor(sf::Color(255, 255, 255, alpha2));
		}
	}


}

void License::render(sf::RenderWindow & window)
{

	window.clear(sf::Color::White);
	window.draw(m_trackSprite);
	window.draw(m_madTing);
	window.draw(m_racing);
	if (m_cumulativeTime.asSeconds() >= 6)
	{
		window.draw(m_continue);
	}



	window.display();
}
