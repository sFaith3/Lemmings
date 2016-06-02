#ifndef SCENEPOSTGAME_H
#define SCENEPOSTGAME_H

#include "FileManager.h"
#include "ABCsAlphaNum.h"
#include "SceneManager.h"
#include "Background.h"

class ScenePostGame :
	public Scene
{
private:
	ScenePostGame();

	static ScenePostGame* gInstance; /*!<	Singleton instance*/

	int level;
	string lemmingsSaved;
	string lemmingsToSave;
	bool winGame;

	Background* fons;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	FileManager* fileManager;

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

	void setWinGame();
};

#endif