#include "MenuGameOver.h"

void MenuGameOver::initVariables()
{
	this->dxButtonMenuOver = 750.f;
	this->checkRestartGame = false;
}

void MenuGameOver::initSound()
{
		this->soundBufferGameOver.loadFromFile("Audio/Gameover.wav");
		this->soundGameOver.setBuffer(this->soundBufferGameOver);
}

void MenuGameOver::initButtonPlayAgain()
{
	this->buttonPlayAgain.setTexture("Texture/tiles.png");
	this->buttonPlayAgain.setPosition({ 200.f,350.f });
	this->buttonPlayAgain.setTextureRect({ 125,53,100,100 });
}

void MenuGameOver::initFont()
{
	if (!this->font.loadFromFile("Font/eurof55.ttf"))
	{
		//error
	}
}

void MenuGameOver::initText()
{
	this->textScore.setFont(this->font);
	this->textScore.setCharacterSize(150);
	this->textScore.setLineSpacing(0.7f);
	this->textScore.setOutlineThickness(2);
	this->textScore.setFillColor(sf::Color::White);
	//this->textScore.setPosition(50.f, 80.f);

	this->text.setFont(this->font);
	this->text.setCharacterSize(50);
	this->text.setFillColor(sf::Color::White);
}

void MenuGameOver::initButtonExit()
{
	this->buttonExit.setTexture("Texture/tiles.png");
	this->buttonExit.setTextureRect({ 227,50,100,100 });
}

void MenuGameOver::initTexture()
{
	if (!this->texture.loadFromFile("Texture/tiles.png"))
	{
		//error
	}
}

void MenuGameOver::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(195.f, 195.f);
	this->sprite.setTextureRect(sf::IntRect(5, 188, 390, 390));
	this->sprite.setPosition(250.f, 500.f);
}

MenuGameOver::MenuGameOver()
{
	this->initVariables();
	this->initButtonPlayAgain();
	this->initButtonExit();
	this->initTexture();
	this->initSprite();
	this->initFont();
	this->initText();
	this->initSound();
}

MenuGameOver::~MenuGameOver()
{

}

bool MenuGameOver::getCheckRestartGame()
{
	return this->checkRestartGame;
}

bool MenuGameOver::getIsMouseRestartGame(sf::RenderWindow& window)
{
	return this->buttonPlayAgain.isMouseOver(window);
}

bool MenuGameOver::getIsMouseExit(sf::RenderWindow& window)
{
	return this->buttonExit.isMouseOver(window);
}

void MenuGameOver::updateText(int score)
{
	std::stringstream ss,ss1;
	ss << score;
	this->textScore.setString(ss.str());
	ss1 << "No Moves Left";
	this->text.setString(ss1.str());
}

void MenuGameOver::updateButton(bool endGame, bool startGame,bool restartGame)
{
	this->checkRestartGame = restartGame;
	this->checkEndGame = endGame;
	if (!checkEndGame)
	{
		//this->soundGameOver.play();
		checkEndGame = !checkEndGame;
	}
	if (endGame && startGame && !restartGame)
	{
		this->dxButtonMenuOver -= 3;
		if (this->dxButtonMenuOver < 250) this->dxButtonMenuOver = 250;
	}
	else if(!endGame && restartGame)
	{
		this->dxButtonMenuOver -= 10;
		if (this->dxButtonMenuOver < -200) { this->checkRestartGame = false; this->dxButtonMenuOver = 750; }
		//std::cout << this->dxButtonMenuOver << std::endl;
	}
}

void MenuGameOver::update(bool endGame,bool startGame,bool restartGame,int score)
{
	this->updateButton(endGame, startGame,restartGame);
	this->updateText(score);
}

void MenuGameOver::render(sf::RenderTarget& target)
{
	this->sprite.setPosition(this->dxButtonMenuOver, 500.f);
	target.draw(this->sprite);
	this->buttonPlayAgain.setPosition({ this->dxButtonMenuOver - 135, 570.f});
	this->buttonPlayAgain.render(target);
	this->buttonExit.setPosition({ this->dxButtonMenuOver + 50,570 });
	this->buttonExit.render(target);
	this->textScore.setPosition(this->dxButtonMenuOver-30, 380.f);
	target.draw(this->textScore);
	this->text.setPosition(this->dxButtonMenuOver - 130, 340);
	target.draw(this->text);
}
