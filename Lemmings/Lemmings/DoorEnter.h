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
	DoorEnter(int x, int y, const char* img, int srcX, int srcY, int w, int h, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim, float timeToSpawn, int numInstancies);
	~DoorEnter();

	void update(int temps);
	void setTimeToSpawn(int temps);

	bool getSpawnning();

	void setTimeToSpawn(int temps);
};

