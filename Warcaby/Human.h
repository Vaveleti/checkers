#pragma once
#include "Pawn.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Response.h"
#include "Ai.h"

class Human : public Response
{
public:
	Pawn *pawns[12];
	const int number{ 11 };
	Pawn *pawnsAI[12];
	
	Human(int scaling);
	~Human();
	int checkHitboxes(float locX, float locY);
	void updatePawn();

	int** map;

private:
	Ai ai;
	const int startingY = 5;

	void updateMap();
	bool beforePickedBool;
	int beforePawnNumber;
	Vector2f beforePickingPosition;

	void makeMove();
};

