#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
	sf::Texture bg_texture, main_character_texture;
	sf::Sprite bg_sprite, main_character_sprite;

	enum Dir{Up, Left, Down, Right};
	sf::Vector2i anim(Down, 0);

	bool updateFPS = false;
	sf::Clock time;

	sf::View view;
	const int screenW = 1000, screenH = 800, size_main_char = 64;

	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Degree Race");
	window.setFramerateLimit(60);

	/* Main character texture + sprite */
	main_character_texture.loadFromFile("Images/main_character.png");
	main_character_texture.setSmooth(true);
	main_character_sprite.setTexture(main_character_texture);
	main_character_sprite.setPosition(0, 700);

	/* Background texture + sprite*/
	bg_texture.loadFromFile("Images/bg.jpg");
	bg_texture.setSmooth(true);
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(1, 1.2);

	/* Rectangle pour test collision*/
	sf::RectangleShape rect(sf::Vector2f(120, 50));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(250, 700);

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
			main_character_sprite.move(0, -3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			anim.x = Down; // x = 3
			main_character_sprite.move(0, 3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			anim.x = Left; // x = 2
			main_character_sprite.move(-3, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			anim.x = Right; // x = 3
			main_character_sprite.move(3, 0);
		}
		main_character_sprite.setTextureRect(sf::IntRect(anim.x * size_main_char, 0, size_main_char, size_main_char));

		/*Collision avec la fenêtre */

		
		if (main_character_sprite.getPosition().x < 0) {
			main_character_sprite.setPosition(sf::Vector2f(0, main_character_sprite.getPosition().y));
		}

		if (main_character_sprite.getPosition().y > 700 ) {
			main_character_sprite.setPosition(sf::Vector2f(main_character_sprite.getPosition().x, 700));
		}
		if(main_character_sprite.getPosition().y < 0)
			main_character_sprite.setPosition(sf::Vector2f(main_character_sprite.getPosition().x, 0));
		
		/*Vue et collision avec le rect*/
		if (std::abs((main_character_sprite.getPosition().x ) - (rect.getPosition().x )) < 50 &&
			std::abs((main_character_sprite.getPosition().y ) - (rect.getPosition().y)) < 50) {

			std::cout << "Collision ! " << std::endl;
			rect.setFillColor(sf::Color::Red);

		}
		else {
			rect.setFillColor(sf::Color::Blue);
		}
		/* Vue */
		view.reset(sf::FloatRect(0,0,screenW, screenH));   //En haut à gauche et en bas à droite donc la vue fait la taille de l'écran dans ce cas ci
		sf::Vector2f position(screenW / 2, screenH / 2); // Centre de l'écran
		position.x = main_character_sprite.getPosition().x - 50; // 50 = Distance que le personnage va parcourir avant que la caméra le suit
		position.y = main_character_sprite.getPosition().y - (screenH);
		if (position.x < 0) {
			position.x = 0;
		}
		if (position.y < 0) {
			position.y = 0;
		}
		view.reset(sf::FloatRect(position.x, position.y, screenW, screenH));
		
		/* Ajout des éléments à la window */
		window.setView(view);
		window.draw(bg_sprite);
		window.draw(main_character_sprite);
		window.draw(rect);
		window.display();
		window.clear();
	}

	return 0;
}