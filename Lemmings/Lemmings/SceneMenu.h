#pragma once
#include "Scene.h"
#include "Background.h"
#include "Button.h"

class SceneMenu :
	public Scene
{
private:
	SingletonManager* sManager;

	Background fons;

	vector<Button*> buttons;

public:
	SceneMenu();
	~SceneMenu();

	void init();
	void update();
	void render();
};