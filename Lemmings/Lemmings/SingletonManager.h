#include "SceneManager.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "ResourceManager.h"

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
};