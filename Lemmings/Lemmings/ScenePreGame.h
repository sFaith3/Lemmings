#pragma once
#include "Scene.h"
#include "FileManager.h"
#include "ABCsAlphaNum.h"
#include "Element.h"
#include "SceneManager.h"

class ScenePreGame :
	public Scene
{
private:
	FileManager* fileManager;

	int level;
	string nameLvl;
	string numLemming;
	string lemmingsToSave;
	string releaseRate;
	string timeLvl;
	string rating;

	Element* fons;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	SceneManager* smManager;

public:
	ScenePreGame();
	~ScenePreGame();

	void init();
	void update();
	void render();

	void SetRating(string rating);

	void IncrementLevel();
};

