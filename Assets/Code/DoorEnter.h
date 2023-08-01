#pragma once
#include "ElementGame.h"

class DoorEnter :
	public ElementGame
{
private:
	int timeToBeReady; // Time it takes to switch to the next state after opening the doors.
	int currentTimeToSpawn; // The current time it takes to instantiate an element.
	int initialTimeToSpawn; // For auxiliary purposes in the 'currentTimeToSpawn' calculation.
	int lastSpawnTime; // Auxiliary to calculate the time to instantiate an element.

	bool isSpawning; // This is activated when the time is completed. So it tells SceneGame where an element has to be spawned.
	int remainingToSpawn; // Elements remaining to be spawned.

	enum EstatsEnum{
		NOT_READY, OPENING, READY, EMPTY
	};
	int currEstat;

	int idSoundOpen;
	bool soundOpen;

public:
	DoorEnter(int x, int y, int currentTimeToSpawn, int numInstancies);
	~DoorEnter();

	int getRemainingToSpawn();
	bool getIsSpawning();

	void update(int time);
	void updateTimeToSpawn(int time);

	void notMoreSpawns();
};

