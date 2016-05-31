#include "ScenePreGame.h"


ScenePreGame::ScenePreGame(){
	fileManager = FileManager::getInstanceFile();

	level = 1;
	nameLvl = numLemmings = lemmingsToSave = releaseRate = timeLvl = rating = "";

	fons = new Background();
	fons->init(0, 0, "Assets/Images/PreGame/_mision.png", 0, 0, 809, 446, 1, 1);
	fons->SetScale(0.75, 0.75); //

	digits.clear();
	string nomFile = "Assets/Levels/PreGame/level";
	string rutaMapa = "Assets/Levels/";
	string rutaTilesets = "Assets/Levels/";
	switch (level){
	case 1:
		nomFile += "1.txt";
		rutaMapa += "lvl01/lvl01.tmx";
		rutaTilesets += "lvl01/";
		break;
	}
	const char* _nomFile = nomFile.c_str();
	const char* _rutaMapa = rutaMapa.c_str();
	const char* _rutaTilesets = rutaTilesets.c_str();

	fileManager->Read(_nomFile);

	nameLvl = fileManager->GetValueFromData("name");
	numLemmings = fileManager->GetValueFromData("numberLemmings");
	lemmingsToSave = fileManager->GetValueFromData("lemmingsToSave");
	timeLvl = fileManager->GetValueFromData("time");
	releaseRate = fileManager->GetValueFromData("releaseRate");

	int x = (fons->GetPosX() + fons->GetWidth()) / 2;
	int y = 20;
	int scaleX = 0.5;
	int scaleY = 0.5;
	mapa = new Map();
	mapa->init(40, 5, true, _rutaMapa, "colisiones", 3, _rutaTilesets, false, 1, 0, 0, NULL, NULL);
	mapa->SetPoisition(x, y);
	mapa->SetScale(scaleX, scaleY);

	// NAME LVL.
	int xDigit = 40;
	int yDigit = 100;
	for (int i = 0; i < nameLvl.length(); i++){
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, nameLvl[i]);
		if (nameLvl[i] != '_')
			xDigit += 20;
		else
			xDigit += 30;
	}
	// NUMBER LEMMINGS.
	int numLem = 0;
	xDigit = 60;
	yDigit = 225;
	for (int i = 0; i < numLemmings.length(); i++){
		if (i == 0)
			numLem += ((int)numLemmings[i] - 48) * 10;
		else
			numLem += (int)numLemmings[i] - 48;

		int num = (int)numLemmings[i] - 48;
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
	// TIME.
	xDigit = 80;
	yDigit = 275;
	int num = (int)timeLvl[0] - 48;
	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, 1, 1, num);
	// RELEASE RATE.
	xDigit = 80;
	yDigit = 300;
	for (int i = 0; i < releaseRate.length(); i++){
		int num = (int)releaseRate[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, num);
		xDigit += 20;
	}
	// RATING.
	xDigit = 80;
	yDigit = 325;
	for (int i = 0; i < rating.length(); i++){
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, 1, 1, rating[i]);
		xDigit += 20;
	}
	sGame = SceneGame::getInstanceSceneGame();
	sGame->initFromPreGame(mapa, numLem, lemToSave, timeLvl, releaseRate);

	smManager = SceneManager::getInstanceSM();
}


ScenePreGame::~ScenePreGame(){

}


void ScenePreGame::init(){
	inputManager->SetCursorRelative(true);
}

void ScenePreGame::update(){
	if (inputManager->CheckClick() || inputManager->CheckEnter())
		smManager->changeScene(smManager->GAME);
	else if (inputManager->CheckESC()){
		inputManager->ResetESC();
		inputManager->SetCursorRelative(false);
		smManager->changeScene(smManager->MENU);
	}
}

void ScenePreGame::render(){
	fons->render();

	mapa->render();

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