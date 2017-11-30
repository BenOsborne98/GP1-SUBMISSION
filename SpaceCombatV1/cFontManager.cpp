/*
== == == == == == == == =
cFontMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/

#include "cFontManager.h"

cFontManager* cFontManager::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cFontManager* cFontManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cFontManager();
	}
	return cFontManager::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cFontManager::cFontManager()
{
}

cFontManager::~cFontManager()							// Destructor.
{
	deleteFont();
	TTF_Quit();
}

bool cFontManager::initFontLib()
{
	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{
		cout << "TTF_Init() Failed: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void cFontManager::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))
	{
		cFont * newFont = new cFont();
		newFont->loadFont(fileName, fontSize);
		fontList.insert(make_pair(fontName, newFont));
	}
}

cFont* cFontManager::getFont(LPCSTR fontName)				// return the font for use
{
	map<LPCSTR, cFont*>::iterator theFont = fontList.find(fontName);
	if (theFont != fontList.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}

void cFontManager::deleteFont()								// delete font.
{
	for (map<LPCSTR, cFont*>::const_iterator theFont = fontList.begin(); theFont != fontList.end(); theFont++)
	{
		TTF_CloseFont(theFont->second->getFont());
		delete theFont->second;
	}
}