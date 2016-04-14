#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SceneGame.h"

class SceneManager
{
private:
	static SceneManager* smInstance;

	enum escenes{
		JOC, MENU
	};
	int currentScene;

	SceneGame game;

	SingletonManager* sManager;

public:
	SceneManager();
	~SceneManager();

	static SceneManager* getInstanceSM();

	void Init(int scene);
	void Update();
	void Render();

	//SceneGame getSceneGame();
	int getMapCollisionSceneGame();
};

#endif