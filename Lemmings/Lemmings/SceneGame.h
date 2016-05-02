#pragma once
#include "Scene.h"
#include "Utils.h"
#include "Lemming.h"
#include "Map.h"
#include "Actions.h"

class SceneGame :
	public Scene
{
private:
	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLem;

	Map *fons;

	Actions *action;

public:
	SceneGame();
	~SceneGame();

	void init();
	void update();
	void render();
};

