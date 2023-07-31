#include "SceneGame.h"


SceneGame *SceneGame::gInstance = NULL;

SceneGame::SceneGame()
{
	map = nullptr;

	time = nullptr;

	actions = new Actions();

	numLemmings = lemmingsToSave = 0;
	remainingTime = releaseRate = "";

	lemmingsDead = lemmingsSaved = 0;

	gameFinished = false;

	exitDoor = new ElementGame();

	for (int i = 0; i < NUM_STATES; i++) {
		states[i] = new Word();
	}

	for (int i = 0; i < NUM_COUNTERS; i++) {
		counters[i] = new Counter();
	}

	cursorChanged = false;
	cursor = Cursor::getInstanceCursor();

	sPostGame = ScenePostGame::getInstanceScenePostGame();
	gameStats = GameStats::getInstanceGameStats();
	smManager = SceneManager::getInstanceSM();
}

SceneGame::~SceneGame() {
	delete actions;
	delete exitDoor;

	for (int i = 0; i < NUM_STATES; i++) {
		delete states[i];
	}
	for (int i = 0; i < NUM_COUNTERS; i++) {
		delete counters[i];
	}
}


SceneGame *SceneGame::getInstanceSceneGame()
{
	if (gInstance == NULL)
		gInstance = new SceneGame();

	return gInstance;
}


void SceneGame::initFromPreGame(Map* map, int numLemmings, int lemmingsToSave, string rateSpeed, string time)
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
		"MOVE", "FALL", "BREAK", "GLIDE", "CLIMB", "DIG", "PICK", "IMMOBILE", "STAIRS", "EXPLOSION",
		"DEAD", "DEAD_FALL", "OPEN_UMBRELLA", "NO_STAIRS", "END_CLIMB", "RESCUED", "EXPLODING"
	};
	for (int i = 0; i < NUM_STATES; i++) {
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

	for (auto lemming : lemmings) {
		delete lemming;
	}
	lemmings.clear();
	lemmings.resize(0);

	for (int i = 0; i < NUM_STATES; i++) {
		states[i]->clear();
	}
	if (currState != -1)
		currState = -1;

	for (int i = 0; i < NUM_COUNTERS; i++) {
		counters[i]->clear();
	}

	for (int i = 0; i <= (int)MaxNumSoundsEnum; i++) {
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
			playInitialSound();
		}
		updateDoors();
		updateLemmings();
		updateChangeCursor();

		if (time->getTimeOut())
		{
			audioManager->pauseMusic();
			gameFinished = true;
		}

		if (gameFinished)
		{
			finishGame();
		}

		if (inputManager->isPause())
		{
			setPauseGame(true);
			inputManager->resetPause();
		}
	}
	else if (gameStats->GetPause() && inputManager->isPause())
	{
		setPauseGame(false);
		inputManager->resetPause();
	}
	else if (gameStats->GetPause() && inputManager->isClickLeft())
		checkUnpaused();

	cursor->update();

	if (inputManager->isESC())
	{
		exitToTheMainMenu();
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
	const int ACTION = actions->update();
	switch ((Actions::ActionEnum)ACTION)
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
		setPauseGame(!gameStats->GetPause());
		inputManager->resetClick();
		break;
	case Actions::MOAB:
		if (lemmings.size() > 0)
		{
			enterDoor->notMoreSpawns();
			// Explode all lemmings.
			for (itLemmings = lemmings.begin(); itLemmings != lemmings.end(); itLemmings++)
			{
				if (!(*itLemmings)->GetIsGoingToExplode())
					(*itLemmings)->SetLevelTimeToExplode(time->getTime());
			}
		}
		break;
	default:
		audioManager->playSound(idSounds[SelectSkill]);
		currAction = ACTION;
		break;
	}
}

void SceneGame::playInitialSound() {
	if (time->getTimeMs() >= 30)
	{
		audioManager->playSound(idSounds[StartGame]);
		initialSound = true;
	}
}

