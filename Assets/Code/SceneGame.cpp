#include "SceneGame.h"


SceneGame *SceneGame::gInstance = NULL;

SceneGame::SceneGame()
{
	actions = new Actions();

	numLemmings = lemmingsToSave = 0;
	remainingTime = releaseRate = "";

	lemmingsDead = lemmingsSaved = 0;

	gameFinished = false;

	exitDoor = new ElementGame();

	for (int i = 0; i < NUM_STATES; i++)
	{
		states[i] = new Word();
	}

	counters[0] = new Counter();
	counters[1] = new Counter();

	cursorChanged = false;
	cursor = Cursor::getInstanceCursor();

	sPostGame = ScenePostGame::getInstanceScenePostGame();
	gameStats = GameStats::getInstanceGameStats();
	smManager = SceneManager::getInstanceSM();
}

SceneGame::~SceneGame()
{
}


SceneGame *SceneGame::getInstanceSceneGame()
{
	if (gInstance == NULL)
		gInstance = new SceneGame();

	return gInstance;
}


void SceneGame::initFromPreGame(Map *map, int numLemmings, int lemmingsToSave, string rateSpeed, string time)
{
	this->map = map;
	this->numLemmings = numLemmings;
	this->lemmingsToSave = lemmingsToSave;
	releaseRate = rateSpeed;
	remainingTime = time + ":00";
}

void SceneGame::init()
{
	idMusic = audioManager->getMusicID("Assets/Art/Audios/Music/inGame.wav");

	lemmingsDead = lemmingsSaved = 0;

	gameFinished = false;

	map->SetPositionTiles(-475, 22);
	map->SetScaleTiles(1, 1);

	currAction = actions->init(1, 1, releaseRate, "10", "10", "10", "10", "10", "10", "10", "10");

	// Initialization of the game doors, the spawn point, and the start line of the lemmings.
	enterDoor = new DoorEnter(110, 80, 20, numLemmings);
	exitDoor->init(338, 200, "Assets/Art/Images/Doors/exit.png", false, 0, 0, 42, 31, 1, 1, 92, 31, 49, 2, 12);

	int x, y;
	x = 20;
	y = 260;
	const string NAME_STATES[] = {
		"MOVE", "FALL", "BREAK", "GLIDE", "CLIMB", "DIG", "PICK", "STOP", "STAIR", "EXPLOSION",
		"DEAD", "DEADFALL", "OPENUMBRELLA", "NOSTAIR", "ENDCLIMB", "RESCUED", "EXPLODING"};
	for (int i = 0; i < NUM_STATES; i++)
	{
		states[i]->init(x, y, 1, 1, 15, NAME_STATES[i]);
	}
	currState = -1;

	counters[0]->init(155, 258, "Assets/Art/Images/HUD/Counters/Out.png", 35, 19, 1, 1, 42, 15, false);
	counters[1]->init(253, 258, "Assets/Art/Images/HUD/Counters/In.png", 25, 19, 1, 1, 33, 15, true);

	idSounds[0] = audioManager->getSoundID("Assets/Art/Audios/Sounds/startGame.wav");
	idSounds[1] = audioManager->getSoundID("Assets/Art/Audios/Sounds/selectSkill.wav");
	idSounds[2] = audioManager->getSoundID("Assets/Art/Audios/Sounds/putSkill.wav");
	initialSound = false;

	time = new Timer(355, 258, remainingTime);
	time->start();

	audioManager->playMusic(idMusic, -1);
}

void SceneGame::clear()
{
	idMusic = -1;

	if (gameStats->GetPause())
		gameStats->SetPause(false);

	delete map;

	delete time;

	currAction = -1;

	delete enterDoor;

	lemmings.clear();
	lemmings.resize(0);

	for (int i = 0; i < NUM_STATES; i++)
	{
		states[i]->clear();
	}
	if (currState != -1)
		currState = -1;

	counters[0]->clear();
	counters[1]->clear();

	for (int i = 0; i <= (int)MaxNumSoundsEnum; i++)
	{
		idSounds[i] = -1;
	}
}

