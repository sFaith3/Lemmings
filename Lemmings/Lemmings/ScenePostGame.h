#pragma once
#include "Scene.h"
#include "FileManager.h"
#include "ABCsAlphaNum.h"
#include "SceneManager.h"
#include "SceneGame.h"

class ScenePostGame :
	public Scene
{
private:
	int level;
	string lemmingsSaved;
	string lemmingsToSave;
	string codeLvl;

	Background* fons;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	FileManager* fileManager;

	SceneGame* sGame;

	SceneManager* smManager;

public:
	ScenePostGame();
	~ScenePostGame();

	void init();
	void clear();
	void update();
	void render();
};

