#include "Tiles.h"

void Tiles::initVariables()
{
	this->dx = 0;
	this->rotate = 0;
	this->colorNum = 1;
	this->timer = 1;
	this->delay = 0.3f;
	this->valueScale = 1;
	this->score = 0;
	int n = rand() % 7;
	this->getCheck = false;
	for (int i = 0; i < 4; i++)
	{
		this->a[i].x = this->figures[n][i] % 2 + 4;
		this->a[i].y = this->figures[n][i] / 2;
	}
}

void Tiles::initSound()
{
	this->soundBufferLineClear.loadFromFile("Audio/Lineclear.wav");
	this->soundLineClear.setBuffer(this->soundBufferLineClear);
	this->soundBufferDrop.loadFromFile("Audio/Drop.wav");
	this->soundDrop.setBuffer(this->soundBufferDrop);
	this->soundDrop.setVolume(50);
}

void Tiles::initTexture()
{

	if (!this->texture.loadFromFile("Texture/tiles.png"))
	{
		std::cout << "File tiles does not exits" << std::endl;
	}
}

void Tiles::initSprites()
{
	this->sprite.setTexture(this->texture);
}

Tiles::Tiles()
{
	this->initVariables();
	this->initTexture();
	this->initSprites();
	this->initSound();
}

Tiles::~Tiles()
{
}

void Tiles::setPos(const int dx)
{
	this->dx = dx;
}

void Tiles::setRotate(const bool rotate)
{
	this->rotate = rotate;
}

void Tiles::setDelay(const float delay)
{
	this->delay = delay;
}

void Tiles::setHightScore(const int hightScore)
{
	this->hightScore = hightScore;
}

int Tiles::getScore()
{
	return this->score;
}

int Tiles::getHightScore()
{
	return this->hightScore;
}

bool Tiles::getCheckEndGame()
{
	return this->getCheck;
}

const int& Tiles::getM() const
{
	return this->M;
}

const int& Tiles::getN() const
{
	return this->N;
}

void Tiles::restartGame()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->field[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		a[i].x = 0;
		a[i].y = 0;
		b[i].x = 0;
		b[i].y = 0;
	}
	this->initVariables();
}


bool Tiles::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return false;
		else if (this->field[this->a[i].y][this->a[i].x]) return false;
	}
	return true;
}

void Tiles::updateHightScore()
{

}

void Tiles::updateTime()
{
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;
}

void Tiles::updateLines()
{
	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < N) { k--; }
		else if (count == N) { this->soundLineClear.play(); this->score++; }
	}
}

void Tiles::updatePosition(bool pauseGame, bool endGame)
{
	this->getCheck = this->check();
	if (!pauseGame)
	{
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			this->a[i].x += dx;
		}
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		if (this->timer > this->delay)
		{
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];
				this->a[i].y += 1;
				if(!endGame)
				this->soundDrop.play();
			}
			if (!this->check())
			{
				for (int i = 0; i < 4; i++)  this->field[b[i].y][b[i].x] = this->colorNum;
				this->colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					this->a[i].x = this->figures[n][i] % 2 + 4;
					this->a[i].y = this->figures[n][i] / 2;
				}
			}
			timer = 0;
		}
		if (!this->check())
		{
			for (int i = 0; i < 4; i++)
			{
				this->a[i] = this->b[i];
			}
		}
	}
}

void Tiles::updateRotation(bool pauseGame)
{
	if (this->rotate && !pauseGame)
	{
		Point t = a[1];
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			int x = this->a[i].y - t.y;
			int y = this->a[i].x - t.x;
			this->a[i].x = t.x - x;
			this->a[i].y = t.y + y;
		}
		if (this->check() == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		}
	}
}


void Tiles::update(bool pauseGame, bool startGame, bool endGame)
{
	//this->sprite.setScale(this->valueScale, this->valueScale);
	this->updateTime();
	this->updatePosition(pauseGame,endGame);
	this->updateRotation(pauseGame);
	this->updateLines();
	
	this->rotate = false;
	this->dx = 0;
	this->delay = 0.3f;
}

void Tiles::render(sf::RenderTarget& target,bool restartGame)
{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (this->field[i][j] == 0)
					continue;
				this->sprite.setTextureRect(sf::IntRect(this->field[i][j] * 40, 0, 40, 40));
				this->sprite.setOrigin(sf::Vector2f(20.f, 20.f));
				this->sprite.setPosition(j * 42, i * 42);
				this->sprite.move(60.f, 70.f);
				target.draw(this->sprite);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			this->sprite.setTextureRect(sf::IntRect(colorNum * 40, 0, 40, 40));
			this->sprite.setOrigin(sf::Vector2f(20.f, 20.f));
			this->sprite.setPosition(this->a[i].x * 42, this->a[i].y * 42);
			this->sprite.move(60.f, 70.f);
			target.draw(this->sprite);
		}
	
}
