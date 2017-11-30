/*
==================================================================================
cSoundManager.cpp
==================================================================================
*/

#include "cSoundManager.h"

cSoundManager* cSoundManager::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSoundManager::cSoundManager()
{

}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSoundManager* cSoundManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSoundManager();
	}
	return cSoundManager::pInstance;
}

void cSoundManager::add(LPCSTR sndName, LPCSTR fileName, soundType sndType)
{
	if (!getSnd(sndName))
	{
		cSound * newSnd = new cSound(sndType);
		newSnd->load(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

cSound* cSoundManager::getSnd(LPCSTR sndName)
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}

void cSoundManager::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}

bool cSoundManager::initMixer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		cout << "SDL_Init_AUDIO Failed: " << SDL_GetError() << endl;
		return false;
	}
	//Initialise SDL_mixer 
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		cout << "Mix_OpenAudio Failed: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

cSoundManager::~cSoundManager()
{
	deleteSnd();
	Mix_CloseAudio();
	Mix_Quit();
}