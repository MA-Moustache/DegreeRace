#include "pch.h"
#include "player.h"

Player::Player(std::string type)
{
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	setSprite(type);
	this->getSprite()->setTextureRect(sf::IntRect(0, 0, size_main_char, size_main_char));
}


Player::~Player()
{
}

// Load the texture and set the sprite
void Player::setSprite(std::string type)
{

	if (type == "main_character")
	{
		this->texture->loadFromFile("Images/main_character.png");
		this->texture->setSmooth(true);
		this->sprite->setTexture(*this->texture);
		this->sprite->setPosition(0, 70);
	}
}

sf::Sprite* Player::getSprite()
{
	return this->sprite;
}

void Player::move(int m)
{
	switch (m)
	{
	case movement::LEFT: this->getSprite()->move(-3, 0);
		break;
	case movement::RIGHT: this->getSprite()->move(3, 0);
		break;
	case movement::UP: this->getSprite()->move(0, -3);
		break;
	case movement::DOWN: this->getSprite()->move(0, 3);
		break;
	}

	this->getSprite()->setTextureRect(sf::IntRect(m * size_main_char, 0, size_main_char, size_main_char));
}

int Player::getX()
{
	return this->sprite->getPosition().x;
}

int Player::getY()
{
	return this->sprite->getPosition().y;
}

void Player::setPosition(int x, int y)
{
	this->sprite->setPosition(sf::Vector2f(x, y));
}