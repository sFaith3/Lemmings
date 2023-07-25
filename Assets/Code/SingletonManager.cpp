#include "SingletonManager.h"
#include"SDL.h"

SingletonManager* SingletonManager::sInstance = NULL;

SingletonManager::SingletonManager(){
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


InputManager* SingletonManager::getInputManager(){
	return inputManager;
}

VideoManager* SingletonManager::getVideoManager(){
	return videoManager;
}

AudioManager* SingletonManager::getAudioManager(){
	return audioManager;
}

ResourceManager* SingletonManager::getResourceManager(){
	return resourceManager;
}