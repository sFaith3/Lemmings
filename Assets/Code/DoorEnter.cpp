#include "DoorEnter.h"


DoorEnter::DoorEnter(int x, int y, int timeToSpawn, int numInstancies){
	ElementGame::init(x, y, "Assets/Art/Images/Doors/entrada.png", false, 0, 0, 57, 31, 1, 1, 126, 31, 69, 2, 25);
	
	timeToBeReady = 1000;
	this->timeToSpawn = _timeToSpawn = timeToSpawn * 100;
	lastTime = 0;

	spawnning = false;
	leftToSpawn = numInstancies;
	
	currEstat = NOT_READY;

	idSoundOpen = audioManager->getSoundID("Assets/Art/Audios/Sounds/openDoor.wav");
	soundOpen = true;
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
		if (soundOpen){
			audioManager->playSound(idSoundOpen);
			soundOpen = false;
		}
		if (contImatges == numImatges)
			currEstat = READY;
		UpdateAnimacio();
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