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

	action = new Actions();
	int hAction = 61;
	action->init(0, SCREEN_HEIGHT - hAction, "Assets/Images/hud.png", 0, 0, 480, hAction);
}

void SceneGame::update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = (*itLem)->GetPosX() / fons->GetSizeTile();
		int y1 = (*itLem)->GetPosY() / fons->GetSizeTile();
		int x2 = ((*itLem)->GetPosX() + (*itLem)->GetWidth()) / fons->GetSizeTile();
		int y2 = ((*itLem)->GetPosY() + (*itLem)->GetHeight()) / fons->GetSizeTile();
		(*itLem)->update(fons, x1, y1, x2, y2);
	}
}

void SceneGame::render(){
	fons->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();
}