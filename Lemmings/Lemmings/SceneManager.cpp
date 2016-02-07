#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init(int scene){
	currentScene = scene;
	if (currentScene == 1){
		tank = new TankScene();
		tank->Init();
	}
	else if (currentScene == 2){
		music = new MusicPlayer();
		music->Init();
	}
	
}

void SceneManager::Update(){
	if (currentScene == 1){
		tank->Update();
	}
	else if (currentScene == 2){
		music->Update();
	}
}

void SceneManager::Render(){
	if (currentScene == 1){
		tank->Render();
	}
	else if (currentScene == 2){
		music->Render();
	}
}