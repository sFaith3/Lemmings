#ifndef SCENEGAME_H
#define SCENEGAME_H

//#include "Utils.h"
#include "Lemming.h"
#include "Map.h"
#include "Actions.h"
#include "SceneManager.h"
#include "Cursor.h"
#include "DoorEnter.h"
#include "Timer.h"
#include "ScenePostGame.h"

class SceneGame :
	public Scene
{
private:
	SceneGame();

	static SceneGame* gInstance; /*!<	Singleton instance*/

	bool mutejarSo;

	bool pausa;

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

	void setMuteigSo(bool mute);
};

#endif