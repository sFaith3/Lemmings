#include "SceneGame.h"

SceneGame::SceneGame(){
	sManager = SingletonManager::getInstanceSingleton();
}


SceneGame::~SceneGame(){
}


void SceneGame::Init(){ // Paràmetres d'inicialització
	Lemming lemming;
	lemming.Init(90, 20, "Assets/Images/lem_ani2.png", 0, 0, 32, 32);
	lemmings.push_back(lemming);

	fons.Init(0, 0, false, "Assets/Images/map.png", NULL , 0, 0, 640, 480);
	mapCollision.Init(0, 0, true, "Assets/Levels/mapaColprova2.xml", NULL, 0, 0, NULL, NULL);
}

void SceneGame::Update(){
	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Update();
	sManager->getVideoManager()->updateTime();
}

void SceneGame::Render(){
	sManager->getVideoManager()->clearScreen(0xFFFFFF);

	fons.Render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		itLem->Render();
	
	sManager->getVideoManager()->updateScreen();
}


int SceneGame::getMapCollision(){
	return mapCollision.getMapa();
}