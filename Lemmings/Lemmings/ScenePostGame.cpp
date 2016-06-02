#include "ScenePostGame.h"


ScenePostGame::ScenePostGame(){
	fileManager = FileManager::getInstanceFile();

	lemmingsSaved = lemmingsToSave = codeLvl = "";

	fons = new Background();
	fons->init(0, 0, "Assets/Images/InfoScene/PostGame/win.png", 0, 0, 809, 446, 1, 1);
	fons->SetScale(0.75, 0.75); //

	sGame = SceneGame::getInstanceSceneGame();

	smManager = SceneManager::getInstanceSM();
}


ScenePostGame::~ScenePostGame(){

}


void ScenePostGame::init(){
	inputManager->SetCursorRelative(true);

	string nomFile = "Assets/Levels/PreGame/level";
	switch (level){
	case 1:
		nomFile += "1.txt";
		break;
	default:
		nomFile += "1.txt";
		break;
	}
	const char* _nomFile = nomFile.c_str();

	fileManager->Read(_nomFile);

	lemmingsToSave = fileManager->GetValueFromData("lemmingsToSave");
	codeLvl = fileManager->GetValueFromData("code");

	int xDigit = 60;
	int yDigit = 225;
	int num = 0;

	// NUMBER LEMMINGS.
	int lemSaved = 0;
	for (int i = 0; i < lemmingsSaved.length(); i++){
		if (i == 0)
			lemSaved += ((int)lemmingsSaved[i] - 48) * 10;
		else
			lemSaved += (int)lemmingsSaved[i] - 48;

		num = (int)lemmingsSaved[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, num);
		xDigit += 20;
	}
	// LEMMINGS TO SAVE.
	int lemToSave = 0;
	xDigit = 60;
	yDigit = 250;
	for (int i = 0; i < lemmingsToSave.length(); i++){
		if (i == 0)
			lemToSave += ((int)lemmingsToSave[i] - 48) * 10;
		else
			lemToSave += (int)lemmingsToSave[i] - 48;

		int num = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, num);
		xDigit += 20;
	}
	// RATING.
	xDigit = 80;
	yDigit = 325;
	for (int i = 0; i < codeLvl.length(); i++){
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, codeLvl[i]);
		xDigit += 20;
	}
}

void ScenePostGame::clear(){
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