#pragma once
#include "Utils.h"
#include "Lemming.h"
#include "Map.h"
class SceneGame
{
private:
	vector<Lemming> lemmings;
	vector<Lemming>::iterator itLem;

	SingletonManager* sManager;

	Map fons;
	Map mapCollision;

public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Render();

	//Map getMapCollision();
	int getMapCollision();
};

