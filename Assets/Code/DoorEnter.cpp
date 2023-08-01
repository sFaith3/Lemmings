#include "DoorEnter.h"

DoorEnter::DoorEnter(int x, int y, int currentTimeToSpawn, int numInstances)
{
	ElementGame::init(x, y, "Assets/Art/Images/Doors/entry.png", false, 0, 0, 57, 31, 1, 1, 126, 31, 69, 2, 25);

	timeToBeReady = 1000;
	this->currentTimeToSpawn = initialTimeToSpawn = currentTimeToSpawn * 100;
	lastSpawnTime = 0;

	isSpawning = false;
	remainingToSpawn = numInstances;

	currEstat = NOT_READY;

	idSoundOpen = audioManager->getSoundID("Assets/Art/Audios/Sounds/openDoor.wav");
	soundOpen = true;
}

DoorEnter::~DoorEnter()
{
}


int DoorEnter::getRemainingToSpawn()
{
	return remainingToSpawn;
}

bool DoorEnter::getIsSpawning()
{
	if (isSpawning)
	{
		isSpawning = false;
		return true;
	}

	return false;
}


void DoorEnter::update(int time)
{
	switch (currEstat)
	{
	case NOT_READY:
		if (time >= timeToBeReady)
		{
			currEstat = OPENING;
			lastSpawnTime = timeToBeReady;
		}
		break;
	case OPENING:
		if (soundOpen)
		{
			audioManager->playSound(idSoundOpen);
			soundOpen = false;
		}
		if (currentSprite == numSprites)
			currEstat = READY;
		UpdateAnimation();
		break;
	case READY:
		time -= lastSpawnTime;
		if (time >= currentTimeToSpawn)
		{
			lastSpawnTime += currentTimeToSpawn;
			isSpawning = true;
			remainingToSpawn--;
			if (remainingToSpawn == 0)
				currEstat = EMPTY;
		}
		break;
	case EMPTY:
		break;
	}
}

void DoorEnter::updateTimeToSpawn(int time)
{
	time = 50 - time;
	currentTimeToSpawn = ((time * initialTimeToSpawn) / 50) + initialTimeToSpawn;
}


void DoorEnter::notMoreSpawns()
{
	currEstat = EMPTY;
}