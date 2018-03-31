#pragma once

#include <SFML\Graphics.hpp>
#include "Pawn.h"
using namespace sf;


class Board : public sf::Drawable
{
private:
	const float defualtPosition{ 0.f };
	sf::Texture boardTexture; //Board texture
	sf::Sprite boardSprite;
	void draw(RenderTarget& target, RenderStates state) const override;


public:
	Vector2f scalingVector;
	Board() = delete;
	Board(int scaling);
	~Board() = default;
};

