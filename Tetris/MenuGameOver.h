#pragma once
#include "Button.h"
class MenuGameOver
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	Button buttonPlayAgain;
	Button buttonExit;

	sf::Font font;
	sf::Text textScore;
	sf::Text text;

	sf::SoundBuffer soundBufferGameOver;
	sf::Sound soundGameOver;

	float dxButtonMenuOver;

	bool checkRestartGame;
	bool checkEndGame;

	void initVariables();
	void initSound();
	void initButtonPlayAgain();
	void initFont();
	void initText();
	void initButtonExit();
	void initTexture();
	void initSprite();
public:
	MenuGameOver();
	~MenuGameOver();

	bool getCheckRestartGame();
	bool getIsMouseRestartGame(sf::RenderWindow& window);
	bool getIsMouseExit(sf::RenderWindow& window);

	void updateText(int score);
	void updateButton(bool endGame, bool startGame, bool restartGame);
	void update(bool endGame, bool startGame, bool restartGame,int score);
	void render(sf::RenderTarget& target);
};

