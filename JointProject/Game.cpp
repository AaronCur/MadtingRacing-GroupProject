#include "Game.h"
#include <iostream>

/// <summary>
/// Aaron Curry //James Condon //Jake Comiskey
/// C00207200
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game():

	m_window(sf::VideoMode(1000, 650, 32), "Madting Racing"),
	m_currentGameState(GameState::MainMenu)

{

	if (!m_agentOrange.loadFromFile("AGENTORANGE.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
		m_mainMenu = new MainMenu(*this, m_agentOrange);
	}

	m_mainMenu = new MainMenu(*this, m_agentOrange);
	m_licenseScreen = new License(*this, m_comicSans);
	m_splashScreen = new Splash(*this, m_agentOrange);
	m_helpScreen = new Help(*this, m_comicSans);
	m_options = new Options(*this, m_comicSans);
	m_gameScreen = new GameScreen(*this, m_agentOrange);
	m_pause = new Pause(*this, m_agentOrange);
	m_pauseOptions = new PauseOptions(*this, m_agentOrange);
	m_helpOptions = new OptionsHelp(*this, m_agentOrange);
	m_carSelectScreen = new CarSelect(*this, m_agentOrange);
	m_player = new Player(*this, *m_carSelectScreen);
	controller = new Xbox360Controller();

	//miniMapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.35f));
	//m_miniMap.setView(miniMapView);
	
}
Game::~Game()
{
	delete(m_splashScreen);
	delete(m_licenseScreen);
	delete(m_helpScreen);
	delete(m_options);
	delete(m_gameScreen);
	delete(m_pause);
	delete(m_pauseOptions);
	delete(m_helpOptions);
	delete(m_carSelectScreen);
	std::cout << "destructing game" << std::endl;
}

/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	
	
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}
/// <summary>
/// setd the current game state 
/// </summary>
/// <param name="gameState"></param>
void Game::setGameState(GameState gameState)
{
	m_currentGameState = gameState;
}

/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		
		//To check for the Akeypress to transition from splash screen to main menu
		if (controller->m_currentState.A == true && m_currentGameState == GameState::License)
		{
			m_licenseScreen->checkButtonPress();
		}
		if (m_mainMenu->close)
		{
			m_window.close();
		}

	}
}


/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(sf::Time time)
{
	switch (m_currentGameState)
	{
	case GameState::None:
	//	m_splashScreen->print(time);
		std::cout << "no GameState" << std::endl;
		break;
	case GameState::Splash:
		controller->update();
		m_splashScreen->update(time);
		break;
	case GameState::License:
		controller->update();
		m_licenseScreen->update(time);
		break;
	case GameState::MainMenu:
		m_mainMenu->update(time, *controller);
		controller->update();
		break;
	case GameState::Help:
		controller->update();
		m_helpScreen->update(time, *controller);
		break;
		controller->update();
		m_helpScreen->update(time, *controller);
	case GameState::Options:
		controller->update();
		m_options->update(time, *controller);
		break;
	case GameState::GameScreen:
		controller->update();
		m_gameScreen->update(time, *controller);
		m_player->update(time, *controller, *m_carSelectScreen);
		break;
	case GameState::CarSelect:
		controller->update();
		m_carSelectScreen->update(time, *controller);
		break;
	case GameState::Pause:
		controller->update();
		m_pause->update(time, *controller);
		break;
	case GameState::PauseOptions:
		controller->update();
		m_pauseOptions->update(time, *controller);
		break;
	case GameState::OptionsHelp:
		controller->update();
		m_helpOptions->update(time, *controller);
		break;
	default:
		break;
		
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	switch (m_currentGameState)
	{
	case GameState::Splash:
		m_splashScreen->render(m_window);
		break;
	case GameState::License:
		m_licenseScreen->render(m_window);
		break;
	case GameState::MainMenu:
		m_mainMenu->render(m_window);
		break;
	case GameState::Help:
		m_helpScreen->render(m_window);
		break;
	case GameState::Options:
		m_options->render(m_window);
		break;
	case GameState::GameScreen :
		m_player->render(m_window);
		m_gameScreen->render(m_window, *m_player);
		
		break;
	case GameState::CarSelect:
		m_carSelectScreen->render(m_window);
		break;
	case GameState::Pause:
		m_pause->render(m_window);
		break;
	case GameState::PauseOptions:
		m_pauseOptions->render(m_window);
		break;
	case GameState::OptionsHelp:
		m_helpOptions->render(m_window);
		break;
	default:
		break;

	}
	m_window.display();
	
}


