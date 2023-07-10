#include "SceneGame.h"

SceneGame *SceneGame::gInstance = NULL;

SceneGame::SceneGame()
{
	actions = new Actions();

	numLemmings = lemmingsToSave = 0;
	tempsRestant = releaseRate = "";

	lemmingsMorts = lemmingsSaved = 0;

	gameFinish = false;

	exitDoor = new ElementGame();

	for (int i = 0; i < 17; i++)
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

void SceneGame::initFromPreGame(Map *mapa, int numLemmings, int lemmingsToSave, string rateSpeed, string temps)
{
	this->mapa = mapa;
	this->numLemmings = numLemmings;
	this->lemmingsToSave = lemmingsToSave;
	releaseRate = rateSpeed;
	tempsRestant = temps + ":00";
}

void SceneGame::init()
{
	idMusic = audioManager->getMusicID("Assets/Art/Audios/Music/inGame.wav");

	lemmingsMorts = lemmingsSaved = 0;

	gameFinish = false;

	mapa->SetPositionTiles(-475, 22);
	mapa->SetScaleTiles(1, 1);

	currAction = actions->init(1, 1, releaseRate, "10", "10", "10", "10", "10", "10", "10", "10");

	// Inicialitzaci� de les portes del joc. Punt de respawn i de sortida dels lemmings.
	enterDoor = new DoorEnter(110, 80, 20, numLemmings);
	exitDoor->init(338, 200, "Assets/Art/Images/Doors/exit.png", false, 0, 0, 42, 31, 1, 1, 92, 31, 49, 2, 12);

	int x, y;
	x = 20;
	y = 260;
	string nomStates[] = {
		"MOVE", "FALL", "BREAK", "GLIDE", "CLIMB", "DIG", "PICK", "STOP", "STAIR", "EXPLOSION",
		"DEAD", "DEADFALL", "OPENUMBRELLA", "NOSTAIR", "ENDCLIMB", "RESCUED", "EXPLODING"};
	for (int i = 0; i < 17; i++)
	{
		states[i]->init(x, y, 1, 1, 15, nomStates[i]);
	}
	currState = -1;

	counters[0]->init(155, 258, "Assets/Art/Images/HUD/Counters/Out.png", 35, 19, 1, 1, 42, 15, false);
	counters[1]->init(253, 258, "Assets/Art/Images/HUD/Counters/In.png", 25, 19, 1, 1, 33, 15, true);

	idSounds[0] = audioManager->getSoundID("Assets/Art/Audios/Sounds/startGame.wav");
	idSounds[1] = audioManager->getSoundID("Assets/Art/Audios/Sounds/selectSkill.wav");
	idSounds[2] = audioManager->getSoundID("Assets/Art/Audios/Sounds/putSkill.wav");
	initialSound = false;

	temps = new Timer(355, 258, tempsRestant);
	temps->start();

	audioManager->playMusic(idMusic, -1);
}

void SceneGame::clear()
{
	idMusic = -1;

	if (gameStats->GetPause())
		gameStats->SetPause(false);

	delete mapa;

	delete temps;

	currAction = -1;

	delete enterDoor;

	lemmings.clear();
	lemmings.resize(0);

	for (int i = 0; i < 17; i++)
	{
		states[i]->clear();
	}
	if (currState != -1)
		currState = -1;

	counters[0]->clear();
	counters[1]->clear();

	for (int i = 0; i < 3; i++)
	{
		idSounds[i] = -1;
	}
}

void SceneGame::update()
{
	if (!gameStats->GetPause())
	{
		updateActions();
		temps->update();
		if (!initialSound)
		{
			if (temps->getTimeMs() >= 30)
			{
				audioManager->playSound(idSounds[StartGame]);
				initialSound = true;
			}
		}
		updateLemmings();
		updateDoors();
		updateChangeCursor();

		if (temps->getTempsOut())
		{
			audioManager->pauseMusic();
			gameFinish = true;
		}

		if (gameFinish)
		{
			int _lemmingsToSave = (lemmingsToSave * numLemmings) / 100; // Sense percentatge.
			if (lemmingsSaved >= _lemmingsToSave)
				gameStats->SetWin(true);

			int _lemmingsSaved = (lemmingsSaved * 100) / numLemmings; // Amb percentatge.
			sPostGame->initFromGame(_lemmingsSaved, lemmingsToSave);
			smManager->changeScene(smManager->POST_GAME);
			gameFinish = false;
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
	mapa->render();

	enterDoor->render();
	exitDoor->render();

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
		(*itLem)->render();

	actions->render();

	temps->render();

	if (currState != -1)
		states[currState]->render();

	for (int i = 0; i < 2; i++)
		counters[i]->render();

	cursor->render();
}

void SceneGame::updateActions()
{
	int action = actions->update();
	switch (action)
	{
	case -1:
		break;
	case 0: // REST_VEL_SPAWN
		actions->decrementVelocitySkill();
		enterDoor->updateTimeToSpawn(actions->getNumberUsesSkill(1));
		break;
	case 1: // PLUS_VEL_SPAWN
		actions->incrementVelocitySkill();
		enterDoor->updateTimeToSpawn(actions->getNumberUsesSkill(1));
		break;
	case 10: // PAUSAR JOC.
		gameStats->SetPause(!gameStats->GetPause());
		audioManager->pauseMusic();
		inputManager->resetClick();
		break;
	case 11: // MOAB.
		if (lemmings.size() > 0)
		{
			enterDoor->notMoreSpawns();
			// Explotar tots els Lemmings.
			for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
			{
				if (!(*itLem)->GetContExplotar())
					(*itLem)->SetContadorTemps(temps->getTime());
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
	enterDoor->update(temps->getTimeMs());
	if (enterDoor->getIsSpawning())
	{
		Lemming *lemming = new Lemming();
		int posX = mapa->getPosX() + ((enterDoor->getPosX() / 2) - 3);
		int posY = mapa->getPosY() + enterDoor->getPosY();
		lemming->init(posX, posY, mapa->getPosX(), mapa->getPosY());
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

	for (itLem = lemmings.begin(); itLem != lemmings.end(); itLem++)
	{
		int x1 = ((*itLem)->getPosX() + (*itLem)->GetLimitX()) / mapa->GetSizeTile();
		int y1 = (*itLem)->getPosY() / mapa->GetSizeTile();
		int x2 = ((*itLem)->getPosX() + (*itLem)->getWidth()) / mapa->GetSizeTile();
		int y2 = ((*itLem)->getPosY() + (*itLem)->getHeight()) / mapa->GetSizeTile();
		(*itLem)->update(mapa, x1, y1, x2, y2, temps->getTime());

		// Si el Lemming ha completat l'animaci� de caminar cap a la porta, s'esborra i incrementa el n�mero de Lemmings salvats.
		if ((*itLem)->GetRescatat())
		{
			lemmingsSaved++;
			counters[0]->decrementNumber();
			int _lemSaved = (((lemmingsSaved * 100) / numLemmings));
			counters[1]->setNumber(_lemSaved);
			lemmings.erase(itLem);
			if (lemmings.size() == 0)
			{
				if (((lemmingsSaved + lemmingsMorts) >= numLemmings) || (enterDoor->getRemainingToSpawn() + lemmingsSaved + lemmingsMorts) >= numLemmings)
					gameFinish = true;
				break;
			}
			itLem = lemmings.begin();
		}
		// Si surten del mapa o moren.
		else if ((mapa->getPosX() + x1 < mapa->getPosX() || mapa->getPosX() + x2 > mapa->getPosX() + mapa->GetWidthMap() || mapa->getPosY() + y2 > mapa->getPosY() + mapa->GetHeightMap()) || (*itLem)->GetMort())
		{
			lemmingsMorts++;
			counters[0]->decrementNumber();
			lemmings.erase(itLem);
			if (lemmings.size() == 0)
			{
				if (((lemmingsSaved + lemmingsMorts) >= numLemmings) || (enterDoor->getRemainingToSpawn() + lemmingsSaved + lemmingsMorts) >= numLemmings)
					gameFinish = true;
				break;
			}
			itLem = lemmings.begin();
		}
		else
		{
			if ((*itLem)->CursorOnLemming())
			{
				if (!cursorChanged)
				{
					cursorChanged = true;
					currState = (*itLem)->GetEstat();
				}

				// Posar habilitats als Lemmings.
				if (inputManager->isClickLeft())
				{
					int numUsos = actions->getNumberUsesSkill(currAction);
					if ((*itLem)->SetSkill(numUsos, currAction, temps->getTime()))
					{
						audioManager->playSound(idSounds[PutSkill]);
						actions->detractUseSkill(currAction);
					}
					inputManager->resetClick();
				}
			}

			// Si el Lemming surt per la porta.
			if ((*itLem)->GetEstat() != (*itLem)->RESCUED)
			{
				if (mapa->getPosX() + x1 > (exitDoor->getPosX() / mapa->GetSizeTile()) + 31 && mapa->getPosX() + x2 < ((exitDoor->getPosX() + exitDoor->getWidth()) / mapa->GetSizeTile()) + 22 &&
					mapa->getPosY() + y1 > (exitDoor->getPosY() / mapa->GetSizeTile()) + 5 && mapa->getPosY() + y2 < exitDoor->getPosY() + exitDoor->getHeight())
				{
					(*itLem)->SetRescatar();
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
	case 10: // PAUSAR JOC.
		gameStats->SetPause(!gameStats->GetPause());
		audioManager->resumeMusic();
		inputManager->resetClick();
		break;
	default:
		break;
	}
}