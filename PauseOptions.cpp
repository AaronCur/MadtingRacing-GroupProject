#include "PauseOptions.h"
#include <iostream>
/// <summary>
/// Aaron Curry - worked on 20:00 - 20:20
/// </summary>
PauseOptions::PauseOptions(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_options("Options", m_font, 35)

{

	m_options.setPosition(740, 18);
	m_options.setStyle(sf::Text::Bold);
	m_helpText.setFont(m_font);
	m_helpText.setString("Help");
	m_helpText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_helpText.setCharacterSize(40);

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
	setPosition();

}

PauseOptions::~PauseOptions()
{
	std::cout << "destructing License " << std::endl;
}


void PauseOptions::update(sf::Time deltaTime, Xbox360Controller &controller)
{
	m_cumulativeTime += deltaTime;

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
		m_arrowSprite.setPosition(55, 560);
		onSlider = false;
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
	else if (controller.m_currentState.DpadUp && onSong1 && !controller.m_previousState.DpadUp)
	{
		m_arrowSprite.setPosition(45, 305);
		onSong1 = false;
		onSlider = true;
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

		m_game->setGameState(GameState::Pause);

	}




	if (controller.m_currentState.DpadRight && onSlider)
	{
		increaseVolume();
	}
	else if (controller.m_currentState.DpadLeft && onSlider)
	{
		decreaseVolume();
	}


	//Stops player from going straight to help after selecting options if A button is held
	//Button has to be released and then pressed before allowing the player to go to the help menu
	if (controller.m_currentState.A && controller.m_previousState.A == false && onHelp)
	{
		m_game->setGameState(GameState::OptionsHelp);
	}

	buttonUpdate();
}

void PauseOptions::render(sf::RenderWindow & window)
{

	window.draw(m_backgroundSprite);
	for (int i = 0; i < 2; i++)
	{
		window.draw(m_buttonSprite[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_songSprite[i]);
	}

	window.draw(m_arrowSprite);
	window.draw(m_sliderSprite);
	window.draw(m_markerSprite);
	window.draw(m_helpText);
	window.draw(m_highscoreText);
	window.draw(m_songtxt);
	window.draw(m_options);

}
void PauseOptions::buttonUpdate()
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
void PauseOptions::setPosition()
{
	m_sliderSprite.setPosition(100, 300);
	m_markerSprite.setPosition(value, 310);
	m_buttonSprite[0].setPosition(100, 50);
	m_buttonSprite[1].setPosition(100, 180);
	m_songSprite[0].setPosition(100, 530);
	m_songSprite[1].setPosition(250, 530);
	m_songSprite[2].setPosition(400, 530);
	m_arrowSprite.setPosition(140, 65);
	m_helpText.setPosition(220, 65);
	m_highscoreText.setPosition(210, 205);
	m_songtxt.setPosition(520, 560);


}

void PauseOptions::increaseVolume()
{
	if (m_markerSprite.getPosition().x <= 620)
	{
		value++;
		m_markerSprite.setPosition(value, 310);
	}

}

void PauseOptions::decreaseVolume()
{
	if (m_markerSprite.getPosition().x >= 140)
	{
		value--;
		m_markerSprite.setPosition(value, 310);
	}
}