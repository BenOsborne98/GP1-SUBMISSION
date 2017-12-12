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
	
	SDL_Rect currentSpritePos = this->getSpritePos();//sets sprite position
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;//sets x position
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;//sets y posiiton

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });//set sprite position
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
