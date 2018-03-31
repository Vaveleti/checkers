#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;


class Pawn : public sf::Drawable
{
private:
	const float artificialWidth{ 4.f };
	const float artificialHeight{ 4.f };

	const float defualtPosition{ 0.f };
	sf::Texture pawnTexture; //Board texture
	sf::Sprite pawnSprite;
	void draw(RenderTarget& target, RenderStates state) const override;
	float positionX;
	float positionY;
	float scale;
public:
	bool aviable;


	static int humanCount;
	static int aiCount;


	String owner;
	Vector2f scalingVector;
	Pawn() = delete;
	Pawn(int scaling, String colour, String owned, int locX, int locY);
	~Pawn();
	Vector2f returnPosition();
	void setPosition(Vector2f positions, bool normal);
	Vector2f simplifiedPosition();
	int hitBox(float locX, float locY);
};

