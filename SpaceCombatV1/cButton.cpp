/*
=================
- cButton.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cButton.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cButton::cButton() : cSprite()
{
}


/*
=================================================================
Update the sprite position
=================================================================
*/


gameState cButton::update(gameState theCurrentGameState, gameState newGameState, SDL_Point theAreaClicked)//update function for when buttons are clicked
{
	SDL_Point areaClicked = theAreaClicked;//checks the point on screen which has been clicked
	if (areaClicked.x > this->getSpritePos().x && areaClicked.x < (this->getSpritePos().x + this->getSpriteDimensions().w) && areaClicked.y > this->getSpritePos().y && areaClicked.y < (this->getSpritePos().y + this->getSpriteDimensions().h))
	{
		this->buttonClickedRC.x = (int)(areaClicked.x - this->getSpritePos().x) / this->getSpriteDimensions().w;
		this->buttonClickedRC.y = (int)(areaClicked.y - this->getSpritePos().y) / this->getSpriteDimensions().h;
		this->clicked = true;
		return newGameState;//switches game state
	}
	return theCurrentGameState;
}

bool cButton::getClicked()
{
	return this->clicked;//detappenedects if click has h
}
void cButton::setClicked(bool state)
{
	this->clicked = state;//clicking will change the state
}