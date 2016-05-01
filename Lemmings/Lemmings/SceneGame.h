#pragma once
#include "Scene.h"
#include "Utils.h"
#include "Lemming.h"
#include "Map.h"

class SceneGame :
	public Scene
{
private:
	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLem;

	Map *fons;

public:
	SceneGame();
	~SceneGame();

	void init();
	void update();
	void render();
};

