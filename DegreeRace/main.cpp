#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Degree Race");
	window.setFramerateLimit(60);

	sf::Texture bg_texture, main_character_texture;
	sf::Sprite bg_sprite, main_character_sprite;

	enum Dir{Up, Left, Down, Right};
	sf::Vector2i anim(Down, 0);

	bool updateFPS = false;
	sf::Clock time;

	/* Main character texture + sprite */
	main_character_texture.loadFromFile("Images/main_character.png");
	main_character_texture.setSmooth(true);
	main_character_sprite.setTexture(main_character_texture);

	/* Background texture + sprite*/
	bg_texture.loadFromFile("Images/bg.jpg");
	bg_texture.setSmooth(true);
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(1, 1.2);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				updateFPS = true;
			}
			else {
				updateFPS = false;
			}
		}
		/* Input keyboard */
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			anim.x = Up; // x = 1
			main_character_sprite.move(0, -2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			anim.x = Down; // x = 3
			main_character_sprite.move(0, 2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			anim.x = Left; // x = 2
			main_character_sprite.move(-2, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			anim.x = Right; // x = 3
			main_character_sprite.move(2, 0);
		}

		main_character_sprite.setTextureRect(sf::IntRect(anim.x * 64, 0, 64, 64));
		main_character_sprite.setOrigin(sf::Vector2f(0, -700));

		window.draw(bg_sprite);
		window.draw(main_character_sprite);
		window.display();
		window.clear();
	}

	return 0;
}