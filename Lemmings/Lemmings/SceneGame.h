#pragma once
#include "Scene.h"
#include "Utils.h"
#include "Lemming.h"
#include "Map.h"
#include "Actions.h"
#include "SceneManager.h"
#include "Cursor.h"
#include "DoorEnter.h"
#include "Timer.h"

class SceneGame :
	public Scene
{
private:
	Map* fons;

	Timer* temps;

	Actions* actions;
	int currAction;

	int lemmingsToSave;
	int lemmingsSaved;

	DoorEnter* enterDoor;
	ElementGame* exitDoor;

	vector<Lemming*> lemmings;
	vector<Lemming*>::iterator itLem;
	
	bool cursorChanged;
	Cursor* cursor;

	SceneManager* smManager;

public:
	SceneGame();
	~SceneGame();

	void init();
	void update();
	void render();
};