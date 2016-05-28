#include "DoorEnter.h"


DoorEnter::DoorEnter(int x, int y, const char* img, int srcX, int srcY, int w, int h, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim, int timeToSpawn, int numInstancies){
	ElementGame::init(x,y, img, srcX, srcY, w, h, 1, 1, wSpriteSheet, hSpriteSheet, toNextSpriteX, numImgs, fpsAnim);
	
	timeToBeReady = 2;
	this->timeToSpawn = timeToSpawn;
	lastTime = 0;

	spawnning = false;
	leftToSpawn = numInstancies;
	
	currEstat = NOT_READY;
}


DoorEnter::~DoorEnter()
{
}


void DoorEnter::update(int temps){
	switch (currEstat){
	case NOT_READY:
		if (temps >= timeToBeReady){
			currEstat = OPENNING;
			lastTime = timeToBeReady;
		}
		break;
	case OPENNING:
		UpdateAnimacio();
		if (contImatges == numImatges)
			currEstat = READY;
		break;
	case READY:
		temps -= lastTime;
		if (temps >= timeToSpawn){
			lastTime += timeToSpawn;
			spawnning = true;
			leftToSpawn--;
			if (leftToSpawn <= 0)
				currEstat = EMPTY;
		}
		break;
	case EMPTY:
		break;
	}
}


bool DoorEnter::getSpawnning(){
	if (spawnning){
		spawnning = false;
		return !spawnning;
	}

	return false;
}


void DoorEnter::setTimeToSpawn(int temps){
	//timeToSpawn 
}