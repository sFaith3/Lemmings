#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H

#include "Utils.h"

class SingletonManager
{
private:
	SingletonManager();
	
	static SingletonManager* sInstance;
	
	SceneManager* sceneManager;
	InputManager* inputManager;
	VideoManager* videoManager;
	ResourceManager* resourceManager;

public:
	~SingletonManager();

	static SingletonManager* getInstanceSingleton();

	SceneManager* getScene();
	InputManager* getInput();
	VideoManager* getVideo();
	ResourceManager* getResource();
};

#endif