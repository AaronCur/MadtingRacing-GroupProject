#include "Game.h"
#include "SFML/Audio.hpp"

static double const MS_PER_UPDATE = 10.0;

Game::Game() :
	m_window(sf::VideoMode(1000, 650, 32), "Madting Racing"),
	m_currentGameState(GameState::Options)

{
	
	int currentLevel = 1;
	if (!m_agentOrange.loadFromFile("./resources/images/AGENTORANGE.ttf"))
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
	m_upgradeScreen = new Upgrade(*this, m_comicSans);
	m_carSelectScreen = new CarSelect(*this, m_agentOrange);
	m_player = new Player(*this, m_agentOrange);
	controller = new Xbox360Controller();

	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;

	}
	
	for (PathData const &path : m_level.m_paths)
	{
		sf::CircleShape circle(60);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		m_nodes.push_back(circle);
	}


	for (PathData const &path : m_level.m_pathsTwo)
	{
		sf::CircleShape circle(60);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		m_nodesTwo.push_back(circle);
	}
	
	for (PathData const &path : m_level.m_pathsThree)
	{
		sf::CircleShape circle(60);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		m_nodesThree.push_back(circle);
	}
	
	for (PathData const &path : m_level.m_pathsFour)
	{
		sf::CircleShape circle(60);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		m_nodesFour.push_back(circle);
	}

	m_ai = new Ai(*this, m_nodes, m_nodesTwo, m_nodesThree, m_nodesFour);
	


	if (!m_backgroundTexture.loadFromFile("./resources/images/track2.png"))

	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	//loads the spritesheet texture 
	if (!m_spriteSheetTexture.loadFromFile("./resources/images/track2.png"))

	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	/// loads the spritesheet texture 
	if (!m_texture.loadFromFile("./resources/images/Spritesheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	lapText.setFont(m_agentOrange);
	lapText.setString("Time: ");
	lapText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	lapText.setPosition(20, 40);
	lapText.setCharacterSize(40);
	
		generateWalls();
		generatePath();
		generatePathTwo();
		generatePathThree();

		
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
		delete(m_upgradeScreen);
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
/// this is where the walls are generated and created 
/// </summary>
void Game::generateWalls()
{
	//the rectangle for the wall from the spritesheet 
	sf::IntRect wallRect(2, 129, 33, 23);
	for (ObstacleData const &obstacle : m_level.m_obstacles)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(wallRect);
		sprite->setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite->setPosition(obstacle.m_position);
		sprite->setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(std::move(sprite));

	}
}
/// <summary>
/// this is where the walls are generated and created 
/// </summary>
void Game::generatePath()
{
	//the rectangle for the wall from the spritesheet 
	sf::IntRect pathRect(2, 129, 33, 23);
	for (PathData const &path : m_level.m_paths)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(pathRect);
		sprite->setOrigin(pathRect.width / 2.0, pathRect.height / 2.0);
		sprite->setPosition(path.m_position);
		m_pathSprites.push_back(std::move(sprite));
		
	}
}

/// <summary>
/// this is where the walls are generated and created 
/// </summary>
void Game::generatePathTwo()
{
	//the rectangle for the wall from the spritesheet 
	sf::IntRect pathRect(2, 129, 33, 23);
	for (PathData const &path : m_level.m_pathsTwo)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(pathRect);
		sprite->setOrigin(pathRect.width / 2.0, pathRect.height / 2.0);
		sprite->setPosition(path.m_position);
		m_pathSprites.push_back(std::move(sprite));

	}
}

/// <summary>
/// this is where the walls are generated and created 
/// </summary>
void Game::generatePathThree()
{
	//the rectangle for the wall from the spritesheet 
	sf::IntRect pathRect(2, 129, 33, 23);
	for (PathData const &path : m_level.m_pathsThree)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(pathRect);
		sprite->setOrigin(pathRect.width / 2.0, pathRect.height / 2.0);
		sprite->setPosition(path.m_position);
		m_pathSprites.push_back(std::move(sprite));

	}
}

/// <summary>
/// sets the current game state 
/// </summary>
/// <param name="gameState"></param>
void Game::setGameState(GameState gameState)
{
	m_currentGameState = gameState;
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents()
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
	/*controller->update();*/
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
	case GameState::Upgrade:
		controller->update();
		m_upgradeScreen->update(time, *controller, *m_player);
		break;
	case GameState::Help:
		controller->update();
		m_helpScreen->update(time, *controller);
		break;
	case GameState::Options:
		controller->update();
		m_options->update(time, *controller);
		break;
	case GameState::GameScreen:
		
		controller->update();
		m_player->update(time, *controller, *m_carSelectScreen);
		m_ai->update(time, *controller, *m_player);
		m_gameScreen->update(time, *controller);	
		break;
	case GameState::CarSelect:
		controller->update();
		m_carSelectScreen->update(time, *controller);
		break;
	case GameState::Pause:
		controller->update();
		m_pause->update(time, *controller, *m_player);
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
	case GameState::GameScreen:
		
		m_player->render(m_window);
		m_ai->render(m_window);
		/*m_window.draw(m_background);*/
		/*for (auto &m_sprite : m_pathSprites)
		{
			m_window.draw(*m_sprite);
		}
		for (auto &m_sprite : m_wallSprites)
		{
			m_window.draw(*m_sprite);
		}*/
		m_gameScreen->render(m_window, *m_player, *m_ai);
		
		break;
	case GameState::CarSelect:
		m_carSelectScreen->render(m_window, *m_upgradeScreen);
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
	case GameState::Upgrade:
		m_upgradeScreen->render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}


