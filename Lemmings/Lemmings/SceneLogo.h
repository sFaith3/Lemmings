#pragma once
#include "Scene.h"

class SceneLogo :
	public Scene
{
public:
	SceneLogo();
	~SceneLogo();

	void init();
	void update();
	void render();
};

