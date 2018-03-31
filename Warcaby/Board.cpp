#include "stdafx.h"
#include "Board.h"


Board::Board(int scaling)
{
	if (!boardTexture.loadFromFile("board.png")) {
		exit(0);
	}
	else {
		boardTexture.loadFromFile("board.png");
		boardSprite.setTexture(boardTexture);
		boardSprite.setPosition(defualtPosition, defualtPosition);
		boardSprite.setScale({(float)scaling,(float)scaling});

	}

}

void Board::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->boardSprite, state);
}
