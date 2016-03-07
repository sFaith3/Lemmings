#include "SingletonManager.h"


SingletonManager* SingletonManager::sInstance = NULL;

SingletonManager::SingletonManager(){
	sceneManager = SceneManager::getInstanceSM();
	inputManager = InputManager::getInstanceInput();
	videoManager = VideoManager::getInstanceVideo();
	resourceManager = ResourceManager::getInstanceResourceManager();
}

SingletonManager::~SingletonManager(){

}

SingletonManager* SingletonManager::getInstanceSingleton(){
	if (sInstance == NULL){
		sInstance = new SingletonManager();
	}
	return sInstance;
}

SceneManager* SingletonManager::getScene(){
	return sceneManager->getInstanceSM();
}

InputManager* SingletonManager::getInput(){
	return inputManager->getInstanceInput();
}

VideoManager* SingletonManager::getVideo(){
	return videoManager->getInstanceVideo();
}

ResourceManager* SingletonManager::getResource(){
	return resourceManager->getInstanceResourceManager();
}