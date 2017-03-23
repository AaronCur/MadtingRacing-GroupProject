#include "Options.h"
#include <iostream>
/// <summary>
/// author James Condon
/// time taken: 10:00 - 15:00
/// Aaron Curry - worked on 17:00 - 18:30
/// James Condon worked on 12:00 - 13:00
/// </summary>
Options::Options(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font),
	m_optionsTxt("Options", m_meatLoaf, 70)

{
	setPosition();
	//loads font from file 
	m_font.loadFromFile("./resources/images/AGENTORANGE.TTF");
	m_meatLoaf.loadFromFile("./resources/images/Meatloaf.ttf");

	if (!m_muteTexture[0].loadFromFile("./resources/images/unMute.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_muteTexture[1].loadFromFile("./resources/images/mute.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	m_muteSprite.setTexture(m_muteTexture[0]);

	m_optionsTxt.setPosition(790, -10);
	m_helpText.setFont(m_font);
	m_helpText.setString("Help");
	m_helpText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_helpText.setCharacterSize(40);

	currentSongtext.setFont(m_meatLoaf);
	currentSongtext.setString("Lil Jon & The East Side Boyz - Get Low");
	currentSongtext.setStyle(sf::Text::Bold);
	currentSongtext.setCharacterSize(30);
	currentSongtext.setPosition(1000, 610);

	m_highscoreText.setFont(m_font);
	m_highscoreText.setString("scores");
	m_highscoreText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_highscoreText.setCharacterSize(28);

	m_songtxt.setFont(m_font);
	m_songtxt.setString("SONGS");
	m_songtxt.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_songtxt.setCharacterSize(28);

	m_backgroundTexture.loadFromFile("./resources/images/background.png");
	m_markerTexture.loadFromFile("./resources/images/marker.png");
	m_buttonTexture.loadFromFile("./resources/images/button.png");
	m_songTextures[0].loadFromFile("./resources/images/songButton1.png");
	m_songTextures[1].loadFromFile("./resources/images/songButton2.png");
	m_songTextures[2].loadFromFile("./resources/images/songButton3.png");
	m_arrowTexture.loadFromFile("./resources/images/arrow.png");
	m_sliderTexture.loadFromFile("./resources/images/songButton.png");

	for (int i = 0; i < 2; i++)
	{
		m_buttonSprite[i].setTexture(m_buttonTexture);
	}
	for (int i = 0; i < 3; i++)
	{
		m_songSprite[i].setTexture(m_songTextures[i]);
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_markerSprite.setTexture(m_markerTexture);
	m_arrowSprite.setTexture(m_arrowTexture);
	m_sliderSprite.setTexture(m_sliderTexture);

	//SONGS ARE LOADED and loops are set and volume 
	song1.openFromFile("./resources/images/song1.wav");
	song2.openFromFile("./resources/images/song2.wav");
	song3.openFromFile("./resources/images/song3.wav");
	song1.play();
	song1.setLoop(true);
	song2.setLoop(true);
	song3.setLoop(true);
	song1.setVolume(volume);
	song2.setVolume(volume);
	song3.setVolume(volume);

	m_blankTexture.loadFromFile("./resources/images/blank.png");
	m_blankSprite.setTexture(m_blankTexture);

	if (!m_shader.loadFromFile("firstShader.txt", sf::Shader::Fragment))
	{
		std::cout << "Shader is not available" << std::endl;
	}

	m_shader.setParameter("time", 0);
	m_shader.setParameter("resolution", 1000, 650);

	m_blankSprite.setPosition(0, 0);

	if (!buffer.loadFromFile("./resources/images/button.wav"))
	{
		std::string main("Error Loading sound");
		throw std::exception(main.c_str());
	}
	buttonPress.setBuffer(buffer);
}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}


void Options::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;
	if (ready)
	{
		currentSongtext.move(-2, 0);
		if (currentSongtext.getPosition().x <= -400)
		{
			currentSongtext.setPosition(1000, 610);
		}
		/// <summary>
		/// all the button positions are handled sets the arrow sprite to the button 
		/// changes the bools to allow navigation through the GUI
		/// </summary>
		/// <param name="deltaTime"></param>
		/// <param name="controller"></param>
		if (controller.m_currentState.DpadDown && onHelp && !controller.m_previousState.DpadDown)
		{
			m_arrowSprite.setPosition(140, 195);
			onHelp = false;
			onHighScores = true;
		}
		else if (controller.m_currentState.DpadDown && onHighScores && !controller.m_previousState.DpadDown)
		{
			m_arrowSprite.setPosition(45, 305);
			onHighScores = false;
			onSlider = true;
		}
		else if (controller.m_currentState.DpadDown && onSlider && !controller.m_previousState.DpadDown)
		{
			m_arrowSprite.setPosition(45, 430);
			onSlider = false;
			onMute = true;
		}
		else if (controller.m_currentState.DpadDown && onMute && !controller.m_previousState.DpadDown)
		{
			m_arrowSprite.setPosition(55, 560);
			onMute = false;
			onSong1 = true;
		}
		else if (controller.m_currentState.DpadDown && onSong1 && !controller.m_previousState.DpadDown)
		{
			m_arrowSprite.setPosition(140, 65);
			onSong1 = false;
			onHelp = true;
		}
		else if (controller.m_currentState.DpadRight && onSong1 && !controller.m_previousState.DpadRight)
		{
			m_arrowSprite.setPosition(205, 560);
			onSong1 = false;
			onSong2 = true;
		}
		else if (controller.m_currentState.DpadRight && onSong2 && !controller.m_previousState.DpadRight)
		{
			m_arrowSprite.setPosition(355, 560);
			onSong2 = false;
			onSong3 = true;
		}
		else if (controller.m_currentState.DpadRight && onSong3 && !controller.m_previousState.DpadRight)
		{
			m_arrowSprite.setPosition(55, 560);
			onSong3 = false;
			onSong1 = true;
		}


		if (controller.m_currentState.DpadUp && onHelp && !controller.m_previousState.DpadUp)
		{
			m_arrowSprite.setPosition(55, 560);
			onHelp = false;
			onSong1 = true;
		}
		else if (controller.m_currentState.DpadUp && onHighScores && !controller.m_previousState.DpadUp)
		{
			m_arrowSprite.setPosition(140, 65);
			onHighScores = false;
			onHelp = true;
		}
		else if (controller.m_currentState.DpadUp && onSlider && !controller.m_previousState.DpadUp)
		{
			m_arrowSprite.setPosition(140, 195);
			onSlider = false;
			onHighScores = true;
		}
		else if (controller.m_currentState.DpadUp && onMute && !controller.m_previousState.DpadUp)
		{
			m_arrowSprite.setPosition(45, 305);
			onMute = false;
			onSlider = true;
		}
		else if (controller.m_currentState.DpadUp && onSong1 && !controller.m_previousState.DpadUp)
		{
			m_arrowSprite.setPosition(45, 430);
			onSong1 = false;
			onMute = true;
		}
		else if (controller.m_currentState.DpadLeft && onSong1 && !controller.m_previousState.DpadLeft)
		{
			m_arrowSprite.setPosition(355, 560);
			onSong1 = false;
			onSong3 = true;
		}
		else if (controller.m_currentState.DpadLeft && onSong2 && !controller.m_previousState.DpadLeft)
		{
			m_arrowSprite.setPosition(55, 560);
			onSong2 = false;
			onSong1 = true;
		}
		else if (controller.m_currentState.DpadLeft && onSong3 && !controller.m_previousState.DpadLeft)
		{
			m_arrowSprite.setPosition(205, 560);
			onSong3 = false;
			onSong2 = true;
		}


		else if (controller.m_currentState.B && !controller.m_previousState.B)
		{

			m_game->setGameState(GameState::MainMenu);
			ready = false;
			setPosition();

		}



		if (controller.m_currentState.DpadRight && onSlider)
		{
			increaseVolume();
		}
		else if (controller.m_currentState.DpadLeft && onSlider)
		{
			decreaseVolume();
		}
		/// <summary>
		/// changes all the songs stops and plays each song that is chosen 
		/// </summary>
		/// <param name="deltaTime"></param>
		/// <param name="controller"></param>
		if (controller.m_currentState.A && onSong1 && !controller.m_previousState.A)
		{
			buttonPress.play();
			song1.play();
			song2.stop();
			song3.stop();
			currentSongtext.setString("Lil Jon & The East Side Boyz - Get Low");//changes the text
			currentSongtext.setPosition(1000, 610);
		}
		if (controller.m_currentState.A && onSong2 && !controller.m_previousState.A)
		{
			buttonPress.play();
			song1.stop();
			song2.play();
			song3.stop();
			currentSongtext.setString("Snoop Dogg ft. The Doors - Riders On The Storm ");//changes the text
			currentSongtext.setPosition(1000, 610);
		}
		if (controller.m_currentState.A && onSong3 && !controller.m_previousState.A)
		{
			buttonPress.play();
			song1.stop();
			song2.stop();
			song3.play();
			currentSongtext.setString("Smash Mouth - All Star");//changes the text
			currentSongtext.setPosition(1000, 610);
		}
		//Stops player from going straight to help after selecting options if A button is held
		//Button has to be released and then pressed before allowing the player to go to the help menu
		if (controller.m_currentState.A && controller.m_previousState.A == false && onHelp)
		{
			buttonPress.play();
			m_game->setGameState(GameState::Help);
		}
	}

	//changes the button to mute 
	if (controller.m_currentState.A && onMute && !controller.m_previousState.A && !changed)
	{
		buttonPress.play();
		changed = true;
		if (changed)//stops all the music 
		{
			m_muteSprite.setTexture(m_muteTexture[1]);
			song1.stop();
			song2.stop();
			song3.stop();
		}
		else//resets songs and texture 
		{
			m_muteSprite.setTexture(m_muteTexture[0]);
			song1.play();
		}
	}
	//changes the button to un mute 
	else if (controller.m_currentState.A && onMute && !controller.m_previousState.A && changed)
	{
		buttonPress.play();
		changed = false;
		if (changed)//stops all the music 
		{
			m_muteSprite.setTexture(m_muteTexture[1]);
			song1.stop();
			song2.stop();
			song3.stop();
		}
		else//resets the music and texture 
		{
			m_muteSprite.setTexture(m_muteTexture[0]);
			song1.play();
		}
	}

	controller.m_previousState = controller.m_currentState;

	buttonUpdate();
	//moves all the sprites and texture to animate on the screen 
	if (m_sliderSprite.getPosition().x > 100)
	{
		m_sliderSprite.move(-12, 0);
		m_buttonSprite[0].move(-12, 0);
		m_buttonSprite[1].move(-12, 0);
		m_songSprite[0].move(-12, 0);
		m_songSprite[1].move(-12, 0);
		m_songSprite[2].move(-12, 0);
		m_arrowSprite.move(-12, 0);
		m_helpText.move(-12, 0);
		m_highscoreText.move(-12, 0);
		m_songtxt.move(-12, 0);
		m_muteSprite.move(-12, 0);
	}
	else
	{
		ready = true;
	}
	if (ready)//if sprites are in position sets the marker 
	{
		m_markerSprite.setPosition(value, 310);
	}
}

void Options::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	window.draw(m_blankSprite, &m_shader);
	for (int i = 0; i < 2; i++)
	{
		window.draw(m_buttonSprite[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_songSprite[i]);
	}
	window.draw(m_optionsTxt);
	window.draw(m_arrowSprite);
	window.draw(m_sliderSprite);
	//only draws the marker when everything is in position 
	if (ready)
	{
		window.draw(m_markerSprite);
	}

	window.draw(m_helpText);
	window.draw(m_highscoreText);
	window.draw(m_songtxt);
	window.draw(currentSongtext);
	window.draw(m_muteSprite);
}
/// <summary>
/// updates all the colors of the buttons is they are pressed 
/// </summary>
void Options::buttonUpdate()
{
	if (onHelp) {
		m_helpText.setColor(sf::Color::Yellow);
	}
	else {
		m_helpText.setColor(sf::Color::White);
	}
	if (onHighScores) {
		m_highscoreText.setColor(sf::Color::Yellow);
	}
	else {
		m_highscoreText.setColor(sf::Color::White);
	}
	if (onSong1) {
		m_songSprite[0].setColor(sf::Color::Yellow);
	}
	else {
		m_songSprite[0].setColor(sf::Color::White);
	}
	if (onSong2) {
		m_songSprite[1].setColor(sf::Color::Yellow);
	}
	else {
		m_songSprite[1].setColor(sf::Color::White);
	}
	if (onSong3) {
		m_songSprite[2].setColor(sf::Color::Yellow);
	}
	else {
		m_songSprite[2].setColor(sf::Color::White);
	}
	if (onSlider) {
		m_markerSprite.setColor(sf::Color::Yellow);
	}
	else {
		m_markerSprite.setColor(sf::Color::White);
	}
	if (onSong1 || onSong2 || onSong3) {
		m_songtxt.setColor(sf::Color::Yellow);
	}
	else {
		m_songtxt.setColor(sf::Color::White);
	}
}
/// <summary>
/// sets ll the positions of all the sprites and texts 
/// in the game and is called in the initialise 
/// </summary>
void Options::setPosition()
{
	m_sliderSprite.setPosition(1100, 300);
	m_buttonSprite[0].setPosition(1100, 50);
	m_buttonSprite[1].setPosition(1100, 180);
	m_songSprite[0].setPosition(1100, 530);
	m_songSprite[1].setPosition(1250, 530);
	m_songSprite[2].setPosition(1400, 530);
	m_arrowSprite.setPosition(1140, 65);
	m_helpText.setPosition(1220, 65);
	m_highscoreText.setPosition(1210, 205);
	m_songtxt.setPosition(1520, 560);
	m_muteSprite.setPosition(1100, 400);


}
/// <summary>
/// increases the volume of the slider 
/// adds to the volume by a float volume 
/// sets all the songs to the volume 
/// </summary>
void Options::increaseVolume()
{
	if (m_markerSprite.getPosition().x <= 620)
	{
		value++;
		volume = volume + 0.1f;
		song1.setVolume(volume);
		song2.setVolume(volume);
		song3.setVolume(volume);
		m_markerSprite.setPosition(value, 310);
	}

}
/// <summary>
/// decreases the volume of the slider 
/// adds to the volume by a float volume 
/// sets all the songs to the volume 
/// </summary>
void Options::decreaseVolume()
{
	if (m_markerSprite.getPosition().x >= 140)
	{
		volume = volume - 0.21f;
		song1.setVolume(volume);
		song2.setVolume(volume);
		song3.setVolume(volume);
		value--;
		m_markerSprite.setPosition(value, 310);
	}
}




