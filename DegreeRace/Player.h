#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Player
{
public:
	Player(std::string);
	void setSprite(std::string type);
	sf::Sprite* getSprite();
	~Player();
private:
	sf::Texture *texture;
	sf::Sprite *sprite;
};

