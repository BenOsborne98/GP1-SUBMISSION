/*
=================
cLasers.h
- Header file for class definition - SPECIFICATION
- Header file for the Lasers class which is a child of cSprite class
=================
*/
#ifndef _CLASERS_H
#define _CLASERS_H
#include "cSprite.h"


class cLasers : public cSprite
{
private:
	SDL_Point laserVelocity;

public:
	cLasers();
	void update(double deltaTime);		// Lasers update method
	void setlaserVelocity(SDL_Point laserVel); // Sets the velocity for the lasers
	SDL_Point getlaserVelocity();				 // Gets the Bullet velocity
};
#endif
