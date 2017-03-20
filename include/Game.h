#pragma once

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Splash.h"
#include "Xbox360Controller.h"
#include "License.h"
#include "MainMenu.h"
#include "Help.h"
#include "Options.h"
#include "GameScreen.h"
#include "Player.h"
#include "AI.h"

/// <summary>
/// @brief Main class for the SFML Playground project.
/// author James Condon
/// This will be a single class framework for learning about SFML.
/// </summary>

//each class is declared
class License;
class Splash;
class MainMenu;
class Help;
class Options;
class GameScreen;
class Player;
class Ai;

enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Options,
	Upgrade,
	Exit,
	HighScores,
	Help,
	GameScreen
};

class Game
{
public:
	Game();
	void run();
	GameState m_currentGameState;
	GameState m_previousGameState;
	void setGameState(GameState gameState);
	std::vector<sf::CircleShape> m_nodes;
protected:
	void update(sf::Time time);
	void render();
	void processEvents();

	void processGameEvents();
	void generateWalls();
	void generatePath();
	
	sf::Sprite m_sprite;//spritesheet
	sf::Sprite m_sprite2;//spritesheet 
	sf::Texture m_texture;
	sf::Texture m_backgroundTexture;
	sf::Texture m_spriteSheetTexture;
	sf::Texture m_overTexture;
	sf::Sprite m_background;//backgoround sprite 
 
	sf::Clock m_clock;//game clock 
	std::vector<std::unique_ptr<sf::Sprite>> m_wallSprites;//memeber variuable for wall sprites 
	std::vector<std::unique_ptr<sf::Sprite>> m_pathSprites;
	sf::Vector2f currentPosition;
	LevelData m_level;
	PathData m_path;
	/************************************/
	Xbox360Controller *controller;
	// main window
	sf::RenderWindow m_window;
	//pointers set for all screens
	License *m_licenseScreen;
	Splash *m_splashScreen;
	MainMenu * m_mainMenu;
	sf::Font m_agentOrange;//font 
	Help * m_helpScreen;
	Options *m_options;
	sf::Font m_comicSans;//font 
	GameScreen *m_gameScreen;
	Player *m_player;
	Ai *m_ai;

};
