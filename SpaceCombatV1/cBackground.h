/*
================
cBackround.h
- Header file for class definition - SPECIFICATION
- Header file for the Background class which is a child of cSprite class
=================
*/
#ifndef _CBACKGROUND_H
#define _CBACKGROUND_H
#include "cSprite.h"

class cBackground : public cSprite
{
public:
	void render();		// Default render function
	void update();		// Update method
};
#endif
