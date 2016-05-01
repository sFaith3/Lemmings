#include "SceneGame.h"

SceneGame::SceneGame(){
}


SceneGame::~SceneGame(){
}


void SceneGame::init(){
	Lemming *lemming = new Lemming();
	lemming->init(90, 60, "Assets/Images/lem_ani.png", 4, 0, 10, 10);
	lemmings.push_back(lemming);
	
	fons = new Map();
	fons->init(0, 0, "Assets/Levels/lvl01/lvl01.tmx", "colisiones", 3, "Assets/Levels/lvl01/TexturePixel.png", false, 1, 0, 0, 640, 480);
}

void SceneGame::update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = (*itLem)->GetPosX() / fons->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / fons->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / fons->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / fons->GetSizeTile();

		if ((*itLem)->GetEstat() != (*itLem)->FALL && (fons->GetMapa(x1, y1) == 0 && fons->GetMapa(x2, y2) == 0))
			(*itLem)->SetCaure();
		else if ((*itLem)->GetEstat() == (*itLem)->FALL && (fons->GetMapa(x1, y1) != 0 || fons->GetMapa(x2, y2) != 0)){
			(*itLem)->SetMoure();
		}

		/*if ((*itLem)->GetEstat() == (*itLem)->MOVE){
			if ((*itLem)->GetDir() == 0 && fons->GetMapa(x2 + 1, y2 - 1) != 0)
				(*itLem)->SetDir(2);
			else if ((*itLem)->GetDir() == 2 && fons->GetMapa(x1 - 1, y2 - 1) != 0)
				(*itLem)->SetDir(0);
		}*/

		(*itLem)->update();
	}
}

void SceneGame::render(){
	fons->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();
}