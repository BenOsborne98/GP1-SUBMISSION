/*
=================
cTextureManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the TextureManager class
=================
*/
#include "cTextureManager.h"
cTextureManager* cTextureManager::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cTextureManager* cTextureManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cTextureManager();
	}
	return cTextureManager::pInstance;
}

/*
=================
- Data constructor initializes the TextureMgr object
- Is always called, thus ensures all TextureMgr objects are in a consistent state.
=================
*/
cTextureManager::cTextureManager()
{

}

cTextureManager::cTextureManager(SDL_Renderer* theRenderer)
{
	theSDLRenderer = theRenderer;
}

/*
=================
- Destructor.
=================
*/
cTextureManager::~cTextureManager()
{
	deleteTextures();
}

void cTextureManager::addTexture(LPCSTR txtName, LPCSTR theFilename)
{
	if (!getTexture(txtName))
	{
		cTextures * newTxt = new cTextures();
		newTxt->loadTexture(theFilename, theSDLRenderer);
		textureList.insert(make_pair(txtName, newTxt));
	}
}

void cTextureManager::addTexture(LPCSTR txtName, SDL_Texture* theTexture)
{
	if (!getTexture(txtName))
	{
		cTextures * newTxt = new cTextures();
		newTxt->loadTexture(theTexture);
		textureList.insert(make_pair(txtName, newTxt));
	}
}
void cTextureManager::deleteTextures()
{
	for (map<LPCSTR, cTextures*>::iterator txt = textureList.begin(); txt != textureList.end(); ++txt)
	{
		delete txt->second;
	}
}
void cTextureManager::deleteTexture(LPCSTR txtName)
{
	map<LPCSTR, cTextures*>::iterator txt = textureList.find(txtName);
	this->textureList.erase(txt);
}
/*
=================
- return the texture.
=================
*/
cTextures* cTextureManager::getTexture(LPCSTR textureName)        // return the texture.
{
	map<LPCSTR, cTextures*>::iterator txt = textureList.find(textureName);
	if (txt != textureList.end())
	{
		return txt->second;
	}
	else
	{
		return NULL;
	}
}
/*
=================
- Set the renderer.
=================
*/
void cTextureManager::setRenderer(SDL_Renderer* ptheRenderer)
{
	this->theSDLRenderer = ptheRenderer;
}