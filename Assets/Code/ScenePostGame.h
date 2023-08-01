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

	Background* background;

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

	GameStats* gameStats;
	FileManager* fileManager;
	SceneManager* sceneManager;

public:
	~ScenePostGame();

	//! Gets Singleton instance.
	static ScenePostGame* getInstanceScenePostGame();

	void initFromGame(const int lemmingsSaved, const int lemmingsToSave);
	void init();
	void initDigitsNumberLemmingsSaved(int& xDigit, int& _xDigit, int& yDigit, float scaleX, int alphaNum);
	void initDigitsNumberLemmingsToSave(int& xDigit, int& _xDigit, int& yDigit, float scaleX, int alphaNum);
	void initDigitsNumberLevel(int& xDigit, int& yDigit, float scaleX);
	void initDigitsCodeLevel(int& xDigit, int& yDigit, float scaleX);
	void clear();
	void update();
	void render();
};

#endif