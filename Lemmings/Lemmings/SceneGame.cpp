#include "SceneGame.h"

SceneGame::SceneGame(){
	sManager = SingletonManager::getInstanceSingleton();
}


SceneGame::~SceneGame(){
}


void SceneGame::Init(){ // Paràmetres d'inicialització d'ins del mètode 'Init'.
	Lemming lemming;
	lemming.Init(90, 20, "Assets/Images/lem_ani2.png", 0, 0, 32, 32);
	lemmings.push_back(lemming);

	fons.Init(0, 0, "Assets/Levels/level.tmx", "Assets/Levels/tileset.png", "Assets/Levels/mapaCollision.tmx", 0, 0, 640, 480);
}

void SceneGame::Update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++){
		int x1 = itLem->GetPosX() / 32;
		int y1 = itLem->GetPosY() / 32;
		int x2 = (itLem->GetPosX() + itLem->GetWidth()) / 32;
		int y2 = (itLem->GetPosY() + itLem->GetHeight()) / 32;

		if (itLem->GetEstat() != itLem->FALL && (fons.getMapa(x1, y1) == 91 && fons.getMapa(x2, y2) == 91))
			itLem->SetFall();
		else if (itLem->GetEstat() == itLem->FALL && (fons.getMapa(x1, y1) != 91 || fons.getMapa(x2, y2) != 91)){
			itLem->SetMove();
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