#include "SingletonManager.h"


SingletonManager* SingletonManager::sInstance = NULL;

SingletonManager::SingletonManager(){
	sInstance = getInstanceSingleton();

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