void SceneGame::update()
{
	if (!gameStats->GetPause())
	{
		updateActions();
		time->update();
		if (!initialSound)
		{
			if (time->getTimeMs() >= 30)
			{
				audioManager->playSound(idSounds[StartGame]);
				initialSound = true;
			}
		}
		updateLemmings();
		updateDoors();
		updateChangeCursor();

		if (time->getTimeOut())
		{
			audioManager->pauseMusic();
			gameFinished = true;
		}

		if (gameFinished)
		{
			int _lemmingsToSave = (lemmingsToSave * numLemmings) / 100; // No percentage.
			if (lemmingsSaved >= _lemmingsToSave)
				gameStats->SetWin(true);

			int _lemmingsSaved = (lemmingsSaved * 100) / numLemmings; // With percentage.
			sPostGame->initFromGame(_lemmingsSaved, lemmingsToSave);
			smManager->changeScene(smManager->POST_GAME);
			gameFinished = false;
		}

		if (inputManager->isPause())
		{
			gameStats->SetPause(true);
			audioManager->pauseMusic();
			inputManager->resetPause();
		}
	}
	else if (gameStats->GetPause() && inputManager->isPause())
	{
		gameStats->SetPause(false);
		audioManager->resumeMusic();
		inputManager->resetPause();
	}
	else if (gameStats->GetPause() && inputManager->isClickLeft())
		checkUnpaused();

	cursor->update();

	// EXIT TO THE MAIN MENU.
	if (inputManager->isESC())
	{
		inputManager->resetESC();
		inputManager->setCursorRelative(false);
		audioManager->stopMusic();
		audioManager->stopSounds();
		smManager->changeScene(smManager->MENU);
	}
}

void SceneGame::render()
{
	map->render();

	enterDoor->render();
	exitDoor->render();

	for (itLemmings = lemmings.begin(); itLemmings != lemmings.end(); itLemmings++)
		(*itLemmings)->render();

	actions->render();

	time->render();

	if (currState != -1)
		states[currState]->render();

	for (int i = 0; i < NUM_COUNTERS; i++)
		counters[i]->render();

	cursor->render();
}

void SceneGame::updateActions()
{
	const int action = actions->update();
	switch ((Actions::ActionEnum)action)
	{
	case -1:
		break;
	case Actions::REST_VEL_SPAWN:
		actions->decrementVelocitySkill();
		enterDoor->updateTimeToSpawn(actions->getNumberUsesSkill(1));
		break;
	case Actions::PLUS_VEL_SPAWN:
		actions->incrementVelocitySkill();
		enterDoor->updateTimeToSpawn(actions->getNumberUsesSkill(1));
		break;
	case Actions::PAUSE:
		gameStats->SetPause(!gameStats->GetPause());
		audioManager->pauseMusic();
		inputManager->resetClick();
		break;
	case Actions::MOAB:
		if (lemmings.size() > 0)
		{
			enterDoor->notMoreSpawns();
			// Explode all lemmings.
			for (itLemmings = lemmings.begin(); itLemmings != lemmings.end(); itLemmings++)
			{
				if (!(*itLemmings)->GetContExplotar())
					(*itLemmings)->SetContadorTemps(time->getTime());
			}
		}
		break;
	default:
		audioManager->playSound(idSounds[SelectSkill]);
		currAction = action;
		break;
	}
}

void SceneGame::updateDoors()
{
	// ENTER DOOR.
	enterDoor->update(time->getTimeMs());
	if (enterDoor->getIsSpawning())
	{
		Lemming* lemming = new Lemming();
		int posX = map->getPosX() + ((enterDoor->getPosX() / 2) - 3);
		int posY = map->getPosY() + enterDoor->getPosY();
		lemming->init(posX, posY, map->getPosX(), map->getPosY());
		lemmings.push_back(lemming);
		counters[0]->incrementNumber();
	}

	// EXIT DOOR.
	exitDoor->UpdateAnimation();
}