void SceneGame::updateDoors()
{
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

		if ((*itLemmings)->GetIsRescued())
		{
			rescueLemming();
			if (lemmings.empty()) {
				checkActiveLemmings();
				break;
			}

			itLemmings = lemmings.begin();
		}
		else if (isOutOfMap(x1, x2, y2) || (*itLemmings)->GetIsDead())
		{
			killLemming();
			if (lemmings.empty())
			{
				checkActiveLemmings();
				break;
			}

			itLemmings = lemmings.begin();
		}
		else
		{
			if ((*itLemmings)->IsCursorOnLemming())
			{
				checkCursorChanged();
				putSkillIntoLemming();
			}

			if ((*itLemmings)->GetCurrState() != (*itLemmings)->RESCUED)
			{
				if (isLemmingInOutDoor(x1, x2, y1, y2))
				{
					(*itLemmings)->SetRescued();
				}
			}
		}
	}
}

void SceneGame::rescueLemming() {
	lemmingsSaved++;

	counters[0]->decrementNumber();
	const int LEMMINGS_SAVED = (((lemmingsSaved * 100) / numLemmings));
	counters[1]->setNumber(LEMMINGS_SAVED);

	lemmings.erase(itLemmings);
}

void SceneGame::checkActiveLemmings() {
	if (areThereAnyActiveLemming())
		gameFinished = true;
}

bool SceneGame::areThereAnyActiveLemming() {
	return (lemmingsSaved + lemmingsDead >= numLemmings)
		|| (enterDoor->getRemainingToSpawn() + lemmingsSaved + lemmingsDead >= numLemmings);
}

bool SceneGame::isOutOfMap(const int x1, const int x2, const int y2) {
	return (map->getPosX() + x1 < map->getPosX() || map->getPosX() + x2 > map->getPosX() + map->GetWidthMap()
		|| map->getPosY() + y2 > map->getPosY() + map->GetHeightMap());
}

void SceneGame::killLemming() {
	lemmingsDead++;
	counters[0]->decrementNumber();
	lemmings.erase(itLemmings);
}

void SceneGame::checkCursorChanged() {
	if (!cursorChanged) {
		cursorChanged = true;
		currState = (*itLemmings)->GetCurrState();
	}
}

void SceneGame::putSkillIntoLemming() {
	if (inputManager->isClickLeft())
	{
		const int NUMBERS_USES = actions->getNumberUsesSkill(currAction);
		if ((*itLemmings)->SetSkill(NUMBERS_USES, currAction, time->getTime()))
		{
			audioManager->playSound(idSounds[PutSkill]);
			actions->detractUseSkill(currAction);
		}
		inputManager->resetClick();
	}
}

bool SceneGame::isLemmingInOutDoor(const int x1, const int x2, const int y1, const int y2) {
	return map->getPosX() + x1 > (exitDoor->getPosX() / map->GetSizeTile()) + 31
		&& map->getPosX() + x2 < ((exitDoor->getPosX() + exitDoor->getWidth()) / map->GetSizeTile()) + 22
		&& map->getPosY() + y1 >(exitDoor->getPosY() / map->GetSizeTile()) + 5
		&& map->getPosY() + y2 < exitDoor->getPosY() + exitDoor->getHeight();
}

void SceneGame::updateChangeCursor()
{
	if (cursorChanged && !cursor->isCursorChanged())
		cursor->changeCursor();
	else if (!cursorChanged && cursor->isCursorChanged())
		cursor->changeCursor();
}

void SceneGame::finishGame() {
	const int LEMMINGS_TO_SAVE = (lemmingsToSave * numLemmings) / 100; // No percentage.
	if (lemmingsSaved >= LEMMINGS_TO_SAVE)
		gameStats->SetWin(true);

	const int LEMMINGS_SAVED = (lemmingsSaved * 100) / numLemmings; // With percentage.
	sPostGame->initFromGame(LEMMINGS_SAVED, lemmingsToSave);
	smManager->changeScene(smManager->POST_GAME);
	gameFinished = false;
}

void SceneGame::setPauseGame(const bool isPause){
	gameStats->SetPause(isPause);
	isPause ? audioManager->pauseMusic() : audioManager->resumeMusic();
}

void SceneGame::checkUnpaused()
{
	const int ACTION = actions->update();
	switch (ACTION)
	{
	case Actions::PAUSE:
		setPauseGame(!gameStats->GetPause());
		inputManager->resetClick();
		break;
	default:
		break;
	}
}

void SceneGame::exitToTheMainMenu() {
	inputManager->resetESC();
	inputManager->setCursorRelative(false);
	audioManager->stopMusic();
	audioManager->stopSounds();
	smManager->changeScene(smManager->MENU);
}