#include "DoorEnter.h"


DoorEnter::DoorEnter(int x, int y, int timeToSpawn, int numInstancies){
	ElementGame::init(x, y, "Assets/Images/Doors/entrada.png", 0, 0, 57, 31, 1, 1, 126, 31, 69, 2, 25);
	
	timeToBeReady = 0.5 * 100;
	this->timeToSpawn = _timeToSpawn = timeToSpawn * 100;
	lastTime = 0;

	spawnning = false;
	leftToSpawn = numInstancies;
	
	currEstat = NOT_READY;
}


DoorEnter::~DoorEnter(){

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
			if (leftToSpawn == 0)
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
	temps = 50 - temps;
	timeToSpawn = ((temps * _timeToSpawn) / 50) + _timeToSpawn;
}

int DoorEnter::getNumToSpawn(){
	return leftToSpawn;
}

void DoorEnter::notMoreSpawns(){
	currEstat = EMPTY;
}