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
#include "Word.h"
#include "Counter.h"

class SceneGame :
	public Scene
{
private:
	SceneGame();

	static SceneGame* gInstance; /*!<	Singleton instance*/

	Map* map;

	Timer* time;

	Actions* actions;
	int currAction;

	// Scene parameters where the mission is reported. It also sets the HUD elements corresponding to these variables.
	int numLemmings;
	int lemmingsToSave; // In a percentage.
	string remainingTime, releaseRate; 

	int lemmingsDead;
	int lemmingsSaved;

	bool gameFinished; // It's activated when the game ends in order to perform the relevant actions.

	DoorEnter* enterDoor;
	ElementGame* exitDoor;

	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLemmings;
	
	Word* states[17];
	int currState;

	Counter* counters[2];

	enum SoundsEnum{
		StartGame, SelectSkill, PutSkill
	};
	int idSounds[3];
	int initialSound;

	bool cursorChanged;
	Cursor* cursor;

	ScenePostGame* sPostGame;
	GameStats* gameStats;
	SceneManager* smManager;

public:
	~SceneGame();

	//! Gets Singleton instance.
	static SceneGame* getInstanceSceneGame();

	void initFromPreGame(Map* map, int numLemmings, int lemmingsToSave, string rateSpeed, string time);

	void init();
	void clear();
	void update();
	void render();

	void updateActions();
	void updateDoors();
	void updateLemmings();
	void updateChangeCursor();
	void checkUnpaused();
};

#endif