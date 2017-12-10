/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CENEMYSHIPS_H
#define _CENEMYSHIPS_H
#include "cSprite.h"

class cEnemyShips : public cSprite
{
private:
	SDL_Point enemyShipVelocity;//ariable for enemy ship velocity

public:
	cEnemyShips();
	void update(double deltaTime);		// EnemyShips update method
	void setenemyShipVelocity(SDL_Point enemyShipVel);   // Sets the velocity for the EnemyShips
	SDL_Point getenemyShipVelocity();				 // Gets the EnemyShip velocity
};
#endif
