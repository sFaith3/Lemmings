#pragma once
#include "Scene.h"
#include "FileManager.h"
#include "ABCsAlphaNum.h"
#include "SceneManager.h"
#include "SceneGame.h"

class ScenePreGame :
	public Scene
{
private:
	int level;
	string nameLvl;
	string numLemmings;
	string lemmingsToSave;
	string releaseRate;
	string timeLvl;
	string rating;

	Background* fons;

	Map* mapa;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	FileManager* fileManager;

	SceneGame* sGame;

	SceneManager* smManager;

public:
	ScenePreGame();
	~ScenePreGame();

	void init();
	void clear();
	void update();
	void render();

	void SetRating(string rating);

	void IncrementLevel();
};

