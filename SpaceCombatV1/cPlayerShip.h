/*
=================
cPlayerShip.h
- Header file for class definition - SPECIFICATION
- Header file for the Player Ship class which is a child of cSprite class
=================
*/
#ifndef _CPLAYERSHIP_H
#define _CPLAYERSHIP_H
#include "cSprite.h"

class cPlayerShip : public cSprite
{
private:
	SDL_Point playerShipVelocity;

public:
	cPlayerShip();
	void update(double deltaTime);		// PlayerShip update method
	void setplayerShipVelocity(SDL_Point playerShipVel);   // Sets the velocity for the PlayerShip
	SDL_Point getplayerShipVelocity();				 // Gets the PlayerShip velocity
};
#endif
