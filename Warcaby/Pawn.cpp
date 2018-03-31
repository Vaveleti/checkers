#include "stdafx.h"
#include "Pawn.h"
#include <iostream>


int Pawn::humanCount = -1;
int Pawn::aiCount = -1;

Pawn::~Pawn() {
	if (this->owner == "human") { humanCount--; }
	else if (this->owner == "ai") { aiCount--; }
	aviable = false;
}


Pawn::Pawn(int scaling, String colour, String owned, int locX, int locY)
{
	if (!pawnTexture.loadFromFile(colour + "Pawn.png")) {
		exit(0);
	}
	else {
		this->aviable = true;
		if (owned == "human") {
			humanCount++;
		}
		else if (owned == "ai") {
			aiCount++;
		}
		this->scale = (float)scaling;

		pawnTexture.loadFromFile(colour + "Pawn.png");
		pawnSprite.setTexture(pawnTexture);
		pawnSprite.setScale({ (float)scaling,(float)scaling });
		this->owner = owned;
		pawnSprite.setOrigin({ -1.f, -1.f});

		
		this->positionX = (float)locX + defualtPosition;
		this->positionY = (float)locY + defualtPosition;

		pawnSprite.setPosition(defualtPosition + artificialWidth*locX*scaling, defualtPosition + artificialHeight*locY*scaling);
	}

}

void Pawn::draw(RenderTarget& target, RenderStates state) const
{
	if (aviable) {
		target.draw(this->pawnSprite, state);
	}
}

int Pawn::hitBox(float locX, float locY) {
	float realX = pawnSprite.getPosition().x + scale;
	float realY = pawnSprite.getPosition().y + scale;
	float realXend = realX + (artificialWidth/2)*scale;
	float realYend = realY + (artificialHeight/2)*scale;
	if (locX >= realX && locY >= realY && locX <= realXend && locY <= realYend) {
		std::cout << "Pressed :D!" << std::endl;
		if (this->owner == "human" && aviable) { return 1; }
		else if (this->owner == "ai" && aviable) {return -1; }
	}
		return 0;
}

Vector2f Pawn::returnPosition() {
	return pawnSprite.getPosition();
}

void Pawn::setPosition(Vector2f position, bool normal) {
	if (normal) {
		pawnSprite.setPosition(position.x, position.y);
	}
	else {
		pawnSprite.setPosition(position.x - scale * artificialWidth / 2, position.y - scale * artificialHeight / 2);
	}
}

Vector2f Pawn::simplifiedPosition() {
	int x = (int)(pawnSprite.getPosition().x + 40);
	int y = (int)(pawnSprite.getPosition().y + 40);
	x = x / 80;
	y = y / 80;
	return { (float) x, (float) y };
}