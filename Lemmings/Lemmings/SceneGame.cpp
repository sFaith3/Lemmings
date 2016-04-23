#include "SceneGame.h"

SceneGame::SceneGame(){
	sManager = SingletonManager::getInstanceSingleton();
}


SceneGame::~SceneGame(){
}


void SceneGame::Init(){
	Lemming lemming;
	lemming.Init(90, 20, "Assets/Images/lem_ani2.png", 0, 0, 32, 32);
	lemmings.push_back(lemming);

	fons.Init(0, 0, "Assets/Levels/level.tmx", 1, "Assets/Levels/tileset.png", 1, "Assets/Levels/mapaColprova2.tmx", 0, 0, 640, 480);
}

void SceneGame::Update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = itLem->GetPosX() / fons.GetSizeTile();
		int y1 = itLem->GetPosY() / fons.GetSizeTile();
		int x2 = (itLem->GetPosX() + itLem->GetWidth()) / fons.GetSizeTile();
		int y2 = (itLem->GetPosY() + itLem->GetHeight()) / fons.GetSizeTile();

		if (itLem->GetEstat() != itLem->FALL && (fons.GetMapa(x1, y1) == 91 && fons.GetMapa(x2, y2) == 91))
			itLem->SetCaure();
		else if (itLem->GetEstat() == itLem->FALL && (fons.GetMapa(x1, y1) != 91 || fons.GetMapa(x2, y2) != 91)){
			itLem->SetMoure();
		}

		itLem->Update();
	}

	sManager->getVideoManager()->updateTime();
}

void SceneGame::Render(){
	sManager->getVideoManager()->clearScreen(0xFFFFFF);

	fons.Render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Render();
	
	sManager->getVideoManager()->updateScreen();
}