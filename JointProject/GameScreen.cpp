#include<iostream>
#include"GameScreen.h"

/// <summary>
/// MiniMap author Aaron Curry
/// time taken: 9:00 - 13:50

GameScreen::GameScreen(Game & game, sf::Font font) :
	m_game(&game)
{
	m_font.loadFromFile("AGENTORANGE.TTF");
	circle = sf::CircleShape(40);
	rectangle = sf::RectangleShape(sf::Vector2f(10, 10));
	//Load in the gamescreen track texture
	/*if (!trackTexture.loadFromFile("track2.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}*/
	//Load in the track texture for the minimap (added whie border, to distinguish 
	if (!miniMapTexture.loadFromFile("bigTrack.png"))
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
	//gameView.setSize(4000, 2600);
	//Set the origin to the center
	gameView.setCenter(500, 325);
	
	
	//Set up second view for minimap, scale and positioned to the top right hand corner
	miniMapView.setViewport(sf::FloatRect(0.73f, 0.02f, 0.25f, 0.25f));
	miniMapView.setSize(4000, 2600);
	miniMapView.setCenter(2000, 1300);
	//miniMapWindow.setView(miniMapView);
	


}
GameScreen::~GameScreen()
{
	std::cout << "destructing Help" << std::endl;
}

void GameScreen::update(sf::Time dt, Xbox360Controller&controller)
{
	follow.setCenter(rec.getPosition()); //put in player postion where rec is.
}

void GameScreen::render(sf::RenderWindow & window, Player& player)
{
	
	//Draw game view
	//window.setView(gameView);
	circle.setPosition(player.carSprite.getPosition());
	circle.setOutlineColor(sf::Color::Black);
	circle.setFillColor(sf::Color::Green);
	//Draw mini map view
	window.setView(miniMapView);
	window.draw(miniMapSprite);
	//player.carSprite.setScale(1.2, 1.2);
	window.draw(circle);
	/*window.setView(follow);
	window.draw(trackSprite);*/
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

	
}