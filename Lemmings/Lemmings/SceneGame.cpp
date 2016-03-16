#include "SceneGame.h"

SceneGame::SceneGame(){
	sManager = SingletonManager::getInstanceSingleton();
}


SceneGame::~SceneGame(){
}


void SceneGame::Init(){
	Lemming lemming;
	lemming.Init(100, 100, "Imatges/ll.png", 0, 0, 32, 32);
	lemmings.push_back(lemming);
}

void SceneGame::Update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Update();
	sManager->videoManager->UpdateTime();
}

void SceneGame::Render(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Render();
	sManager->videoManager->clearScreen(0xFFFFFF);
	sManager->videoManager->updateScreen();
}