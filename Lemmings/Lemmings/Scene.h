#pragma once
#include "SingletonManager.h"

class Scene
{
protected:
	InputManager* inputManager;

public:
	Scene();
	~Scene();

	virtual void init();
	virtual void update();
	virtual void render();
};