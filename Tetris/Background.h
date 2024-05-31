#pragma once

#include "MenuGameOver.h"

class Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	Button buttonPlay;
	Button buttonPause;
	Button buttonContinue;



	float timer;
	float delay;
	sf::Clock clock;

	int dyButtonStart;
	int dyButtonPause;
	int dyButtonContinue;

	void initButtonPlay();
	void initButtonPause();
	void initButtonContinue();
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Background();
	~Background();

	bool getIsMousePlay(sf::RenderWindow& window);
	bool getIsMousePause(sf::RenderWindow& window);
	bool getIsMouseContinue(sf::RenderWindow& window);

	void updateButton(bool startGame,bool pauseGame);
	void updateTime();
	void update(bool startGame, bool pauseGame);
	void render(sf::RenderTarget& target);
	void renderHear(sf::RenderTarget& target);
	void renderButton(sf::RenderTarget& target, bool startGame, bool pauseGame);
};

