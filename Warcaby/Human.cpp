#include "stdafx.h"
#include "Human.h"
#include <math.h>
#include <iostream>

Human::Human(int scaling)
{

	//Creating map
	this->map = new int*[8];
	for(int i = 0; i < 8; i++){
		this->map[i] = new int[8];
		for (int x = 0; x < 8; x++) {
			map[i][x] = 0;
		}
	}

	//Creating pawns
	int y = 0;
	int x = 0;
	int z = 1;
	for (int i = 0; i <= this->number; i++) {
		pawns[i] = new Pawn(scaling, "white", "human", x, y + this->startingY);
		pawnsAI[i] = new Pawn(scaling, "black", "ai", z, y);
		x += 2;
		z += 2;
		if (x >= 8 && y != 1) {
			z = 0;
			x = 1;
			y++;
		}
		else if (x >= 8 && y == 1) {
			z = 1;
			x = 0;
			y++;
		}
	}

	//initialaizing
	beforePickedBool = false;
	this->beforePawnNumber = 0;
	this->beforePickingPosition = pawns[0]->returnPosition();
	updateMap();
}

Human::~Human() {
	for (int i = 0; i <= this->number; i++) {
		delete pawns[i];
		delete pawnsAI[i];
	}

	for (int i = 0; i < 8; i++) {
		delete this->map[i];
	}
	delete this->map;

}


int Human::checkHitboxes(float locX, float locY) {
	int temp = 0;
	if (!beforePickedBool)
	{
		for (int i = 0; i <= Pawn::humanCount; i++) {
			temp = pawns[i]->hitBox(locX, locY);
			if (temp != 0) {
				this->beforePawnNumber = i;
				this->beforePickedBool = true;
				updateMap();
				this->beforePickingPosition = pawns[i]->returnPosition();
				pawns[i]->setPosition({ locX, locY }, false);
				return temp;
			}
		}
		/*
		for (int i = 0; i <= Pawn::aiCount; i++) {
			temp = pawnsAI[i]->hitBox(locX, locY);
			if (temp != 0) { return temp; }
		}
		*/
		return 0;
	}
	else
	{
		pawns[beforePawnNumber]->setPosition({ locX, locY }, false);
	}
}

void Human::updatePawn() {

	this->beforePickedBool = false;
	Vector2f simplyfiedPosition = pawns[beforePawnNumber]->simplifiedPosition();
	Vector2f updatedPosition = simplyfiedPosition * 80.f;
	if (map[(int)simplyfiedPosition.y][(int)simplyfiedPosition.x] == 0 &&
		(-simplyfiedPosition.y + beforePickingPosition.y/80) == 1 &&
		abs(simplyfiedPosition.x - beforePickingPosition.x/80) == 1
		) {
		this->pawns[beforePawnNumber]->setPosition(updatedPosition, true);
		updateMap();
		makeMove();
		this->beforePickingPosition = pawns[beforePawnNumber]->returnPosition();
	}
	else if (
		map[(int)simplyfiedPosition.y][(int)simplyfiedPosition.x] == 0 &&
		(-simplyfiedPosition.y + beforePickingPosition.y / 80) == 2 && (
			((simplyfiedPosition.x - beforePickingPosition.x / 80) == 2 && map[(int)simplyfiedPosition.y-1][(int)simplyfiedPosition.x-1] < 0) ||
			((simplyfiedPosition.x - beforePickingPosition.x / 80) == -2 && map[(int)simplyfiedPosition.y - 1][(int)simplyfiedPosition.x + 1] < 0)
			)
		) 
	{
		this->pawns[beforePawnNumber]->setPosition(updatedPosition, true);
		updateMap();

		this->pawnsAI[(map[(int)simplyfiedPosition.y + 1][(int)simplyfiedPosition.x - (int)beforePickingPosition.x / 160] + 1)*(-1)]->~Pawn();

		makeMove();
		this->beforePickingPosition = pawns[beforePawnNumber]->returnPosition();
	}
	else
	{
		this->pawns[beforePawnNumber]->setPosition(beforePickingPosition, true);
	}
}

void Human::updateMap() {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			map[y][x] = 0;
		}
	}
	for (int i = 0; i <= number; i++) {
		if (pawns[i]->aviable) {
			this->map[(int)(pawns[i]->simplifiedPosition().y)][(int)(pawns[i]->simplifiedPosition().x)] = i+1; //+1 bo tak to zerowy pionek bylby zerem
		}
		if (pawnsAI[i]->aviable) {
			this->map[(int)(pawnsAI[i]->simplifiedPosition().y)][(int)(pawnsAI[i]->simplifiedPosition().x)] = -i-1; //tu podobnie
		}
	}

	//debugging
	/*
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			std::cout << (int)map[x][y] << "	";
		}
		std::cout << std::endl;
	}
	int n = 0;
	std::cin >> n;
	*/
}


void Human::makeMove() {
	Response::response answer = ai.makeMove(map);
	Vector2f current = pawnsAI[answer.number]->simplifiedPosition();

	if (abs(answer.y - (int)current.y) == 2) {
		int shiftX = ((int)current.x - answer.x)/2;
		int shiftY = ((int)current.y - answer.y)/2;

		//std::cout << (int)(current.y - shiftY) << " " << (int)(current.x - shiftX) << std::endl; int n; std::cin >> n;
		this->pawns[map[(int)(current.y - shiftY)][(int)(current.x - shiftX)] - 1]->~Pawn();
	}

	this->pawnsAI[answer.number]->setPosition({(answer.x)*80.f, (answer.y)*80.f}, true);
	updateMap();
}

