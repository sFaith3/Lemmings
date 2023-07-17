#include "ScenePreGame.h"


ScenePreGame *ScenePreGame::gInstance = NULL;

ScenePreGame::ScenePreGame()
{
	nameLvl = numLemmings = lemmingsToSave = releaseRate = timeLvl = rating = "";

	background = new Background();
	background->init(0, 0, "Assets/Art/Images/InfoScene/PreGame/missionInfo.png", false, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);

	map = nullptr;

	fileManager = FileManager::getInstanceFile();
	sGame = SceneGame::getInstanceSceneGame();
	gameStats = GameStats::getInstanceGameStats();
	smManager = SceneManager::getInstanceSM();
}

ScenePreGame::~ScenePreGame()
{
}


ScenePreGame *ScenePreGame::getInstanceScenePreGame()
{
	if (gInstance == NULL)
		gInstance = new ScenePreGame();

	return gInstance;
}


void ScenePreGame::init()
{
	const int CURRENT_LEVEL = gameStats->GetLevel();

	if (isLastMap(CURRENT_LEVEL))
	{
		cout << "More levels comming soon!\n";
		gameStats->ResetLevel();
		inputManager->setCursorRelative(false);
		smManager->changeScene(smManager->MENU);

		return;
	}

	loadLevelInfo(CURRENT_LEVEL);
}

void ScenePreGame::clear()
{
	digits.clear();
	digits.resize(0);
}

void ScenePreGame::update()
{
	if (isNextScene())
	{
		inputManager->resetClick();
		smManager->changeScene(smManager->GAME);
	}
	else if (isPreviousScene())
	{
		inputManager->resetESC();
		inputManager->setCursorRelative(false);
		smManager->changeScene(smManager->MENU);
	}
}

void ScenePreGame::render()
{
	background->render();

	map->render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++)
	{
		(*itDigits)->render();
	}
}


bool ScenePreGame::isLastMap(const int LEVEL) {
	return LEVEL > NUM_MAPS;
}

void ScenePreGame::loadLevelInfo(const int LEVEL) {
	const char* PATH_LEVEL = "Assets/Levels/levels.txt";
	fileManager->Read(PATH_LEVEL, LEVEL);

	int numLem, lemToSave;
	numLem = lemToSave = 0;
	initLevelInfo(LEVEL, numLem, lemToSave);

	string pathMap, pathTilesets;
	pathMap = pathTilesets = "";
	getPathsToInitMap(pathMap, pathTilesets, LEVEL);
	const char* PATH_MAP = pathMap.c_str();
	const char* PATH_TILESETS = pathTilesets.c_str();
	initMap(PATH_MAP, PATH_TILESETS);

	sGame->initFromPreGame(map, numLem, lemToSave, releaseRate, timeLvl);
}

void ScenePreGame::initLevelInfo(const int LEVEL, int& numLem, int& lemToSave) {
	nameLvl = fileManager->GetValueFromData("name");
	numLemmings = fileManager->GetValueFromData("numberLemmings");
	lemmingsToSave = fileManager->GetValueFromData("lemmingsToSave");
	releaseRate = fileManager->GetValueFromData("releaseRate");
	timeLvl = fileManager->GetValueFromData("time");

	initLevelInfoForRender(LEVEL, numLem, lemToSave);
}

void ScenePreGame::initLevelInfoForRender(const int LEVEL, int& numLem, int& lemToSave) {
	int xDigit = 95;
	int yDigit = 83;
	float scaleX = 0.75f;
	float scaleY = 1.f;
	int num = 0;

	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, scaleX, scaleY, LEVEL);

	// Level name.
	xDigit += 42;
	scaleX = 0.75;
	scaleY = 1;
	for (int i = 0; i < nameLvl.length(); i++)
	{
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, (char)nameLvl[i]);
		if (nameLvl[i] != '_')
			xDigit += 19;
		else
			xDigit += 15;
	}

	// Lemmings number.
	xDigit = 465;
	yDigit = 127;
	for (int i = 0; i < numLemmings.length(); i++)
	{
		numLem *= 10;
		numLem += (int)numLemmings[i] - 48;

		num = (int)numLemmings[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 18;
	}

	// Lemming to save.
	xDigit = 158;
	yDigit += 30;
	for (int i = 0; i < lemmingsToSave.length(); i++)
	{
		lemToSave *= 10;
		lemToSave += (int)lemmingsToSave[i] - 48;

		num = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 18;
	}

	// Release rate.
	xDigit = 370;
	yDigit += 30;
	for (int i = 0; i < releaseRate.length(); i++)
	{
		num = (int)releaseRate[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 20;
	}

	// Time.
	xDigit = 240;
	yDigit += 30;
	num = (int)timeLvl[0] - 48;
	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);

	// Rating.
	xDigit = 80;
	yDigit += 30;
	for (int i = 0; i < rating.length(); i++)
	{
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, rating[i]);
		xDigit += 20;
	}
}

void ScenePreGame::getPathsToInitMap(string& pathMap, string& pathTilesets, const int LEVEL) {
	pathMap = pathTilesets = "Assets/Levels/";
	const string STR_LEVEL = to_string(LEVEL);

	pathMap += "lvl0" + STR_LEVEL + "/lvl0" + STR_LEVEL + ".tmx";
	pathTilesets += "lvl0" + STR_LEVEL + "/";
}

void ScenePreGame::initMap(const char* PATH_MAP, const char* PATH_TILESETS) {
	float scaleX, scaleY;
	scaleX = scaleY = 0.33666f;

	map = new Map();
	map->init(40, 2, true, PATH_MAP, "colisiones", 3, PATH_TILESETS, false, 1, 0, 0, NULL, NULL); // S'inicien les posicions X-Y que es volen a SceneGame.
	map->SetPositionTiles(475, -22);
	map->SetScaleTiles(scaleX, scaleY);
}

bool ScenePreGame::isNextScene() {
	return inputManager->isClickLeft() || inputManager->isClickRight();
}

bool ScenePreGame::isPreviousScene() {
	return inputManager->isESC();
}