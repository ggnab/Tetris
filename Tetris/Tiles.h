#pragma once
#pragma once
#include "Background.h"

class Tiles
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	int M = 20;
	int N = 10;
	int dx;
	int n;
	bool rotate;
	int colorNum;
	float valueScale;
	bool getCheck;
	int score;
	int hightScore;

	int field[20][10] = { 0 };

	float timer;
	float delay;
	sf::Clock clock;

	sf::SoundBuffer soundBufferLineClear;
	sf::Sound soundLineClear;
	sf::SoundBuffer soundBufferDrop;
	sf::Sound soundDrop;

	struct Point
	{
		int x = 0, y = 0;
	} a[4], b[4];

	int figures[7][4] =
	{
		{1,3,5,7}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // S
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}, // O
	};

	void initVariables();
	void initSound();
	void initTexture();
	void initSprites();
public:
	Tiles();
	~Tiles();

	void setPos(const int dx);
	void setRotate(const bool rotate);
	void setDelay(const float delay);
	void setHightScore(const int hightScore);

	int getScore();
	int getHightScore();
	bool getCheckEndGame();
	

	const int& getM() const;
	const int& getN() const;
	
	void restartGame();

	bool check();
	void updateHightScore();
	void updateTime();
	void updateLines();
	void updatePosition(bool pauseGame, bool endGame);
	void updateRotation(bool pauseGame);
	void update(bool pauseGame,bool startGame, bool endGame);
	void render(sf::RenderTarget& target, bool restartGame);
};