#ifndef SCENEPREGAME_H
#define SCENEPREGAME_H

#include "Utils.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "FileManager.h"
#include "ABCsAlphaNum.h"

class ScenePreGame :
	public Scene
{
private:
	ScenePreGame();

	static ScenePreGame* gInstance; /*!<	Singleton instance*/

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

	GameStats* gameStats;

	SceneManager* smManager;

public:
	~ScenePreGame();

	//! Gets Singleton instance.
	static ScenePreGame* getInstanceScenePreGame();

	void init();
	void clear();
	void update();
	void render();
};

#endif