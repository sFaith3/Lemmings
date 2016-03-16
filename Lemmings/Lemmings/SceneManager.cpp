#include "SceneManager.h"

#include "SDL.h"

SceneManager* SceneManager::smInstance = NULL;

SceneManager::SceneManager(){
	sManager = SingletonManager::getInstanceSingleton();
}

SceneManager::~SceneManager(){
	sManager->videoManager->close();
}

SceneManager* SceneManager::getInstanceSM(){
	if (smInstance == NULL)
		smInstance = new SceneManager();

	return smInstance;
}

void SceneManager::Init(int scene){
	currentScene = scene;
	switch (currentScene){
	case JOC:
		game.Init();
		break;

	default:
		break;
	}
}

void SceneManager::Update(){
	switch (currentScene){
	case JOC:
		game.Update();
		break;
	
	default:
		break;
	}
}

void SceneManager::Render(){
	switch (currentScene){
	case JOC:
		game.Render();
		break;

	default:
		break;
	}
}