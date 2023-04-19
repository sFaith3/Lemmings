#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H

#include "SDL\InputManager.h"
#include "SDL\VideoManager.h"
#include "SDL\AudioManager.h"
#include "SDL\ResourceManager.h"

class SingletonManager
{
private:
	SingletonManager();
	
	static SingletonManager* sInstance;

	InputManager* inputManager;
	VideoManager* videoManager;
	AudioManager* audioManager;
	ResourceManager* resourceManager;

public:
	~SingletonManager();

	static SingletonManager* getInstanceSingleton();

	InputManager* getInputManager();
	VideoManager* getVideoManager();
	AudioManager* getAudioManager();
	ResourceManager* getResourceManager();
};

#endif