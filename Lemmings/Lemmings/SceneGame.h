#pragma once
#include "Utils.h"
#include "Lemming.h"

class SceneGame
{
private:
	vector<Lemming> lemmings;
	vector<Lemming>::iterator itLem;

	SingletonManager* sManager;

public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Render();
};

