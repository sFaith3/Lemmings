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

	// Information about the level.
	string nameLvl;
	string numLemmings;
	string lemmingsToSave;
	string releaseRate; // Time it takes the DoorEnter class to instantiate Lemmings.
	string timeLvl;
	string rating; // Difficulty of the level.

	// Numbers and letters that come from the variables of the level information.
	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	Background* background;

	Map* map;

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

	bool isLastMap(const int LEVEL);
	void loadLevelInfo(const int LEVEL);
	void initLevelInfo(const int LEVEL, int& numLem, int& lemToSave);
	void initLevelInfoForRender(const int LEVEL, int& numLem, int& lemToSave);
	void getPathsToInitMap(string& pathMap, string& pathTilesets, const int LEVEL);
	void initMap(const char* PATH_MAP, const char* PATH_TILESETS);
	bool isNextScene();
	bool isPreviousScene();
};

#endif