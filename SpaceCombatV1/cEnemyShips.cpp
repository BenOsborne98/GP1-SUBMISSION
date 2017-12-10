/*
=================
cEnemyShips.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemyShips.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemyShips::cEnemyShips() : cSprite()
{
	this->enemyShipVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cEnemyShips ::update(double deltaTime)
{

	this->setSpriteRotAngle(this->getSpriteRotAngle() + (2.0f * deltaTime));//sets the enemy ship rotation speed
	if (this->getSpriteRotAngle() > 360)
	{
		this->setSpriteRotAngle(this->getSpriteRotAngle() - 360);
	}

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	//cout << "EnemyShip position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the enemy ships
=================================================================
*/
void cEnemyShips::setenemyShipVelocity(SDL_Point enemyShipVel)
{
	enemyShipVelocity = enemyShipVel;//sets the velocity of the enemy ships
}
/*
=================================================================
Gets the enemy ships velocity
=================================================================
*/

SDL_Point cEnemyShips::getenemyShipVelocity()
{
	return enemyShipVelocity;
}
