/*
=================
cLasers.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cLasers.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cLasers::cLasers() : cSprite()
{
	this->laserVelocity = { 0, 0 };//sets initial laser velocity as zero
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cLasers::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0 };
	direction.X = (sin((this->getSpriteRotAngle())*PI / 180));
	direction.Y = -(cos((this->getSpriteRotAngle())*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->laserVelocity.x = this->laserVelocity.x + direction.X;
	this->laserVelocity.y = this->laserVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->laserVelocity.x * deltaTime;
	currentSpritePos.y += this->laserVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	cout << "Laser position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the Laser
=================================================================
*/
void cLasers::setlaserVelocity(SDL_Point laserVel)
{
	this->laserVelocity = laserVel;//used for lasers velocity when moving
}
/*
=================================================================
Gets the Laser velocity
=================================================================
*/
SDL_Point cLasers::getlaserVelocity()
{
	return this->laserVelocity;
}