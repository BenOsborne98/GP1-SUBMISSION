/*
=================
cTextures.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DXTexture class
=================
*/
#ifndef _CTEXTURES_H
#define _CTEXTURES_H
#include "GameConstants.h"

class cTextures
{
private:
	SDL_Texture* sdlTextureID;
	int textureWidth;
	int textureHeight;


public:
	cTextures();
	cTextures(LPCSTR theFilename, SDL_Renderer *theRenderer);
	~cTextures();
	bool loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer);		// create the texture for use.
	bool loadTexture(SDL_Texture* theTexture);		// create the texture for use.
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	SDL_Texture* getTexture();						// return the texture.
	int getTWidth();						// Return width of texture;
	int getTHeight();						// Return height of texture;
	SDL_Rect getTextureRect(); // get Texture dimensions
};
#endif
