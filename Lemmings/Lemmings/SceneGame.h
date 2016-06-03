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

	// Paràmetres de l'escena on s'informa sobre la missió. També seteja els elements de la HUD que corresponen a aquestes variables.
	int numLemmings;
	int lemmingsToSave;
	string tempsRestant, releaseRate; 

	int lemmingsMorts;
	int lemmingsSaved;

	bool gameFinish; // S'activa quan finalitza el joc, per tal de realitzar les accions pertinents.

	DoorEnter* enterDoor;
	ElementGame* exitDoor;

	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLem;
	
	// Cursor.
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