#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "Utils.h"
#include "SceneManager.h"
#include "ScenePostGame.h"
#include "Lemming.h"
#include "Map.h"
#include "Actions.h"
#include "Cursor.h"
#include "DoorEnter.h"
#include "Timer.h"

class SceneGame :
	public Scene
{
private:
	SceneGame();

	static SceneGame* gInstance; /*!<	Singleton instance*/

	Map* mapa;

	Timer* temps;

	Actions* actions;
	int currAction;

	// Paràmetres de l'escena on s'informa sobre la missió.
	int numLemmings;
	int lemmingsToSave;
	string tempsRestant, releaseRate;

	int lemmingsMorts;
	int lemmingsSaved;

	bool gameFinish;

	DoorEnter* enterDoor;
	ElementGame* exitDoor;

	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLem;
	
	bool cursorChanged;
	Cursor* cursor;

	ScenePostGame* sPostGame;

	GameStats* gameStats;

	SceneManager* smManager;

public:
	~SceneGame();

	//! Gets Singleton instance.
	static SceneGame* getInstanceSceneGame();

	void initFromPreGame(Map* mapa, int numLemmings, int lemmingsToSave, string rateSpeed, string temps);

	void init();
	void clear();
	void update();
	void render();
};

#endif