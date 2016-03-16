#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H

#include "InputManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "ResourceManager.h"

class SingletonManager
{
private:
	SingletonManager();
	
	static SingletonManager* sInstance;

public:
	~SingletonManager();

	static SingletonManager* getInstanceSingleton();

	InputManager* inputManager;
	VideoManager* videoManager;
	AudioManager* audioManager;
	ResourceManager* resourceManager;
};

#endif