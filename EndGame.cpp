#include "EndGame.h"

EndGame::EndGame(Game& game, sf::Font font) :

	m_game(&game),
	m_font(font),
	m_endGame("End Game", m_meatLoaf, 70),
	m_place("You Placed: ", m_font),
	m_money("Money: ", m_font),
	m_firstPlace("1st", m_font),
	m_notFirst("Not First", m_font),
	m_firstPlacePrize("800!!", m_font),
	m_otherPrize("200", m_font),
	m_goUpgrade("Press A to go Upgrade Screen", m_font),
	alpha(0)
{
	m_meatLoaf.loadFromFile("./resources/images/Meatloaf.ttf");
	m_endGame.setPosition(740, -10);


	if (!m_backGroundTexture.loadFromFile("./resources/images/background.png"))
	{

	}
	m_backGroundSprite.setTexture(m_backGroundTexture);

	m_place.setPosition(250, 200);
	m_place.setScale(1.3, 1.3);

	m_firstPlace.setPosition(600, 200);
	m_firstPlace.setScale(1.3, 1.3);

	m_notFirst.setPosition(600, 200);
	m_notFirst.setScale(1.3, 1.3);

	m_money.setPosition(250, 300);
	m_money.setScale(1.3, 1.3);

	m_firstPlacePrize.setPosition(600, 300);
	m_firstPlacePrize.setScale(1.3, 1.3);

	m_otherPrize.setPosition(600, 300);
	m_otherPrize.setScale(1.3, 1.3);

	m_goUpgrade.setPosition(200, 500);
	m_goUpgrade.setColor(sf::Color::Black);

	//Set up the game view so its 1 to 1 scale with game window
	m_endGameView.setViewport(sf::FloatRect(0, 0, 1, 1));
	//Set the view size
	m_endGameView.setSize(1000, 650);
	//Set the origin to the center
	m_endGameView.setCenter(500, 325);
}

EndGame::~EndGame()
{



}

void EndGame::update(sf::Time dt, Xbox360Controller& controller, Player& player, Ai & ai, Upgrade & upgrade)
{
	m_cumulativeTime += dt;




	//To get the text to pulse 
	if (m_cumulativeTime.asSeconds() > 1)
	{
		//Decides which way the alpha will be incremented ( negative or possitive)
		if (alpha >= 254)
		{
			flip = true;
		}
		else if (alpha <= 1)
		{
			flip = false;
		}
		//Increments the alpha value
		if (flip == false)
		{
			alpha += 2;
			m_goUpgrade.setColor(sf::Color(0, 0, 102, alpha));
		}
		else if (flip == true)
		{
			alpha -= 2;
			m_goUpgrade.setColor(sf::Color(0, 0, 102, alpha));
		}

	}

	if (controller.m_currentState.A)
	{
		m_game->setGameState(GameState::Upgrade);
		player.restartGame = true;
	}

	if (player.lapCount < 3 && asign == true )
	{
		upgrade.m_funds += 200;
		playerLose = true;
		asign = false;
	}
	else if (ai.first == false && asign == true || ai.count1 < 3 && player.lapCount == 3 && asign == true)
	{
		upgrade.m_funds += 800;
		playerWin = true;
		asign = false;
	}
}

void EndGame::render(sf::RenderWindow & window)
{

	window.setView(m_endGameView);
	window.draw(m_backGroundSprite);
	window.draw(m_endGame);
	window.draw(m_place);
	window.draw(m_money);

	if (playerWin == true)
	{
		window.draw(m_firstPlace);
		window.draw(m_firstPlacePrize);
	}


	if (playerLose == true)
	{
		window.draw(m_notFirst);
		window.draw(m_otherPrize);
	}



	window.draw(m_goUpgrade);
}