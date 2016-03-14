#include "SceneManager.h"

#include "SDL.h"

SceneManager* SceneManager::smInstance = NULL;

SceneManager::SceneManager(){

}

SceneManager::~SceneManager(){

}

SceneManager* SceneManager::getInstanceSM(){
	if (smInstance == NULL){

		smInstance = new SceneManager();
	}
	return smInstance;
}

void SceneManager::Init(int scene){
	currentScene = scene;
	/*if (currentScene == 1){
		// Crear escena de joc.
		// Inicialitzar-la.		
	}*/
}

void SceneManager::Update(){
	//if (currentScene == 1){
		// Updates
	//}
	//else if (currentScene == 2){
		
	//}
}

void SceneManager::Render(){
	//if (currentScene == 1){
		
	//}
	//else if (currentScene == 2){
		
	//}
}