#include<iostream>
#include"GameScreen.h"

/// <summary>
/// MiniMap author Aaron Curry
/// time taken: 9:00 - 13:50

GameScreen::GameScreen(Game & game, sf::Font font) :
	m_game(&game)
{
	m_font.loadFromFile("./resources/images/AGENTORANGE.TTF");
	circle = sf::CircleShape(40);
	circle2 = sf::CircleShape(40);
	circle3 = sf::CircleShape(40);
	circle4 = sf::CircleShape(40);
	circle5 = sf::CircleShape(40);
	//Load in the gamescreen track texture
	if (!trackTexture.loadFromFile("./resources/images/track2.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	//Load in the track texture for the minimap (added whie border, to distinguish 
	if (!miniMapTexture.loadFromFile("./resources/images/bigTrackMini.png"))
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
	/*gameView.setSize(1000, 650);*/
	//Set the origin to the center
	gameView.setCenter(500, 325);
	
	
	//Set up second view for minimap, scale and positioned to the top right hand corner
	miniMapView.setViewport(sf::FloatRect(0.73f, 0.02f, 0.25f, 0.25f));
	miniMapView.setSize(4000, 2600);
	miniMapView.setCenter(2000, 1300);
	/*miniMapWindow.setView(miniMapView);*/
	

}
GameScreen::~GameScreen()
{
	std::cout << "destructing Help" << std::endl;
}

void GameScreen::update(sf::Time dt, Xbox360Controller&controller)
{
	//follow.setCenter(rec.getPosition()); //put in player postion where rec is.
}

void GameScreen::render(sf::RenderWindow & window, Player& player, Ai & ai)
{
	circle2.setPosition(ai.m_aiSprite[0].getPosition());
	circle2.setOutlineColor(sf::Color::Black);
	circle2.setFillColor(sf::Color::White);

	circle3.setPosition(ai.m_aiSprite[1].getPosition());
	circle3.setOutlineColor(sf::Color::Black);
	circle3.setFillColor(sf::Color::Magenta);

	circle4.setPosition(ai.m_aiSprite[2].getPosition());
	circle4.setOutlineColor(sf::Color::Black);
	circle4.setFillColor(sf::Color::Yellow);
	
	circle5.setPosition(ai.m_aiSprite[3].getPosition());
	circle5.setOutlineColor(sf::Color::Black);
	circle5.setFillColor(sf::Color::Blue);
	//Draw game view
	circle.setPosition(player.carSprite.getPosition());
	circle.setOutlineColor(sf::Color::Black);
	circle.setFillColor(sf::Color::Green);
	/*window.setView(gameView);
	window.draw(trackSprite);*/
	//Draw mini map view
	window.setView(miniMapView);
	window.draw(miniMapSprite);
	/*window.setView(follow);*/
	//For future use 
	//To scale the screen
	window.draw(circle);
	window.draw(circle2);
	window.draw(circle3);
	window.draw(circle4);
	window.draw(circle5);
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