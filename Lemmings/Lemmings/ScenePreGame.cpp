#include "ScenePreGame.h"


ScenePreGame::ScenePreGame(){
	fileManager = FileManager::getInstanceFile();
	level = 1;
	nameLvl = numLemming = lemmingsToSave = releaseRate = timeLvl = rating = "";
	fons = new Element();
	smManager = SceneManager::getInstanceSM();
}


ScenePreGame::~ScenePreGame()
{
}


void ScenePreGame::init(){
	string nomFile = "Assets/Levels/PreGame/level";
	switch (level){
	case 1:
		nomFile += "1.txt";
		break;
	}

	const char* _nomFile = nomFile.c_str();
	fileManager->Read(_nomFile);

	nameLvl = fileManager->GetValueFromData("name");
	numLemming = fileManager->GetValueFromData("numberLemmings");
	lemmingsToSave = fileManager->GetValueFromData("lemmingsToSave");
	releaseRate = fileManager->GetValueFromData("releaseRate");
	timeLvl = fileManager->GetValueFromData("time");

	fons->init(0, 0, "Assets/Images/PreGame/_mision.png", 0, 0, 809, 446, 1, 1);

	digits.clear();
	// NAME LVL.
	int xDigit = 40;
	int yDigit = 100;
	for (int i = 0; i < nameLvl.length(); i++){
		digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, nameLvl[i]));
		if (nameLvl[i] != '_')
			xDigit += 20;
		else
			xDigit += 30;
	}
	// NUMBER LEMMINGS.
	xDigit = 60;
	yDigit = 225;
	for (int i = 0; i < numLemming.length(); i++){
		int num = (int)numLemming[i] - 48;
		digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, num));
		xDigit += 20;
	}
	// LEMMINGS TO SAVE.
	xDigit = 60;
	yDigit = 250;
	for (int i = 0; i < lemmingsToSave.length(); i++){
		int num = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, num));
		xDigit += 20;
	}
	// RELEASE RATE.
	xDigit = 80;
	yDigit = 275;
	for (int i = 0; i < releaseRate.length(); i++){
		int num = (int)releaseRate[i] - 48;
		digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, num));
		xDigit += 20;
	}
	// TIME.
	xDigit = 80;
	yDigit = 300;
	int num = (int)timeLvl[0] - 48;
	digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, num));
	// RATING.
	xDigit = 80;
	yDigit = 325;
	for (int i = 0; i < rating.length(); i++){
		digits.push_back(new ABCsAlphaNum(xDigit, yDigit, 1, 1, rating[i]));
		xDigit += 20;
	}
}

void ScenePreGame::update(){
	if (inputManager->CheckClick() || inputManager->CheckEnter())
		smManager->changeScene(smManager->GAME);
	else if (inputManager->CheckESC()){
		inputManager->ResetESC();
		smManager->changeScene(smManager->MENU);
	}
}

void ScenePreGame::render(){
	fons->render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++){
		(*itDigits)->Render();
	}
}


void ScenePreGame::SetRating(string rating){
	this->rating = rating;
}


void ScenePreGame::IncrementLevel(){
	level++;
}