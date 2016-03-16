#include "SingletonManager.h"

#include"SDL.h"

SingletonManager* SingletonManager::sInstance = NULL;

SingletonManager::SingletonManager(){
	sInstance = getInstanceSingleton();

	inputManager = InputManager::getInstanceInput();
	videoManager = VideoManager::getInstanceVideo();
	audioManager = AudioManager::getInstanceAudio();
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