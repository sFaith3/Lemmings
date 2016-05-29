#pragma once
#include "ElementGame.h"
class DoorEnter :
	public ElementGame
{
private:
	int timeToBeReady;
	int timeToSpawn, _timeToSpawn;
	int lastTime;

	bool spawnning;
	int leftToSpawn; // Elements que falten per crear.

	enum EstatsEnum{
		NOT_READY, OPENNING, READY, EMPTY
	};
	int currEstat;

public:
	DoorEnter(int x, int y, int timeToSpawn, int numInstancies);
	~DoorEnter();

	void update(int temps);

	bool getSpawnning();

	void setTimeToSpawn(int temps);
};

