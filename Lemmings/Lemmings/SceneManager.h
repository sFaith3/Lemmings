#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Scene.h"
#include "SingletonManager.h"

using namespace std;

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum{
	LOGO, MENU, CODE_LEVEL, PRE_GAME, GAME
};

#define NUM_SCENES 5
#define _LASTSCENE

class SceneManager
{
private:
	SceneManager();

	static SceneManager* smInstance; /*!<	Singleton instance*/
	
	vector<Scene*> mVectorScenes;
	SceneEnum mCurrScene;

	SingletonManager* sManager;

public:
	~SceneManager();

	//! Gets Singleton instance.
	static SceneManager* getInstanceSM();

	void init();
	void update();
	void render();

	void changeScene(SceneEnum next_scene);
};

#endif