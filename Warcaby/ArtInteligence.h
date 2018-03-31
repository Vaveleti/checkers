#pragma once
#include <SFML/Graphics.hpp>

class ArtInteligence
{
public:
	ArtInteligence() = delete;
	ArtInteligence(unsigned int);
	~ArtInteligence() = default;

	struct decision {
		int locX;
		int locY;
		int pawnNumber;
	};

private:
	//static unsigned int difficulty;
protected:
	//decision* aiDecide(int **map);
};

