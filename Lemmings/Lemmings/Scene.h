#pragma once
#include "SingletonManager.h"

class Scene
{
protected:
	InputManager* inputManager;

	AudioManager* audioManager;
	Sint32 idMusic;

public:
	Scene();
	~Scene();

	virtual void init();
	virtual void clear();
	virtual void update();
	virtual void render();
};