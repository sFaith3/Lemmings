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
};