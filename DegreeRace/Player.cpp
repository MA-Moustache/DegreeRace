#include "pch.h"
#include "player.h"

Player::Player(std::string type)
{
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	setSprite(type);
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