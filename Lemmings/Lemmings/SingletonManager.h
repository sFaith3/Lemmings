#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H

#include "SceneManager.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "ResourceManager.h"

class SingletonManager
{
private:
	SingletonManager();
	
	static SingletonManager* sInstance;

public:
	~SingletonManager();

	static SingletonManager* getInstanceSingleton();

	SceneManager* sceneManager;
	InputManager* inputManager;
	VideoManager* videoManager;
	ResourceManager* resourceManager;
};

#endif