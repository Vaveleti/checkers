#include "stdafx.h"
#include "Ai.h"
#include <iostream>


Ai::Ai()
{
}


Response::response Ai::IsMovePossible(location now, location desired, int** map) {

	//Create array of locations of AI's pawns
	location nowPawns[12];
	int pawnTotal = 0;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (map[y][x] < 0) {
				nowPawns[pawnTotal].y = y;
				nowPawns[pawnTotal].x = x;
				pawnTotal++;
			}
		}
	}

	//Looking for most optimum decision
	int maxScore = 0;
	int maxPawn = 0;
	int maxY = 0;
	int maxX = 0;
	for (int pawnLiterating = 0; pawnLiterating <= pawnTotal; pawnLiterating++) {

		for (int locY = 0; locY < 8; locY++) {
			for (int locX = 0; locX < 8; locX++) {
				int score = 0;
				if (abs(nowPawns[pawnLiterating].x - locX) == 1 && nowPawns[pawnLiterating].y - locY == -1 && map[locY][locX] == 0) {
					score = 1;
				}
				
				if (nowPawns[pawnLiterating].x - locX == 2 && nowPawns[pawnLiterating].y - locY == -2 && 
					map[nowPawns[pawnLiterating].y + 1][nowPawns[pawnLiterating].x - 1] > 0 && 
					map[locY][locX] == 0) {
					score = 3;
				}
				
				if (nowPawns[pawnLiterating].x - locX == -2 && nowPawns[pawnLiterating].y - locY == -2 && 
					map[nowPawns[pawnLiterating].y + 1][nowPawns[pawnLiterating].x + 1] > 0 && 
					map[locY][locX] == 0) {
					score = 3;
				}
				
				if (score > maxScore) {
					maxScore = score;
					maxPawn = pawnLiterating;
					maxX = locX;
					maxY = locY;
				}
			}
		}
	}

	/*
	std::cout << maxX << " " << maxY << " " << (map[nowPawns[maxPawn].y][nowPawns[maxPawn].x] + 1)*(-1) << std::endl;
	int n; std::cin >> n;
	*/

	return (Response::response{ maxX,maxY, (map[nowPawns[maxPawn].y][nowPawns[maxPawn].x] + 1)*(-1) });
}


Response::response Ai::makeMove(int **map) {;

	return IsMovePossible({ 0,0 }, { 1,1 }, map);
}




/*
for (int y = 0; y < 8; y++) {
for (int x = 0; x < 8; x++) {
if (total.map[now.x][now.y] < 0) {
if (abs(now.x - desired.x) == 1 && now.y - desired.y == -1 && total.map[desired.x][desired.y] == 0) {
return "move";
}
else if (now.x - desired.x == 2 && now.y - desired.y == -2 && total.map[desired.x + 1][desired.y + 1] > 0) {
return "beatL";
total.total++;
}
else if (now.x - desired.x == -2 && now.y - desired.y == -2 && total.map[desired.x - 1][desired.y + 1] > 0) {
return "beatR";
}
else {
return "no";
}
}
}
}
*/