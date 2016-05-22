#include "SceneGame.h"


SceneGame::SceneGame(){
}


SceneGame::~SceneGame(){
}


void SceneGame::init(){
	for (int i = 0; i < 1; i++){
		Lemming *lemming = new Lemming();
		lemming->init(90 + i, 60);
		lemmings.push_back(lemming);
	}
	
	fons = new Map();
	fons->init(0, 0, "Assets/Levels/lvl01/lvl01.tmx", "colisiones", 3, "Assets/Levels/lvl01/TexturePixel.png", false, 1, 0, 0, 640, 480);

	actions = new Actions();
	//Fer getter del tmx per a obtenir el nombre d'usos que tindrà cada habilitat en aquest mapa.*******
	actions->init("0", "0", "1", "1", "0", "0", "1", "1");
	currAction = -1;
}

void SceneGame::update(){
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

		if (inputManager->CheckClick()){
			int numUsos = actions->GetNumberUsesSkill(currAction);
			if ((*itLem)->SetSkill(numUsos, currAction))
				actions->DetractUseSkill(currAction);
		}
	}
}

void SceneGame::render(){
	fons->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();

	actions->render();
}