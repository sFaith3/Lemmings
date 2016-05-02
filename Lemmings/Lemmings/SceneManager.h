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
		LOGO, MENU, CODE_LEVEL, /*PRE_GAME,*/ GAME
	};

	void init();
	void update();
	void render();

	void changeScene(SceneEnum next_scene);

	int getCurrScene();

private:
	SceneManager();

	static SceneManager* smInstance; /*!<	Singleton instance*/
	
	vector<Scene*> mVectorScenes;
	SceneEnum mCurrScene;

	VideoManager* videoManager;
};

#endif