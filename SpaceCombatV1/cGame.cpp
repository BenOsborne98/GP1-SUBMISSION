/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureManager* theTextureMgr = cTextureManager::getInstance();
static cFontManager* theFontMgr = cFontManager::getInstance();
static cSoundManager* theSoundManager = cSoundManager::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance(); // Used to find buttons (may have to go)


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)


{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundManager->initMixer();
	score = 0;

	// Store the textures
	textureName = { "asteroid1", "asteroid2", "asteroid3", "asteroid4", "lasers","thePlayerShip","theBackground" };
	texturesToUse = { "Images\\asteroid1.png", "Images\\asteroid2.png", "Images\\asteroid3.png", "Images\\asteroid4.png", "Images\\bullet.png", "Images\\PlayerShipNew.png", "Images\\Background.png" }; //"Images\\starscape1024x768.png"};
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	// Create textures for Game Dialogue (text)
	//fontList = { "digital", "spaceAge", "nasa" };
	fontList = { "digital", "spaceAge" };
	//fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/nasalization-rg.ttf" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Space Combat", "Score: 0" , "Health:" };

	theTextureMgr->addTexture("Title", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	theTextureMgr->addTexture("Health", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[2], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	//Might need to be removed-----------------------------------------------------------------------------------------
	
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" };
	btnPos = { { 400, 375 },{ 400, 300 },{ 400, 300 },{ 500, 500 },{ 400, 300 },{ 740, 500 },{ 400, 300 } };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;
	theBtnType = EXIT;
	
	//-------------------------------------------------------------------------------------

	// Load game sounds
	soundList = { "theme", "shot", "explosion" };
	soundTypes = { MUSIC, SFX, SFX };
	soundsToUse = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundManager->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundManager->getSnd("theme")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());
	cout << "Bckgnd w " << spriteBkgd.getSpriteDimensions().w << " h " << spriteBkgd.getSpriteDimensions().h << endl;
	thePlayer.setSpritePos({ 400, 500 });
	thePlayer.setTexture(theTextureMgr->getTexture("thePlayerShip"));
	thePlayer.setSpriteDimensions(theTextureMgr->getTexture("thePlayerShip")->getTWidth(), theTextureMgr->getTexture("thePlayerShip")->getTHeight());
	thePlayer.setplayerShipVelocity({ 0, 0 });

	// Create vector array of textures

	for (int enemy = 0; enemy < 10; enemy++)
	{
		//theAsteroids.push_back(new cAsteroid);
		theEnemies.push_back(new cEnemyShips);
		theEnemies[enemy]->setSpritePos({ 100 * (rand() % 5 + 1), 1 * (rand() % 5 + 1) });
		//theEnemies[enemy]->setSpritePos({ 100 * 4, 50 * 0 }); Change Back to this if Ships dont move
		theEnemies[enemy]->setSpriteTranslation({ 0,(rand() % 8 + 1) });//{ (rand() % 8 + 1), (rand() % 8 + 1) });
		int randEnemyShip = rand() % 4;
		//int randAsteroid = 4;
		theEnemies[enemy]->setTexture(theTextureMgr->getTexture(textureName[randEnemyShip]));
		theEnemies[enemy]->setSpriteDimensions(theTextureMgr->getTexture(textureName[randEnemyShip])->getTWidth(), theTextureMgr->getTexture(textureName[randEnemyShip])->getTHeight());
		theEnemies[enemy]->setenemyShipVelocity({ 0, 0 });
		theEnemies[enemy]->setActive(true);
	}

	/*for (int enemy2 = 0; enemy2 < 10; enemy2++)
	{
		//theAsteroids.push_back(new cAsteroid);
		theEnemies.push_back(new cEnemyShips);
		//theEnemies[enemy]->setSpritePos({ 100 * (rand() % 5 + 1), 50 * (rand() % 5 + 1) });
		theEnemies[enemy2]->setSpritePos({ 100 * 4, 50 * 0 });
		theEnemies[enemy2]->setSpriteTranslation({ 0,(rand() % 8 + 1) });//{ (rand() % 8 + 1), (rand() % 8 + 1) });
		int randAsteroid = rand() % 4;
		//int randAsteroid = 4;
		theEnemies[enemy2]->setTexture(theTextureMgr->getTexture(textureName[randAsteroid]));
		theEnemies[enemy2]->setSpriteDimensions(theTextureMgr->getTexture(textureName[randAsteroid])->getTWidth(), theTextureMgr->getTexture(textureName[randAsteroid])->getTHeight());
		theEnemies[enemy2]->setenemyShipVelocity({ 0, 0 });
		theEnemies[enemy2]->setActive(true);
	}
	*/



}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//bool loop = true;   //may need to be reimplemented
	 loop = true;
	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//Needs to be checked
	
	SDL_RenderClear(theRenderer);
	//cout << "game state = " << theGameState << endl;
	switch (theGameState)
	{
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		//tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		//pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//scale = { 1, 1 };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("CreateTxt");
		//pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("DragDropTxt");
		//pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// Render Button
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	
	
	case PLAYING:
	{
			SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	// Render each asteroid in the vector array
	for (int draw = 0; draw < theEnemies.size(); draw++)
	{
		theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
	}
	// Render each bullet in the vector array
	for (int draw = 0; draw < theLaserfire.size(); draw++)
	{
		theLaserfire[draw]->render(theRenderer, &theLaserfire[draw]->getSpriteDimensions(), &theLaserfire[draw]->getSpritePos(), theLaserfire[draw]->getSpriteRotAngle(), &theLaserfire[draw]->getSpriteCentre(), theLaserfire[draw]->getSpriteScale());
	}
	// Render the Title
	cTextures* tempTextTexture = theTextureMgr->getTexture("Title");
	SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	FPoint scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

	//RenderScore
	if (scoreChanged)
	{
		gameTextList[1] = scoreAsString.c_str();
		//theTextureMgr->addTexture("Score", theFontMgr->getFont("nasa")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
		theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
		scoreChanged = false;
	}
	tempTextTexture = theTextureMgr->getTexture("Score");
	pos = { 10, 40, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	
	//RenderHealth
	tempTextTexture = theTextureMgr->getTexture("Health");
	pos = { 10, 700, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	
	// render the Players ship
	thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre(), thePlayer.getSpriteScale());
	SDL_RenderPresent(theRenderer);
		

		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 740, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
		
		
	
		
	}
	break;
	
	
	case END:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		
		//tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		//pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("ThanksTxt");
		//pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("SeeYouTxt");
		//pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	
	
	case QUIT:
	{
		loop = false;
	}
	break;
	default:
		break;
	}

	SDL_RenderPresent(theRenderer);
	
	/*
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	// Render each asteroid in the vector array
	for (int draw = 0; draw < theEnemies.size(); draw++)
	{
		theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
	}
	// Render each bullet in the vector array
	for (int draw = 0; draw < theLaserfire.size(); draw++)
	{
		theLaserfire[draw]->render(theRenderer, &theLaserfire[draw]->getSpriteDimensions(), &theLaserfire[draw]->getSpritePos(), theLaserfire[draw]->getSpriteRotAngle(), &theLaserfire[draw]->getSpriteCentre(), theLaserfire[draw]->getSpriteScale());
	}
	// Render the Title
	cTextures* tempTextTexture = theTextureMgr->getTexture("Title");
	SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	FPoint scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

	//RenderScore
	if (scoreChanged)
	{
		gameTextList[1] = scoreAsString.c_str();
		//theTextureMgr->addTexture("Score", theFontMgr->getFont("nasa")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
		theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
		scoreChanged = false;
	}
	tempTextTexture = theTextureMgr->getTexture("Score");
	pos = { 10, 40, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	
	//RenderHealth
	tempTextTexture = theTextureMgr->getTexture("Health");
	pos = { 10, 700, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	
	// render the Players ship
	thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre(), thePlayer.getSpriteScale());
	SDL_RenderPresent(theRenderer);
	*/

}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	/*SDL_RenderPresent(theRenderer);
	switch (theGameState)
	{
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		//tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		//pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//scale = { 1, 1 };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("CreateTxt");
		//pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("DragDropTxt");
		//pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// Render Button
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;


	case PLAYING:
	{
		SDL_RenderClear(theRenderer);
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render each asteroid in the vector array
		for (int draw = 0; draw < theEnemies.size(); draw++)
		{
			theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
		}
		// Render each bullet in the vector array
		for (int draw = 0; draw < theLaserfire.size(); draw++)
		{
			theLaserfire[draw]->render(theRenderer, &theLaserfire[draw]->getSpriteDimensions(), &theLaserfire[draw]->getSpritePos(), theLaserfire[draw]->getSpriteRotAngle(), &theLaserfire[draw]->getSpriteCentre(), theLaserfire[draw]->getSpriteScale());
		}
		// Render the Title
		cTextures* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//RenderScore
		if (scoreChanged)
		{
			gameTextList[1] = scoreAsString.c_str();
			//theTextureMgr->addTexture("Score", theFontMgr->getFont("nasa")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
			theTextureMgr->addTexture("Score", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0 ,255 }, { 0, 0, 0, 0 }));
			scoreChanged = false;
		}
		tempTextTexture = theTextureMgr->getTexture("Score");
		pos = { 10, 40, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//RenderHealth
		tempTextTexture = theTextureMgr->getTexture("Health");
		pos = { 10, 700, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// render the Players ship
		thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre(), thePlayer.getSpriteScale());
		SDL_RenderPresent(theRenderer);


		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 740, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());




	}
	break;


	case END:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());

		//tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		//pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("ThanksTxt");
		//pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//tempTextTexture = theTextureMgr->getTexture("SeeYouTxt");
		//pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		//tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;


	case QUIT:
	{
		loop = false;
	}
	break;
	default:
		break;
	}*/

}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	
	// CHeck Button clicked and change state
	if (theGameState == MENU || theGameState == END)
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
	}
	else
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked);
	}
	theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
	theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
	
	
	// Update the visibility and position of each asteriod
	vector<cEnemyShips*>::iterator enemyIterator = theEnemies.begin();
	while (enemyIterator != theEnemies.end())
	{
		if ((*enemyIterator)->isActive() == false)
		{
			enemyIterator = theEnemies.erase(enemyIterator);
		}
		else
		{
			(*enemyIterator)->update(30.0f *deltaTime);
			++enemyIterator;
		}
	}
	// Update the visibility and position of each bullet
	vector<cLasers*>::iterator laserIterartor = theLaserfire.begin();
	while (laserIterartor != theLaserfire.end())
	{
		if ((*laserIterartor)->isActive() == false)
		{
			laserIterartor = theLaserfire.erase(laserIterartor);
		}
		else
		{
			(*laserIterartor)->update(deltaTime);
			++laserIterartor;
		}
	}
	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cLasers*>::iterator laserIterartor = theLaserfire.begin(); laserIterartor != theLaserfire.end(); ++laserIterartor)
	{
		//(*bulletIterartor)->update(deltaTime);
		for (vector<cEnemyShips*>::iterator enemyIterator = theEnemies.begin(); enemyIterator != theEnemies.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->collidedWith(&(*enemyIterator)->getBoundingRect(), &(*laserIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*enemyIterator)->setActive(false);
				(*laserIterartor)->setActive(false);
				theSoundManager->getSnd("explosion")->play(0);
				score+=100;
				if (theTextureMgr->getTexture("Score") != NULL)
				{
					theTextureMgr->deleteTexture("Score");
				}
				//theTextureMgr->deleteTexture("Score");
				string theScore = to_string(score);
				scoreAsString = "Score:" + theScore;
				scoreChanged = true;
			}
		}
	}


	// Update the Rockets position
	thePlayer.update(deltaTime);
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				theAreaClicked = { event.motion.x, event.motion.y };
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;
			
			/*
			SDLK_DOWN:
			{
				if (thePlayer.getSpritePos().x < (renderWidth - thePlayer.getSpritePos().w))
				{
					thePlayer.setSpriteTranslation({ -5, -5 });
				}
			}
			break;

			case SDLK_UP:
			{
				if (thePlayer.getSpritePos().x > 0)
				{
					thePlayer.setSpriteTranslation({ 5, 5 });
				}
			}
			break;
			*/
			case SDLK_d:
			{
				thePlayer.setplayerShipVelocity({ 250, 0 });
			}
			break;

			case SDLK_a:
			{
				thePlayer.setplayerShipVelocity({ -250, 0 });
			}
			break;
			case SDLK_SPACE:
			{
				theLaserfire.push_back(new cLasers);
				int numLasers = theLaserfire.size() - 1;
				theLaserfire[numLasers]->setSpritePos({ thePlayer.getBoundingRect().x + thePlayer.getSpriteCentre().x, thePlayer.getBoundingRect().y + thePlayer.getSpriteCentre().y });
				theLaserfire[numLasers]->setSpriteTranslation({ 50, 50 });
				theLaserfire[numLasers]->setTexture(theTextureMgr->getTexture("lasers"));
				theLaserfire[numLasers]->setSpriteDimensions(theTextureMgr->getTexture("lasers")->getTWidth(), theTextureMgr->getTexture("lasers")->getTHeight());
				theLaserfire[numLasers]->setlaserVelocity({ 50, 50 });
				theLaserfire[numLasers]->setSpriteRotAngle(thePlayer.getSpriteRotAngle());
				theLaserfire[numLasers]->setActive(true);
				cout << "Laser added to Vector at position - x: " << thePlayer.getBoundingRect().x << " y: " << thePlayer.getBoundingRect().y << endl;
			}
			theSoundManager->getSnd("shot")->play(0);
			break;
			default:
				break;
			}

		default:
			break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}