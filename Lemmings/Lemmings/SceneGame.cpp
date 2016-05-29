#include "SceneGame.h"


SceneGame::SceneGame(){
	idMusic = audioManager->getMusicID("Assets/Audios/Music/track_01.wav");

	fons = new Map();
	fons->init(40, 5, true, "Assets/Levels/lvl01/lvl01.tmx", "colisiones", 3, "Assets/Levels/lvl01/", false, 1, 0, 0, NULL, NULL);

	temps = new Timer(250, 260, "5:00");

	actions = new Actions();
	//Fer getter del tmx per a obtenir el nombre d'usos que tindrà cada habilitat en aquest mapa.*******
	currAction = actions->init(1, 1, 50, "10", "10", "10", "10", "10", "10", "10", "10");
	
	lemmingsSaved = 0;

	// Inicialització de les portes del joc.Punt de respawn i de sortida dels lemmings.
	enterDoor = new DoorEnter(110, 80, 20, 12); //50 es el valor de la variable que s'inicialitza a l'scene d'abans de la de game. 40 el número de lemmings.
	exitDoor = new ElementGame();
	exitDoor->init(338, 200, "Assets/Images/Doors/_sortida.png", 0, 0, 42, 31, 1, 1, 92, 31, 49, 2, 12);

	//Per a testejar a l'altre cantó. S'ha d'eliminar la creació d'aquest Lemming**
	Lemming *lemming = new Lemming();
	lemming->init(230, 80, fons->GetPosX(), fons->GetPosY());
	lemmings.push_back(lemming);

	cursorChanged = false;
	cursor = Cursor::getInstanceCursor();

	smManager = SceneManager::getInstanceSM();
}


SceneGame::~SceneGame(){
}


void SceneGame::init(){
	audioManager->playMusic(idMusic, -1);
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
		actions->DecrementVelocitySkill();
		enterDoor->setTimeToSpawn(actions->GetNumberUsesSkill(1));
		break;
	case 1: // PLUS_VEL_SPAWN
		actions->IncrementVelocitySkill();
		enterDoor->setTimeToSpawn(actions->GetNumberUsesSkill(1));
		break;
	case 11: // MOAB
		for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
			(*itLem)->SetContadorTemps(temps->getTime());
		}
		//Explotar tots els lemmings.
		break;
	default:
		currAction = action;
		break;
	}

	// ENTER DOOR.
	enterDoor->update(temps->getTimeMs());
	if (enterDoor->getSpawnning()){
		Lemming *lemming = new Lemming();
		int posX = fons->GetPosX() + ((enterDoor->GetPosX() / 2) - 3);
		int posY = fons->GetPosY() + enterDoor->GetPosY();
		lemming->init(posX, posY, fons->GetPosX(), fons->GetPosY());
		lemmings.push_back(lemming);
	}
	
	// EXIT DOOR.
	exitDoor->UpdateAnimacio();

	// LEMMINGS.
	cursorChanged = false;
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = ((*itLem)->GetPosX() + (*itLem)->GetLimitX()) / fons->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / fons->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / fons->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / fons->GetSizeTile();
		(*itLem)->update(fons, x1, y1, x2, y2, temps->getTime());

		if (!cursorChanged && (*itLem)->CursorOnLemming())
			cursorChanged = true;

		if (inputManager->CheckClick()){
			int numUsos = actions->GetNumberUsesSkill(currAction);
			if ((*itLem)->SetSkill(numUsos, currAction, temps->getTime())){
				actions->DetractUseSkill(currAction);
				inputManager->ResetClick();
			}
		}

		//***
		// Esborrar lemming si surt per la porta i sumar-lo a la variable de lemmings rescatats.
		if ((*itLem)->GetEstat() != (*itLem)->EXIT){
			if (fons->GetPosX() + x1 > (exitDoor->GetPosX() / fons->GetSizeTile()) + 31 && fons->GetPosX() + x2 < ((exitDoor->GetPosX() + exitDoor->GetWidth()) / fons->GetSizeTile()) + 22 &&
				fons->GetPosY() + y1 >(exitDoor->GetPosY() / fons->GetSizeTile()) + 5 && fons->GetPosY() + y2 < exitDoor->GetPosY() + exitDoor->GetHeight()){
				//El lemming passa a l'estat de sortida per la porta.
				cout << "Lemming sortint\n";
			}
		}
		// If el lemming ha completat l'animació de caminar cap a la porta. Get del bool que indica això.
			//Lemming s'esborra.
			//lemmingsSaved++;
		//***

		//Esborrar lemming si surt del mapa.
		if ((fons->GetPosX() + x1 < fons->GetPosX() || fons->GetPosX() + x2 > fons->GetPosX() + fons->GetWidthMap() || fons->GetPosY() + y2 > fons->GetPosY() + fons->GetHeightMap())
			|| (*itLem)->GetMort()){
			lemmings.erase(itLem);
			if (lemmings.size() == 0)
				break;
			itLem = lemmings.begin();
		}

		if ((*itLem)->GetEstat() == (*itLem)->STOP && fons->GetMapa(x1, y2 - 1) == 0 && fons->GetMapa(x2 + 1, y2 - 1) == 0){

			for (int i = -10; i < 3; i++){

				fons->CrearPosMapa(x1, y2 + i, 3);

				fons->CrearPosMapa(x1 + 1, y2 + i, 3);

				fons->CrearPosMapa(x1 + 2, y2 + i, 3);

				fons->CrearPosMapa(x1 + 3, y2 + i, 3);

				fons->CrearPosMapa(x2 + 1, y2 + i, 3);

				fons->CrearPosMapa(x2, y2 + i, 3);

				fons->CrearPosMapa(x2 - 1, y2 + i, 3);
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