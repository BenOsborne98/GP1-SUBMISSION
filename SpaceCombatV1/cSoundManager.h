/*
==========================================================================
cSoundManager.h
==========================================================================
*/

#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

// OpenGL Headers
#include "GameConstants.h"
#include "cSound.h"


using namespace std;

class cSoundManager
{
private:
	static cSoundManager* pInstance;

protected:
	cSoundManager();
	~cSoundManager();
	map <LPCSTR, cSound*> gameSnds;

public:
	void add(LPCSTR sndName, LPCSTR fileName, soundType sndType);
	cSound* getSnd(LPCSTR sndName);
	void deleteSnd();
	bool initMixer();
	static cSoundManager* getInstance();
};
#endif
