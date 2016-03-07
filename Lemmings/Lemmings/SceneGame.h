#pragma once
#include "Lemming.h"
class SceneGame
{
private:
	vector<Lemming> lemmings;
	vector<Lemming>::iterator itLem;

public:
	SceneGame();
	~SceneGame();

	void Init();
	void Update();
	void Render();
};

