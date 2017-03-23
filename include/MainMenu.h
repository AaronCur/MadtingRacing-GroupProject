#ifndef MAINMENU
#define MAINMENU	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"
#include "Options.h"
#include "SFML\Audio.hpp"

class Game;
class Options;
class MainMenu
{
public:
	MainMenu(Game& Game, sf::Font font);
	~MainMenu();
	void update(sf::Time deltaTime, Xbox360Controller& controller);
	void render(sf::RenderWindow& window);
	bool close = false;
private:
	Game *m_game;//pointer to games class 
	sf::Time m_cumulativeTime;//the time 
	sf::Font m_font;
	sf::Window m_window;
	sf::Sprite m_mainMenuSprite;
	sf::Texture m_mainMenuTexture;
	sf::Sprite m_mainMenuSpriteTwo;
	sf::Sprite m_mainMenuSpriteThree;
	sf::Sprite m_mainMenuSpriteFour;
	sf::Text m_mainMenuTxt;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::Font m_meatLoaf;
	sf::Sprite m_select;
	sf::Sprite m_selectUpgrade;
	sf::Sprite m_selectOptions;
	sf::Sprite m_selectExit;
	sf::Texture m_selectTex;

	sf::Texture m_carSpriteSheet;
	sf::Sprite m_carOne;
	sf::Sprite m_carTwo;
	sf::Sound buttonPress;
	sf::SoundBuffer buffer;
	sf::Text m_play;
	sf::Text m_upgrades;
	sf::Text m_options;
	sf::Text m_exit;

	sf::Shader m_shader;
	float updateShader = 0;
	sf::Texture m_blankTexture;
	sf::Sprite m_blankSprite;

	sf::Time time;
	bool ready = false;
	bool buttonOneSelected = false;
	bool buttonTwoSelected = false;
	bool buttonThreeSelected = false;
	bool buttonFourSelected = false;
	int buttonCounter = 0;
	//variable for single press
	bool pressed = false;
	int alpha = 0;
	bool alphaCount = true;

	Options *m_optionScreen;
};
#endif // !