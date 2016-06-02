#include "SceneGame.h"


SceneGame* SceneGame::gInstance = NULL;

SceneGame::SceneGame(){
	idMusic = audioManager->getMusicID("Assets/Audios/Music/track_01.wav");

	actions = new Actions();

	numLemmings = lemmingsToSave = 0;
	tempsRestant = releaseRate = "";

	lemmingsMorts = lemmingsSaved = 0;

	exitDoor = new ElementGame();

	cursorChanged = false;
	cursor = Cursor::getInstanceCursor();

	smManager = SceneManager::getInstanceSM();
}


SceneGame::~SceneGame(){
}


SceneGame* SceneGame::getInstanceSceneGame(){
	if (gInstance == NULL)
		gInstance = new SceneGame();
	
	return gInstance;
}


void SceneGame::initFromPreGame(Map* mapa, int numLemmings, int lemmingsToSave, string rateSpeed, string temps){
	this->mapa = mapa;
	this->numLemmings = numLemmings;
	this->lemmingsToSave = lemmingsToSave;
	tempsRestant = temps + ":00";
	releaseRate = rateSpeed;
}

void SceneGame::init(){
	mapa->SetPositionTiles(-475, 22);
	mapa->SetScaleTiles(1, 1);

	// Inicialització de les portes del joc. Punt de respawn i de sortida dels lemmings.
	enterDoor = new DoorEnter(110, 80, 20, numLemmings); //50 es el valor de la variable que s'inicialitza a l'scene d'abans de la de game.
	exitDoor->init(338, 200, "Assets/Images/Doors/_sortida.png", 0, 0, 42, 31, 1, 1, 92, 31, 49, 2, 12);

	//Fer getter del tmx per a obtenir el nombre d'usos que tindrà cada habilitat en aquest mapa.*******
	currAction = actions->init(1, 1, releaseRate, "10", "10", "10", "10", "10", "10", "10", "10");

	temps = new Timer(250, 260, /*tempsRestant*/ "0:10");
	temps->start();

	audioManager->playMusic(idMusic, -1);
}

void SceneGame::clear(){
	delete mapa;

	delete enterDoor;

	currAction = -1;

	delete temps;

	lemmings.clear();
	lemmings.resize(0);
}

void SceneGame::update(){
	temps->update();

	// ACTIONS.
	int action = actions->update();
	switch (action){
	case -1:
		break;
	case 0: // REST_VEL_SPAWN
		actions->DecrementVelocitySkill();
		enterDoor->setTimeToSpawn(actions->GetNumberUsesSkill(1));
		break;
	case 1: // PLUS_VEL_SPAWN
		actions->IncrementVelocitySkill();
		enterDoor->setTimeToSpawn(actions->GetNumberUsesSkill(1));
		break;
	case 11: // MOAB. Explotar tots els lemmings.
		for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
			if (!(*itLem)->GetContExplotar())
				(*itLem)->SetContadorTemps(temps->getTime());
		}
		break;
	default:
		currAction = action;
		break;
	}

	// ENTER DOOR.
	enterDoor->update(temps->getTimeMs());
	if (enterDoor->getSpawnning()){
		Lemming* lemming = new Lemming();
		int posX = mapa->GetPosX() + ((enterDoor->GetPosX() / 2) - 3);
		int posY = mapa->GetPosY() + enterDoor->GetPosY();
		lemming->init(posX, posY, mapa->GetPosX(), mapa->GetPosY());
		lemmings.push_back(lemming);
	}
	
	// EXIT DOOR.
	exitDoor->UpdateAnimacio();

	// LEMMINGS.
	cursorChanged = false;
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = ((*itLem)->GetPosX() + (*itLem)->GetLimitX()) / mapa->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / mapa->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / mapa->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / mapa->GetSizeTile();
		(*itLem)->update(mapa, x1, y1, x2, y2, temps->getTime());

		if (!cursorChanged && (*itLem)->CursorOnLemming())
			cursorChanged = true;

		if (inputManager->CheckClickLeft()){
			int numUsos = actions->GetNumberUsesSkill(currAction);
			if ((*itLem)->SetSkill(numUsos, currAction, temps->getTime())){
				actions->DetractUseSkill(currAction);
				inputManager->ResetClick();
			}
		}

		// Si el Lemming surt per la porta.
		if ((*itLem)->GetEstat() != (*itLem)->RESCUED){
			if (mapa->GetPosX() + x1 > (exitDoor->GetPosX() / mapa->GetSizeTile()) + 31 && mapa->GetPosX() + x2 < ((exitDoor->GetPosX() + exitDoor->GetWidth()) / mapa->GetSizeTile()) + 22 &&
				mapa->GetPosY() + y1 >(exitDoor->GetPosY() / mapa->GetSizeTile()) + 5 && mapa->GetPosY() + y2 < exitDoor->GetPosY() + exitDoor->GetHeight()){
				(*itLem)->SetRescatar();
			}
		}

		// ESBORRAR LEMMINGS.

		// Si el lemming ha completat l'animació de caminar cap a la porta, s'esborra i incrementa el número de Lemmings salvats.
		if ((*itLem)->GetRescatat()){
			lemmings.erase(itLem);
			itLem = lemmings.begin();
			lemmingsSaved++;
			//updateNumeroLemSaved();
		}
		
		// Si surten del mapa o moren.
		if ((mapa->GetPosX() + x1 < mapa->GetPosX() || mapa->GetPosX() + x2 > mapa->GetPosX() + mapa->GetWidthMap() || mapa->GetPosY() + y2 > mapa->GetPosY() + mapa->GetHeightMap())
			|| (*itLem)->GetMort()){
			lemmings.erase(itLem);
			itLem = lemmings.begin();
			lemmingsMorts++;
			//updateNumeroLemEnJoc();
		}
			
		if (lemmings.size() == 0){
			if ((lemmingsSaved + lemmingsMorts) == numLemmings){
				// Passar info necessària ScenePostGame.*
				smManager->changeScene(smManager->POST_GAME);
			}
			break;
		}

		if ((*itLem)->GetEstat() == (*itLem)->STOP && mapa->GetMapa(x1, y2 - 1) == 0 && mapa->GetMapa(x2 + 1, y2 - 1) == 0){

			for (int i = -10; i < 3; i++){

				mapa->CrearPosMapa(x1, y2 + i, 3);

				mapa->CrearPosMapa(x1 + 1, y2 + i, 3);

				mapa->CrearPosMapa(x1 + 2, y2 + i, 3);

				mapa->CrearPosMapa(x1 + 3, y2 + i, 3);

				mapa->CrearPosMapa(x2 + 1, y2 + i, 3);

				mapa->CrearPosMapa(x2, y2 + i, 3);

				mapa->CrearPosMapa(x2 - 1, y2 + i, 3);
			}
		}

	}

	if (cursorChanged && !cursor->GetChangedCursor())
		cursor->ChangeCursor();
	else if (!cursorChanged && cursor->GetChangedCursor())
		cursor->ChangeCursor();

	cursor->Update();

	if (temps->getTempsOut()){
		audioManager->pauseMusic();
		// Passar info necessària ScenePostGame.*
		smManager->changeScene(smManager->POST_GAME);
	}

	// EXIT TO THE MAIN MENU.
	if (inputManager->CheckESC()){
		inputManager->ResetESC();
		inputManager->SetCursorRelative(false);
		smManager->changeScene(smManager->MENU);
	}
}

void SceneGame::render(){
	mapa->render();

	enterDoor->render();
	exitDoor->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();

	actions->render();

	temps->render();

	cursor->render();
}