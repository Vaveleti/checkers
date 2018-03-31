#pragma once
#include "Pawn.h"
#include "Response.h"
#include <math.h>
#include <iostream>

class Ai : public Response
{
public:
	Ai();
	~Ai() = default;
	Response::response makeMove(int** map);
	struct location {
		int x;
		int y;
	};
	struct totalMap {
		int total = 0;
		int map[10][10];
		Response::response firstResponse;
		int loopNumber = 0;
	};

private:
	Response::response IsMovePossible(location, location, int** map);
};
