#include "Background.h"

void Background::initButtonPlay()
{

	buttonPlay.setTexture("Texture/tiles.png");
	buttonPlay.setTextureRect({ 2, 56, 120, 120 });
	buttonPlay.setPosition({ 180.f,950.f });
}

void Background::initButtonPause()
{
	buttonPause.setTexture("Texture/tiles.png");
	buttonPause.setTextureRect({ 6, 590, 74, 74 });
	buttonPause.setPosition({ 210.f,80.f });
}

void Background::initButtonContinue()
{
	buttonContinue.setTexture("Texture/tiles.png");
	buttonContinue.setTextureRect({ 2, 56, 120, 120 });
	//buttonContinue.setPosition({ 164.f,650.f });
}

void Background::initVariables()
{
	this->timer = 1;
	this->delay = 3;
	this->dyButtonStart = 950;
	this->dyButtonPause = -100;
	this->dyButtonContinue = 1100;
}

void Background::initTexture()
{
	if (!this->texture.loadFromFile("Texture/tiles.png"))
	{
		std::cout << "Files does not exits" << std::endl;
	}
}

void Background::initSprite()
{
	this->sprite.setTexture(this->texture);

	this->sprite.setOrigin(sf::Vector2f(20.f, 20.f));
}

Background::Background()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initButtonPlay();
	this->initButtonPause();
	this->initButtonContinue();
}

Background::~Background()
{

}

bool Background::getIsMousePlay(sf::RenderWindow& window)
{
	return this->buttonPlay.isMouseOver(window);
}

bool Background::getIsMousePause(sf::RenderWindow& window)
{
	return this->buttonPause.isMouseOver(window);
}

bool Background::getIsMouseContinue(sf::RenderWindow& window)
{
	return this->buttonContinue.isMouseOver(window);
}

void Background::updateButton(bool startGame, bool pauseGame)
{
	if (startGame)
	{
		this->dyButtonStart += 10;
		if (this->dyButtonStart > 1100) this->dyButtonStart = 1100;

		if (pauseGame)
		{
			this->dyButtonContinue -= 3;
			if (this->dyButtonContinue < 950) this->dyButtonContinue = 950;
			this->dyButtonPause -= 3;
			if (this->dyButtonPause < -100) this->dyButtonPause = -100;
		}
		else
		{
			this->dyButtonPause += 10;
			if (this->dyButtonPause > 80) this->dyButtonPause = 80;
			this->dyButtonContinue += 10;
			if (this->dyButtonContinue > 1100) this->dyButtonContinue = 1100;
		}
	}
	else
	{
		this->dyButtonStart -= 3;
		if (this->dyButtonStart < 950) this->dyButtonStart = 950;
	}

}

void Background::updateTime()
{
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;
}

void Background::update(bool startGame, bool pauseGame)
{
	this->updateTime();
	this->updateButton(startGame, pauseGame);
}

void Background::render(sf::RenderTarget& target)
{

	for (int i = 19; i >= 0; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			this->sprite.setTextureRect(sf::IntRect(330, 45, 40, 40));
			this->sprite.setPosition(j * 42, i * 42);
			this->sprite.move(60.f, 70.f);
			target.draw(this->sprite);
		}
	}

}

void Background::renderHear(sf::RenderTarget& target)
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->sprite.setTextureRect(sf::IntRect(345, 90, 43, 43));
			this->sprite.setPosition(j * 42, i * 42);
			this->sprite.move(60.f, 70.f);
			target.draw(this->sprite);
		}
	}

}

void Background::renderButton(sf::RenderTarget& target, bool startGame, bool pauseGame)
{
	this->buttonPause.setPosition(sf::Vector2f(210.f, this->dyButtonPause));
	this->buttonPause.render(target);
	this->buttonPlay.setPosition(sf::Vector2f(180.f, this->dyButtonStart));
	this->buttonPlay.render(target);
	this->buttonContinue.setPosition(sf::Vector2f(180.f, this->dyButtonContinue));
	this->buttonContinue.render(target);
}


