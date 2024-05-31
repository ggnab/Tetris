#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <SFML/System/Clock.hpp>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
class Button
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	//void initTexture(const std::string string);
	//void initSprite(const sf::Vector2f pos, const sf::IntRect inr);
public:
	Button();
	~Button();

	void setTexture(std::string string);
	void setTextureRect(sf::IntRect InR);
	void setPosition(sf::Vector2f pos);
	void render(sf::RenderTarget& targer);
	bool isMouseOver(sf::RenderWindow& window);
};

