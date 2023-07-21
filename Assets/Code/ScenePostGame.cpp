#include "ScenePostGame.h"


ScenePostGame* ScenePostGame::gInstance = NULL;

ScenePostGame::ScenePostGame(){
	lemmingsSaved = lemmingsToSave = "";

	background = new Background();

	gameStats = GameStats::getInstanceGameStats();
	fileManager = FileManager::getInstanceFile();
	sceneManager = SceneManager::getInstanceSM();
}

ScenePostGame::~ScenePostGame(){
}


ScenePostGame* ScenePostGame::getInstanceScenePostGame(){
	if (gInstance == NULL)
		gInstance = new ScenePostGame();

	return gInstance;
}


void ScenePostGame::initFromGame(const int lemmingsSaved, const int lemmingsToSave){
	this->lemmingsSaved = to_string(lemmingsSaved);
	this->lemmingsToSave = to_string(lemmingsToSave);
}

void ScenePostGame::init() {
	inputManager->setCursorRelative(true);

	int xDigit = 0, _xDigit = 0;
	int yDigit = 0;
	float scaleX = 0.65f;
	int alphaNum = 0;

	initDigitsNumberLemmingsSaved(xDigit, _xDigit, yDigit, scaleX, alphaNum);
	initDigitsNumberLemmingsToSave(xDigit, _xDigit, yDigit, scaleX, alphaNum);
	
	if (gameStats->GetWin()) {
		initDigitsNumberLevel(xDigit, yDigit, scaleX);
		initDigitsCodeLevel(xDigit, yDigit, scaleX);

		background->init(0, 0, "Assets/Art/Images/InfoScene/PostGame/win.png", false, 0, 0, 480, 340, 1, 1);
	}
	else
		background->init(0, 0, "Assets/Art/Images/InfoScene/PostGame/lose.png", false, 0, 0, 480, 340, 1, 1);
}

void ScenePostGame::initDigitsNumberLemmingsSaved(int& xDigit, int& _xDigit, int& yDigit, float scaleX, int alphaNum) {
	xDigit = _xDigit = 475;
	yDigit = 51;
	for (int i = lemmingsSaved.length() - 1; i >= 0; i--) {
		alphaNum = (int)lemmingsSaved[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, 1, alphaNum);
		xDigit -= 16;
	}
}

void ScenePostGame::initDigitsNumberLemmingsToSave(int& xDigit, int& _xDigit, int& yDigit, float scaleX, int alphaNum) {
	xDigit = _xDigit;
	yDigit += 16;
	for (int i = lemmingsToSave.length() - 1; i >= 0; i--) {
		alphaNum = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, 1, alphaNum);
		xDigit -= 16;
	}
}

void ScenePostGame::initDigitsNumberLevel(int& xDigit, int& yDigit, float scaleX) {
	xDigit = 610;
	yDigit = 217;
	int numNivell = gameStats->GetLevel();
	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, scaleX, 1, numNivell);
}

void ScenePostGame::initDigitsCodeLevel(int& xDigit, int& yDigit, float scaleX) {
	fileManager->Read("Assets/Levels/levels.txt", gameStats->GetLevel());
	string codeLvl = fileManager->GetValueFromData("code");
	xDigit = 367;
	yDigit = 235;
	scaleX = 0.55f;
	for (int i = 0; i < codeLvl.length(); i++) {
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, 1, (char)codeLvl[i]);
		xDigit += 20;
	}
}

void ScenePostGame::clear(){
	gameStats->SetWin(false);

	digits.clear();
	digits.resize(0);
}

void ScenePostGame::update(){
	// Next level or play again.
	if (inputManager->isClickLeft()){
		inputManager->resetClick();
		if (gameStats->GetWin())
			gameStats->IncrementLevel();
		sceneManager->changeScene(sceneManager->PRE_GAME);
	}
	// Back to main menu.
	else if (inputManager->isClickRight()) {
		inputManager->resetClick();
		inputManager->setCursorRelative(false);
		sceneManager->changeScene(sceneManager->MENU);
	}
	// Back to main menu.
	else if (inputManager->isESC()){
		inputManager->resetESC();
		inputManager->setCursorRelative(false);
		sceneManager->changeScene(sceneManager->MENU);
	}
}

void ScenePostGame::render(){
	background->render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++){
		(*itDigits)->render();
	}
}