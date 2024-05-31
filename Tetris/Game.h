#pragma once
#include "Tiles.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;
	sf::Text textScore;
	sf::Text hightScore;

	Tiles* tiles;
	Background background;
	MenuGameOver menuGameOver;

	

	sf::SoundBuffer soundBufferCursor;
	sf::Sound soundCursor;


	bool endGame;
	bool pauseGame;
	bool startGame;
	bool restartGame;

	void initVariables();
	void initSound();
	void initTiles();
	void initFont();
	void initText();
	void initWindow();


public:
	Game();
	~Game();

	const bool running() const;
	const bool endgame() const;

	
	void pollEvent();
	void updateTiles();
	void updateHightScore();
	void updateText();
	void updateRestartGame();
	void update();
	void render();
};

