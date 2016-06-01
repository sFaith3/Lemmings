#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Utils.h"
#include "Scene.h"
#include "SingletonManager.h"

//#define _LASTSCENE

class SceneManager
{
public:
	~SceneManager();

	//! Gets Singleton instance.
	static SceneManager* getInstanceSM();

	//! Enum Scenes.
	/*! All the Scenes in the game. */
	enum SceneEnum{
		MENU, CODE_LEVEL, PRE_GAME, GAME, POST_GAME
	};

	void init();
	void update();
	void render();

	void changeScene(SceneEnum next_scene);

	int getNumCurrScene();

private:
	SceneManager();

	static SceneManager* smInstance; /*!<	Singleton instance*/
	
	vector<Scene*> mVectorScenes;
	SceneEnum mCurrScene;

	VideoManager* videoManager;
};

#endif