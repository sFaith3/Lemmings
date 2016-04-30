#pragma once
#include "Scene.h"

class SceneCodeLevel :
	public Scene
{
public:
	SceneCodeLevel();
	~SceneCodeLevel();

	void init();
	void update();
	void render();
};

