#include "Game.h"

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::endgame() const
{
	return this->endGame;
}

void Game::initTiles()
{
	this->tiles = new Tiles();
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Font/eurof55.ttf"))
	{
		//error
	}
}

void Game::initText()
{
	this->textScore.setFont(this->font);
	this->textScore.setCharacterSize(50);
	this->textScore.setLineSpacing(0.7f);
	this->textScore.setOutlineThickness(1);
	this->textScore.setFillColor(sf::Color::Green);
	this->textScore.setPosition(50.f, 80.f);

	this->hightScore.setFont(this->font);
	this->hightScore.setCharacterSize(50);
	this->hightScore.setLineSpacing(0.7f);
	this->hightScore.setOutlineThickness(1);
	this->hightScore.setFillColor(sf::Color::Green);
	this->hightScore.setPosition(330.f, 80.f);

}

void Game::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
	this->tiles = nullptr;
	this->pauseGame = true;
	this->startGame = false;
	this->restartGame = false;
}

void Game::initSound()
{
	this->soundBufferCursor.loadFromFile("Audio/Cursor.wav");
	this->soundCursor.setBuffer(this->soundBufferCursor);
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(500, 1100);
	this->window = new sf::RenderWindow(videoMode, "Tetris");
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariables();
	this->initTiles();
	this->initWindow();
	this->initFont();
	this->initText();
	this->initSound();
}

Game::~Game()
{
	delete this->window;
	delete this->tiles;
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		default:
			break;
		case sf::Event::Closed: this->window->close(); break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Up) this->tiles->setRotate(true);
			else if (this->event.key.code == sf::Keyboard::Left) this->tiles->setPos(-1);
			else if (this->event.key.code == sf::Keyboard::Right) this->tiles->setPos(1);
			break;
		case sf::Event::MouseButtonPressed:
			if (background.getIsMousePause(*this->window) || background.getIsMouseContinue(*this->window))
			{
				this->pauseGame = !this->pauseGame;
				this->soundCursor.play();
				if (!this->pauseGame)
				{
					std::cout << "Game continue" << std::endl;
				}
				else
				{
					std::cout << "Game pause" << std::endl;
				}
			}
			if (background.getIsMousePlay(*this->window))
			{
				this->startGame = !this->startGame;
				this->pauseGame = false;
				this->soundCursor.play();
				if (this->startGame)
				{
					std::cout << "Game start\n" << std::endl;
				}
			}
			if (menuGameOver.getIsMouseRestartGame(*this->window))
			{
				this->restartGame = !this->restartGame;
				this->updateRestartGame();
				this->soundCursor.play();
				if (this->restartGame)
				{
					std::cout << "Game restart\n" << std::endl;
				}
			}
			if (menuGameOver.getIsMouseExit(*this->window))
			{
				this->window->close();
				this->soundCursor.play();
			}
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->tiles->setDelay(0.05f);
}



void Game::updateTiles()
{
}

void Game::updateHightScore()
{
	int _hightscore;
	std::ifstream readFile;
	readFile.open("HightScore.txt");
	if (readFile.is_open())
		while (!readFile.eof()) {
			readFile >> _hightscore;
			this->tiles->setHightScore(_hightscore);
		}
	readFile.close();
	std::ofstream writeFile;
	writeFile.open("HightScore.txt");
	if (writeFile.is_open()) {
		if (this->tiles->getScore() > this->tiles->getHightScore())
			this->tiles->setHightScore(this->tiles->getScore());
		writeFile << this->tiles->getHightScore();
	}
	writeFile.close();
}

void Game::updateText()
{
	std::stringstream ss, ss1;
	ss << "Score" << "\n    " << this->tiles->getScore();
	this->textScore.setString(ss.str());
	ss1 << "H.Score" << "\n      " << this->tiles->getHightScore();
	this->hightScore.setString(ss1.str());
}

void Game::updateRestartGame()
{
	if (this->restartGame)
	{
		this->tiles->restartGame();
	}
}

void Game::update()
{

	this->pollEvent();
	this->tiles->update(this->pauseGame, this->startGame, this->endGame);
	background.update(this->startGame, this->pauseGame);
	menuGameOver.update(this->endGame, this->startGame, this->restartGame, this->tiles->getScore());
	this->updateHightScore();
	this->updateText();
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	//draw
	this->restartGame = menuGameOver.getCheckRestartGame();
	this->endGame = !this->tiles->getCheckEndGame();
	background.render(*this->window);
	this->tiles->render(*this->window, this->restartGame);
	background.renderHear(*this->window);
	background.renderButton(*this->window, this->startGame, this->pauseGame);
	menuGameOver.render(*this->window);
	this->window->draw(this->textScore);
	this->window->draw(this->hightScore);
	this->window->display();
}