void SceneGame::updateLemmings()
{
	if (cursorChanged)
		cursorChanged = false;

	currState = -1;

	for (itLemmings = lemmings.begin(); itLemmings != lemmings.end(); itLemmings++)
	{
		const int x1 = ((*itLemmings)->getPosX() + (*itLemmings)->GetLimitX()) / map->GetSizeTile();
		const int y1 = (*itLemmings)->getPosY() / map->GetSizeTile();
		const int x2 = ((*itLemmings)->getPosX() + (*itLemmings)->getWidth()) / map->GetSizeTile();
		const int y2 = ((*itLemmings)->getPosY() + (*itLemmings)->getHeight()) / map->GetSizeTile();
		(*itLemmings)->update(map, x1, y1, x2, y2, time->getTime());

		// Si el Lemming ha completat l'animaci� de caminar cap a la porta, s'esborra i incrementa el n�mero de Lemmings salvats.
		if ((*itLemmings)->GetRescatat())
		{
			lemmingsSaved++;
			counters[0]->decrementNumber();
			const int LEMMINGS_SAVED = (((lemmingsSaved * 100) / numLemmings));
			counters[1]->setNumber(LEMMINGS_SAVED);
			lemmings.erase(itLemmings);
			if (lemmings.size() == 0)
			{
				if (((lemmingsSaved + lemmingsDead) >= numLemmings) || (enterDoor->getRemainingToSpawn() + lemmingsSaved + lemmingsDead) >= numLemmings)
					gameFinished = true;
				break;
			}
			itLemmings = lemmings.begin();
		}
		// Si surten del map o moren.
		else if ((map->getPosX() + x1 < map->getPosX() || map->getPosX() + x2 > map->getPosX() + map->GetWidthMap() || map->getPosY() + y2 > map->getPosY() + map->GetHeightMap()) || (*itLemmings)->GetMort())
		{
			lemmingsDead++;
			counters[0]->decrementNumber();
			lemmings.erase(itLemmings);
			if (lemmings.size() == 0)
			{
				if (((lemmingsSaved + lemmingsDead) >= numLemmings) || (enterDoor->getRemainingToSpawn() + lemmingsSaved + lemmingsDead) >= numLemmings)
					gameFinished = true;
				break;
			}
			itLemmings = lemmings.begin();
		}
		else
		{
			if ((*itLemmings)->CursorOnLemming())
			{
				if (!cursorChanged)
				{
					cursorChanged = true;
					currState = (*itLemmings)->GetEstat();
				}

				// Posar habilitats als Lemmings.
				if (inputManager->isClickLeft())
				{
					int numUsos = actions->getNumberUsesSkill(currAction);
					if ((*itLemmings)->SetSkill(numUsos, currAction, time->getTime()))
					{
						audioManager->playSound(idSounds[PutSkill]);
						actions->detractUseSkill(currAction);
					}
					inputManager->resetClick();
				}
			}

			// Si el Lemming surt per la porta.
			if ((*itLemmings)->GetEstat() != (*itLemmings)->RESCUED)
			{
				if (map->getPosX() + x1 > (exitDoor->getPosX() / map->GetSizeTile()) + 31 && map->getPosX() + x2 < ((exitDoor->getPosX() + exitDoor->getWidth()) / map->GetSizeTile()) + 22 &&
					map->getPosY() + y1 > (exitDoor->getPosY() / map->GetSizeTile()) + 5 && map->getPosY() + y2 < exitDoor->getPosY() + exitDoor->getHeight())
				{
					(*itLemmings)->SetRescatar();
				}
			}
		}
	}
}

void SceneGame::updateChangeCursor()
{
	if (cursorChanged && !cursor->isCursorChanged())
		cursor->changeCursor();
	else if (!cursorChanged && cursor->isCursorChanged())
		cursor->changeCursor();
}

void SceneGame::checkUnpaused()
{
	int action = actions->update();
	switch (action)
	{
	case Actions::PAUSE:
		gameStats->SetPause(!gameStats->GetPause());
		audioManager->resumeMusic();
		inputManager->resetClick();
		break;
	default:
		break;
	}
}