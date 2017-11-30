/*
=================
cPlayerShip.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayerShip.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cPlayerShip::cPlayerShip() : cSprite()
{
	this->playerShipVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayerShip::update(double deltaTime)
{

	FPoint direction = { 0, 0 };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->playerShipVelocity.x = this->playerShipVelocity.x + direction.X;
	this->playerShipVelocity.y = this->playerShipVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->playerShipVelocity.x * deltaTime;
	currentSpritePos.y += this->playerShipVelocity.y * deltaTime;

	this->playerShipVelocity.x *= 0.95;
	this->playerShipVelocity.y *= 0.95;

	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cPlayerShip::setplayerShipVelocity(SDL_Point playerShipVel)
{
	playerShipVelocity = playerShipVel;
}

/*
=================================================================
Gets the rocket velocity
=================================================================
*/
/*
SDL_Point cPlayerShip::getplayerShipVelocity()
{
	return playerShipVelocity;
}
*/