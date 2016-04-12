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

	fondo.Init(0, 0, "Assets/Levels/level.tmx", "Assets/Levels/tileset.png", 0, 0, 640, 480);
}

void SceneGame::Update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Update();
	sManager->videoManager->updateTime();
}

void SceneGame::Render(){
	sManager->videoManager->clearScreen(0xFFFFFF);

	fondo.Render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Render();
	
	sManager->videoManager->updateScreen();
}