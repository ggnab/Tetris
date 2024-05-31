#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::setTexture(std::string string)
{
	if (!this->texture.loadFromFile(string))
	{
		std::cout << "File does not exits" << std::endl;
	}
	this->sprite.setTexture(this->texture);
}

void Button::setTextureRect(sf::IntRect InR)
{
	this->sprite.setTextureRect(InR);
}

void Button::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Button::render(sf::RenderTarget& targer)
{
	targer.draw(this->sprite);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = this->sprite.getPosition().x;
	float btnPosY = this->sprite.getPosition().y;

	float btnxPosWidth = this->sprite.getPosition().x + this->sprite.getLocalBounds().width;
	float btnxPosHeight = this->sprite.getPosition().y + this->sprite.getLocalBounds().height;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnxPosHeight && mouseY > btnPosY)
	{
		return true;
	}
	return false;
}
