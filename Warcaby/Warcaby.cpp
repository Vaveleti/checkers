// Warcaby.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Board.h"
#include "Pawn.h"
#include "Human.h"

int main()
{
	//Setting game's world
	const int scale = 20;
	Board world(scale);
	Human human(scale);

	//Setting window
	const unsigned int windowWidth = 32;
	const unsigned int windowHeight = 32;
	sf::RenderWindow window{ sf::VideoMode{ windowWidth*scale, windowHeight*scale}, "Warcaby" };
	window.setFramerateLimit(60);


	//Event of window
	sf::Event event;
	//Mouse?
	sf::Mouse mouse;
	bool previousState = false;

	//testing

	/*Game loop*/
	while (true) {
		window.clear(sf::Color::Black);
		window.pollEvent(event);

		//Exiting from game
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		if( event.type)
		

		window.draw(world);
		for (int i = 0; i <= human.number; i++) {
			if (human.pawnsAI[i]->aviable) { window.draw(*human.pawnsAI[i]); }
		}
		for (int i = 0; i <= human.number; i++) {
			if (human.pawns[i]->aviable) { window.draw(*human.pawns[i]); }
		}
		window.display();

		//Mouse action
		if (sf::Mouse::isButtonPressed(mouse.Left)) {
			human.checkHitboxes((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
			previousState = true;
		}
		else if(previousState) {
			previousState = false;
			human.updatePawn();
		}

		//Debbuging
		std::cout << "x: " <<sf::Mouse::getPosition(window).x << "		y: " << sf::Mouse::getPosition(window).y << std::endl;
		//std::cout << "x: " << human.pawns[0]->simplifiedPosition().x << "		y: " << human.pawns[0]->simplifiedPosition().y << std::endl;
		//std::cout << human.checkHitboxes(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) << std::endl;
	}
	return 0;
}

