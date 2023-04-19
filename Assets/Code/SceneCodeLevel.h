#ifndef SCENECODELEVEL_H
#define SCENECODELEVEL_H

#include "Utils.h"
#include "SceneManager.h"

class SceneCodeLevel :
	public Scene
{
private:
	SceneCodeLevel();

	static SceneCodeLevel* gInstance; /*!<	Singleton instance*/

public:
	~SceneCodeLevel();

	//! Gets Singleton instance.
	static SceneCodeLevel* getInstanceSceneCodeLevel();

	void init();
	void update();
	void render();
};

#endif