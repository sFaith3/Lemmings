#ifndef SCENEPOSTGAME_H
#define SCENEPOSTGAME_H

#include "Utils.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "ABCsAlphaNum.h"
#include "Background.h"

class ScenePostGame :
	public Scene
{
private:
	ScenePostGame();

	static ScenePostGame* gInstance; /*!<	Singleton instance*/

	string lemmingsSaved;
	string lemmingsToSave;

	Background* fons;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	FileManager* fileManager;

	GameStats* gameStats;

	SceneManager* smManager;

public:
	~ScenePostGame();

	//! Gets Singleton instance.
	static ScenePostGame* getInstanceScenePostGame();

	void initFromGame(int lemmingsSaved, int lemmingsToSave);

	void init();
	void clear();
	void update();
	void render();
};

#endif