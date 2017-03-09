#include "Splash.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)
{


}

Splash::~Splash()
{
	std::cout << "destructing Splash" << std::endl;
}

void Splash::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;

}
//Switches the gamestate when this method is called
void Splash::anyKeyPress()
{
	m_game->setGameState(GameState::Help);
}

void Splash::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Blue);
	window.display();
}