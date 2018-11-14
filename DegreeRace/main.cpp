#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

int main()
{
	sf::Texture bg_texture;
	sf::Sprite bg_sprite;

	bool updateFPS = false;
	sf::Clock time;

	sf::View view;
	const int screenW = 1000, screenH = 800, size_main_char = 64;

	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Degree Race");
	window.setFramerateLimit(60);

	/* Main character texture + sprite */
	Player player_1("main_character");

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
			player_1.move(Player::movement::UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player_1.move(Player::movement::DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player_1.move(Player::movement::LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player_1.move(Player::movement::RIGHT);
		}
		std::cout << player_1.getSprite()->getTextureRect().left << std::endl;

		/*Collision avec la fenêtre */

		
		if (player_1.getSprite()->getPosition().x < 0) {
			player_1.getSprite()->setPosition(sf::Vector2f(0, player_1.getSprite()->getPosition().y));
		}

		if (player_1.getSprite()->getPosition().y > 700 ) {
			player_1.getSprite()->setPosition(sf::Vector2f(player_1.getSprite()->getPosition().x, 700));
		}
		if(player_1.getSprite()->getPosition().y < 0)
			player_1.getSprite()->setPosition(sf::Vector2f(player_1.getSprite()->getPosition().x, 0));
		
		/*Vue et collision avec le rect*/
		if (std::abs((player_1.getSprite()->getPosition().x ) - (rect.getPosition().x )) < 50 &&
			std::abs((player_1.getSprite()->getPosition().y ) - (rect.getPosition().y)) < 50) {

			std::cout << "Collision ! " << std::endl;
			rect.setFillColor(sf::Color::Red);

		}
		else {
			rect.setFillColor(sf::Color::Blue);
		}
		/* Vue */
		view.reset(sf::FloatRect(0,0,screenW, screenH));   //En haut à gauche et en bas à droite donc la vue fait la taille de l'écran dans ce cas ci
		sf::Vector2f position(screenW / 2, screenH / 2); // Centre de l'écran
		position.x = player_1.getSprite()->getPosition().x - 50; // 50 = Distance que le personnage va parcourir avant que la caméra le suit
		position.y = player_1.getSprite()->getPosition().y - (screenH);
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
		window.draw(*player_1.getSprite());
		window.draw(rect);
		window.display();
		window.clear();
	}

	return 0;
}