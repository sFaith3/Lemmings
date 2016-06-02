#include "ScenePostGame.h"


ScenePostGame* ScenePostGame::gInstance = NULL;

ScenePostGame::ScenePostGame(){
	fileManager = FileManager::getInstanceFile();

	winGame = false;
	lemmingsSaved = lemmingsToSave = "";

	fons = new Background();
	fons->SetScale(0.75, 0.75);//

	smManager = SceneManager::getInstanceSM();
}


ScenePostGame::~ScenePostGame(){

}


ScenePostGame* ScenePostGame::getInstanceScenePostGame(){
	if (gInstance == NULL)
		gInstance = new ScenePostGame();

	return gInstance;
}


void ScenePostGame::initFromGame(int lemmingsSaved, int lemmingsToSave){
	this->lemmingsSaved = to_string(lemmingsSaved);
	this->lemmingsToSave = to_string(lemmingsToSave);
}

void ScenePostGame::init(){
	inputManager->SetCursorRelative(true);

	int xDigit = 0, _xDigit = 0;
	int yDigit = 0;
	float scaleX = 0.65;
	int num = 0;

	// NUMBER LEMMINGS.
	xDigit = _xDigit = 475;
	yDigit = 50;
	for (int i = lemmingsSaved.length() - 1; i >= 0; i--){
		num = (int)lemmingsSaved[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, 1, num);
		xDigit -= 16;
	}
	// LEMMINGS TO SAVE.
	xDigit = _xDigit;
	yDigit += 16;
	for (int i = lemmingsToSave.length() - 1; i >= 0; i--){
		num = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, 1, num);
		xDigit -= 16;
	}
	//if (winGame){
		// CODE LEVEL
		fileManager->Read("Assets/Levels/levels.txt");
		string codeLvl = fileManager->GetValueFromData("code");
		xDigit = 370;
		yDigit = 235;
		scaleX = 0.55;
		for (int i = 0; i < codeLvl.length(); i++){
			digits.push_back(new ABCsAlphaNum());
			digits.back()->init(xDigit, yDigit, scaleX, 1, codeLvl[i]);
			xDigit += 20;
		}

		fons->init(0, 0, "Assets/Images/InfoScene/PostGame/win.png", 0, 0, 480, 340, 1, 1);
	//}
	//else
		//fons->init(0, 0, "Assets/Images/InfoScene/PostGame/lose.png", 0, 0, 480, 340, 1, 1);
}

void ScenePostGame::clear(){
	winGame = false;

	digits.clear();
	digits.resize(0);
}

void ScenePostGame::update(){
	if (inputManager->CheckClickLeft() || inputManager->CheckEnter()){
		inputManager->ResetClick();
		//Increment level.
		smManager->changeScene(smManager->PRE_GAME);
	}
	else if (inputManager->CheckClickRight()){
		inputManager->ResetClick();
		inputManager->SetCursorRelative(false);
		smManager->changeScene(smManager->MENU);
	}
	else if (inputManager->CheckESC()){
		inputManager->ResetESC();
		inputManager->SetCursorRelative(false);
		smManager->changeScene(smManager->MENU);
	}
}

void ScenePostGame::render(){
	fons->render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++){
		(*itDigits)->Render();
	}
}


void ScenePostGame::setWinGame(){
	winGame = true;
}