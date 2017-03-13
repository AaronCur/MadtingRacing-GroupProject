#include<iostream>
#include"GameScreen.h"

/// <summary>
/// MiniMap author Aaron Curry
/// time taken: 9:00 - 13:50

GameScreen::GameScreen(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)
{
	m_font.loadFromFile("AGENTORANGE.TTF");


	if (!trackTexture.loadFromFile("track2.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	if (!miniMapTexture.loadFromFile("trackMiniMap.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	trackSprite.setTexture(trackTexture);
	trackSprite.setPosition(0, 0);

	miniMapSprite.setTexture(miniMapTexture);


	//Set up the game view so its 1 to 1 scale with game window
	gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
	//Set the view size
	gameView.setSize(1000, 650);
	//Set the origin to the center
	gameView.setCenter(500, 325);
	
	
	//Set up second view for minimap, scale and positioned to the top right hand corner
	miniMapView.setViewport(sf::FloatRect(0.73f, 0.02f, 0.25f, 0.25f));
	miniMapView.setSize(1000, 650);
	miniMapView.setCenter(500, 325);
	//miniMapWindow.setView(miniMapView);
	

}
GameScreen::~GameScreen()
{
	std::cout << "destructing Help" << std::endl;
}

void GameScreen::update(sf::Time dt, Xbox360Controller&controller)
{
	
}

void GameScreen::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color::Blue);
	//Draw game view
	Window.setView(gameView);
	Window.draw(trackSprite);
	//Draw mini map view
	Window.setView(miniMapView);
	Window.draw(miniMapSprite);

	//For future use 
	//To scale the screen

	//sf::Event event;
	//while (Window.pollEvent(event))
	//{
	//	if (event.type == sf::Event::Resized)
	//	{
	//		sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
	//		Window.setView(sf::View(visibleArea));
	//		Window.draw(trackSprite);
	//		//Window.display();

	//	}
	//}

	Window.display();
}