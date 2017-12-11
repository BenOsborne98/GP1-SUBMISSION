#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "SpaceCombat.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop; // Might need to be removed

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	cPlayerShip thePlayer;
	cEnemyShips theEnemy;
	cLasers theLasers;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	vector<cEnemyShips*> theEnemies;
	vector<cLasers*> theLaserfire;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextList;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	
	// Create vector array of button textures
	vector<LPCSTR> btnNameList; //needed for menu
	vector<LPCSTR> btnTexturesToUse;//creates vectors button textures
	vector<SDL_Point> btnPos;//creates vector for button positions
	vector <cButton> theButtons;
	
	// Game objects
	
	// Define the elements and there position in/on the array/map
	//int renderWidth, renderHeight;
	
	int score;//creates integer to keep tab on score
	string scoreAsString;//stores score as string
	bool scoreChanged;//used for true/false statement for score

	int health;
	string healthAsString;
	bool healthChanged;
	
	int spawnEnemy;//integer for enemy spawning
	void createEnemy();
	
	// Define the elements and there position in/on the array/map
	cFileHandler theFile;
	cTileMap theTileMap;
	cSprite dragTile;
	SDL_Point theTileClicked;
	SDL_Point mapTileClicked;
	int renderWidth, renderHeight;//integer used to show width and height of render window
	gameState theGameState;//creates the game state
	btnTypes theBtnType; //
	SDL_Rect pos;
	FPoint scale;
	SDL_Rect aRect;
	SDL_Color aColour;
	cTextures* tempTextTexture;
	SDL_Point theAreaClicked;//
	bool fileAvailable;
};

#endif

