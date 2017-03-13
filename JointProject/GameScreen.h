#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

/// <summary>
/// MiniMap author Aaron Curry
/// time taken: 9:00 - 13:50

class Game;

class GameScreen
{
public:
	GameScreen(Game& game, sf::Font font);
	~GameScreen();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;

	sf::Font m_font;
	//Track sprite and texture
	sf::Texture trackTexture;
	sf::Sprite trackSprite;
	//Mini map track sprite and texture (added white outline) to distinguish from game screen view
	sf::Texture miniMapTexture;
	sf::Sprite miniMapSprite;
	
	//The two views that wil make up the render window
	sf::View gameView;
	sf::View miniMapView;
};

#endif // !Help

