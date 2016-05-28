#include "SceneGame.h"


SceneGame::SceneGame(){
	idMusic = audioManager->getMusicID("Assets/Audios/Music/track_01.wav");

	fons = new Map();
	fons->init(40, 5, true, "Assets/Levels/lvl01/lvl01.tmx", "colisiones", 3, "Assets/Levels/lvl01/", false, 1, 0, 0, NULL, NULL);

	temps = new Timer(250, 260, "5:00");

	actions = new Actions();
	//Fer getter del tmx per a obtenir el nombre d'usos que tindrà cada habilitat en aquest mapa.*******
	actions->init(1, 1, "10", "10", "10", "10", "10", "10", "10", "10");
	currAction = -1;

	lemmingsSaved = 0;

	// Inicialització de les portes del joc.Punt de respawn i de sortida dels lemmings.
	enterDoor = new DoorEnter(130, 80, "Assets/Images/Doors/EnterDoor.png", 0, 0, 80, 80, 0, 0, 0, 2, 2, 2, 10); //50 es el valor de la variable que s'inicialitza a l'scene d'abans de la de game. 40 el número de lemmings.
	exitDoor = new ElementGame();
	exitDoor->init(90, 80, "Assets/Images/Doors/ExitDoor.png", 0, 0, 50, 50, 1, 1, 0, 0, 9, 9, 3);

	for (int i = 0; i < 2; i++){ //Feina per a la porta d'on surten Lemmings.
		Lemming *lemming = new Lemming();
		lemming->init(240, 80, fons->GetPosX(), fons->GetPosY());
		lemmings.push_back(lemming);
	}

	cursorChanged = false;
	cursor = Cursor::getInstanceCursor();

	smManager = SceneManager::getInstanceSM();
}


SceneGame::~SceneGame(){
}


void SceneGame::init(){
	audioManager->playMusic(idMusic, -1); //Afegir Mix_Music al Resource. De moment s'agafa com a un so.
	inputManager->SetCursorRelative(true);
	temps->start();
}

void SceneGame::update(){
	// EXIT TO THE MAIN MENU.
	if (inputManager->CheckESC()){
		inputManager->ResetESC();
		smManager->reinitScene(smManager->GAME);
		smManager->changeScene(smManager->MENU);
	}

	temps->update();

	// ACTIONS.
	int action = actions->update();
	switch (action){
	case -1:
		break;
	case 0: // REST_VEL_SPAWN
		//Resta velocitat al respawn de lemmings.
		break;
	case 1: // PLUS_VEL_SPAWN
		//Incrementa la velocitat al respawn de lemmings.
		break;
	case 12: // MOAB
		//Explotar tots els lemmings.
		break;
	default:
		currAction = action;
		break;
	}

	// ENTER DOOR.
	enterDoor->update(temps->getTime());
	if (enterDoor->getSpawnning()){
		Lemming *lemming = new Lemming();
		lemming->init(enterDoor->GetPosX(), enterDoor->GetPosY(), fons->GetPosX(), fons->GetPosY());
		lemmings.push_back(lemming);
	}

	// LEMMINGS AND EXIT DOOR.
	exitDoor->UpdateAnimacio();

	cursorChanged = false;
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = ((*itLem)->GetPosX() + (*itLem)->GetLimitX()) / fons->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / fons->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / fons->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / fons->GetSizeTile();
		(*itLem)->update(fons, x1, y1, x2, y2);

		if (!cursorChanged && (*itLem)->CursorOnLemming())
			cursorChanged = true;

		if (inputManager->CheckClick()){
			int numUsos = actions->GetNumberUsesSkill(currAction);
			if ((*itLem)->SetSkill(numUsos, currAction))
				actions->DetractUseSkill(currAction);
		}

		//***
		// Esborrar lemming si surt per la porta i sumar-lo a la variable de lemmings rescatats.
		/*if (x1 > exitDoor->GetPosX() && x2 < exitDoor->GetPosX() + exitDoor->GetWidth()
			&& y1 > exitDoor->GetPosY() && y2 < exitDoor->GetPosY() + exitDoor->GetHeight())*/
			//El lemming passa a l'estat de sortida per la porta.
		// If el lemming ha completat l'animació de caminar cap a la porta. Get del bool que indica això.
			//Lemming s'esborra.
			//lemmingsSaved++;
		//***

		//Esborrar lemming si surt del mapa.
		if (fons->GetPosX() + x1 < fons->GetPosX() || fons->GetPosX() + x2 > fons->GetPosX() + fons->GetWidthMap() || fons->GetPosY() + y2 > fons->GetPosY() + fons->GetHeightMap()){
			lemmings.erase(itLem);
			if (lemmings.size() == 0)
				break;
			itLem = lemmings.begin();
		}

		if ((*itLem)->GetEstat() == (*itLem)->STOP && fons->GetMapa(x1, y2 - 1) == 0 && fons->GetMapa(x2 + 1, y2 - 1) == 0){

			for (int i = -10; i < 3; i++){

				fons->CrearPosMapa(x1, y2 + i);

				fons->CrearPosMapa(x1 + 1, y2 + i);

				fons->CrearPosMapa(x1 + 2, y2 + i);

				fons->CrearPosMapa(x1 + 3, y2 + i);

				fons->CrearPosMapa(x2 + 1, y2 + i);

				fons->CrearPosMapa(x2, y2 + i);

				fons->CrearPosMapa(x2 - 1, y2 + i);
			}
		}
	}

	if (cursorChanged && !cursor->GetChangedCursor())
		cursor->ChangeCursor();
	else if (!cursorChanged && cursor->GetChangedCursor())
		cursor->ChangeCursor();

	cursor->Update();
}

void SceneGame::render(){
	fons->render();

	enterDoor->render();
	exitDoor->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();

	actions->render();

	temps->render();

	cursor->render();
}