#pragma once
#ifndef  GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Splash.h"
#include "Xbox360Controller.h"
#include "License.h"
#include "MainMenu.h"
#include "Help.h"
#include "Options.h"
#include "GameScreen.h"
#include "Pause.h"
#include "PauseOptions.h"
#include "OptionsHelp.h"
#include "CarSelect.h"
#include "Player.h"
#include "Upgrade.h"

//each class is declared
class License;
class Splash;
class MainMenu;
class Help;
class Options;
class GameScreen;
class Pause;
class PauseOptions;
class OptionsHelp;
class CarSelect;
class Player;
class Upgrade;


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
	GameScreen,
<<<<<<< HEAD
	UpgradeScreen
=======
	Pause,
	PauseOptions,
	OptionsHelp,
	CarSelect
>>>>>>> 1ac788b8c3627e0751ea33b4156d25a0a3004141
};
class Game
{
public:
	Game();
	~Game();
	void run();
	GameState m_currentGameState;
	GameState m_previousGameState;
	void setGameState(GameState gameState);
	
protected:
	
	void update(sf::Time deltaTime);
	void render();
	void processEvents();
	
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
	Pause *m_pause;
	PauseOptions *m_pauseOptions;
	OptionsHelp *m_helpOptions;
	CarSelect *m_carSelectScreen;
	Player *m_player;
	Upgrade *m_upgradeScreen;

};
#endif // !GAME