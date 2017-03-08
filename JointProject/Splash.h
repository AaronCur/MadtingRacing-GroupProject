#pragma once
#ifndef SPLASH
#define SPLASH	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;

class Splash
{
public:
	Splash(Game& game, sf::Font font);
	~Splash();
	Xbox360Controller controller;
	//void changeScreen();//changes the sprite on screen 
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void anyKeyPress();
	//bool m_pressed;//allowing to change sprites 
	//void print(sf::Time deltaTime);
	
	
private:
	Game *m_game;//pointer to games class 
	sf::Time m_cumulativeTime;//the time 
	sf::Font m_comicSans;//font 
	sf::Text m_textMessage;//the text message 
	sf::Sprite m_splash;//first sprite
	sf::Texture m_texture;//first texture 
	int alpha;
	
};
#endif // !