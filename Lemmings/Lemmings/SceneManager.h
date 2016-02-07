#pragma once
#include "TankScene.h"
#include "MusicPlayer.h"
class SceneManager
{
private:
	TankScene* tank;
	MusicPlayer* music;
	int currentScene;

public:
	SceneManager();
	void Init(int scene);
	void Update();
	void Render();
	~SceneManager();
};

