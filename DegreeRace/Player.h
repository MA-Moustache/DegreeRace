#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Player
{
public:
	Player(std::string);
	void setSprite(std::string type);
	sf::Sprite* getSprite();
	void move(int m);
	int getX();
	int getY();
	void setPosition(int x, int y);
	enum movement { LEFT = 1, RIGHT = 3, UP = 0, DOWN = 2 };
	~Player();
private:
	sf::Texture *texture;
	sf::Sprite *sprite;
	const int size_main_char = 64;
};

