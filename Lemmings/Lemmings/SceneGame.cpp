#include "SceneGame.h"


SceneGame::SceneGame(){
	idMusic = audioManager->getMusicID("Assets/Audios/Music/track_01.wav");

	fons = new Map();
	fons->init(40, 5, true, "Assets/Levels/lvl01/lvl01.tmx", "colisiones", 3, "Assets/Levels/lvl01/", false, 1, 0, 0, NULL, NULL);

	actions = new Actions();
	//Fer getter del tmx per a obtenir el nombre d'usos que tindrà cada habilitat en aquest mapa.*******
	actions->init(1, 1, "10", "10", "10", "10", "10", "10", "10", "10");
	currAction = -1;

	for (int i = 0; i < 1; i++){ //Feina per la porta d'on surten Lemmings.
		Lemming *lemming = new Lemming();
		lemming->init(130 + i, 60, fons->GetPosX(), fons->GetPosY());
		lemmings.push_back(lemming);
	}

	smManager = SceneManager::getInstanceSM();

	cursor = Cursor::getInstanceCursor();
}


SceneGame::~SceneGame(){
}


void SceneGame::init(){
	audioManager->playMusic(idMusic, -1); //Afegir Mix_Music al Resource. De moment s'agafa com a un so.
	inputManager->SetCursorRelative(true);
}

void SceneGame::update(){
	if (inputManager->CheckESC()){
		inputManager->ResetESC();
		smManager->reinitScene(smManager->GAME);
		smManager->changeScene(smManager->MENU);
		inputManager->SetCursorRelative(false);
	}

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

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = (*itLem)->GetPosX() / fons->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / fons->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / fons->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / fons->GetSizeTile();
		(*itLem)->update(fons, x1, y1, x2, y2);

		if ((*itLem)->CursorOnLemming() && !cursor->GetChangedCursor())
			cursor->ChangeCursor();
		else if(!(*itLem)->CursorOnLemming() && cursor->GetChangedCursor())
			cursor->ChangeCursor();

		if (inputManager->CheckClick()){
			int numUsos = actions->GetNumberUsesSkill(currAction);
			if ((*itLem)->SetSkill(numUsos, currAction))
				actions->DetractUseSkill(currAction);
		}

		//Esborrar lemming si surt del mapa. Debuggar per comprovar posicions.
		/*if ((*itLem)->GetPosX() + fons->GetPosX() < fons->GetPosX() || (*itLem)->GetPosX() + fons->GetPosX() > fons->GetPosX() + fons->GetWidthMap() || (*itLem)->GetPosY() + fons->GetPosY() < fons->GetPosY() || (*itLem)->GetPosY() + fons->GetPosY() > fons->GetPosY() + fons->GetHeightMap())
			lemmings.erase(itLem);*/
	}

	cursor->Update();
}

void SceneGame::render(){
	fons->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();

	actions->render();

	cursor->render();
}