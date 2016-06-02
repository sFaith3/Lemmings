#include "ScenePreGame.h"


ScenePreGame::ScenePreGame(){
	fileManager = FileManager::getInstanceFile();

	level = 1;
	nameLvl = numLemmings = lemmingsToSave = releaseRate = timeLvl = rating = "";

	fons = new Background();
	fons->init(0, 0, "Assets/Images/InfoScene/PreGame/infoMision.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);

	sGame = SceneGame::getInstanceSceneGame();

	smManager = SceneManager::getInstanceSM();
}


ScenePreGame::~ScenePreGame(){

}


void ScenePreGame::init(){
	inputManager->SetCursorRelative(true);

	string nomFile = "Assets/Levels/levels.txt";
	string rutaMapa = "Assets/Levels/";
	string rutaTilesets = "Assets/Levels/";
	switch (level){
	case 1:
		rutaMapa += "lvl01/lvl01.tmx";
		rutaTilesets += "lvl01/";
		break;
	case 2:
		rutaMapa += "lvl01/lvl01.tmx";
		rutaTilesets += "lvl01/";
		break;
	}
	const char* _nomFile = nomFile.c_str();
	const char* _rutaMapa = rutaMapa.c_str();
	const char* _rutaTilesets = rutaTilesets.c_str();

	fileManager->Read(_nomFile, 2);

	nameLvl = fileManager->GetValueFromData("name");
	numLemmings = fileManager->GetValueFromData("numberLemmings");
	lemmingsToSave = fileManager->GetValueFromData("lemmingsToSave");
	releaseRate = fileManager->GetValueFromData("releaseRate");
	timeLvl = fileManager->GetValueFromData("time");

	int xDigit = 95;
	int yDigit = 83;
	float scaleX, scaleY;
	scaleX = 0.75;
	scaleY = 1;
	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, scaleX, scaleY, level);
	// NAME LVL.
	xDigit += 55;
	scaleX = 0.75;
	scaleY = 1;
	for (int i = 0; i < nameLvl.length(); i++){
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, nameLvl[i]);
		if (nameLvl[i] != '_')
			xDigit += 20;
		else
			xDigit += 30;
	}
	// NUMBER LEMMINGS.
	int numLem = 0;
	xDigit = 465;
	yDigit = 127;
	for (int i = 0; i < numLemmings.length(); i++){
		if (i == 0)
			numLem += ((int)numLemmings[i] - 48) * 10;
		else
			numLem += (int)numLemmings[i] - 48;

		int num = (int)numLemmings[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 18;
	}
	// LEMMINGS TO SAVE.
	int lemToSave = 0;
	xDigit = 158;
	yDigit += 30;
	for (int i = 0; i < lemmingsToSave.length(); i++){
		if (i == 0)
			lemToSave += ((int)lemmingsToSave[i] - 48) * 10;
		else
			lemToSave += (int)lemmingsToSave[i] - 48;

		int num = (int)lemmingsToSave[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 18;
	}
	// RELEASE RATE.
	xDigit = 370;
	yDigit += 30;
	int num = 0;
	for (int i = 0; i < releaseRate.length(); i++){
		if (i == 0)
			lemToSave += ((int)releaseRate[i] - 48) * 10;
		else
			lemToSave += (int)releaseRate[i] - 48;
		int num = (int)releaseRate[i] - 48;
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
		xDigit += 20;
	}
	// TIME.
	xDigit = 240;
	yDigit += 30;
	num = (int)timeLvl[0] - 48;
	digits.push_back(new ABCsAlphaNum());
	digits.back()->init(xDigit, yDigit, scaleX, scaleY, num);
	// RATING.
	xDigit = 80;
	yDigit += 30;
	for (int i = 0; i < rating.length(); i++){
		digits.push_back(new ABCsAlphaNum());
		digits.back()->init(xDigit, yDigit, scaleX, scaleY, rating[i]);
		xDigit += 20;
	}

	scaleX = scaleY = 0.33666;
	mapa = new Map();
	mapa->init(40, 2, true, _rutaMapa, "colisiones", 3, _rutaTilesets, false, 1, 0, 0, NULL, NULL); // Iniciar les posiciones que es volen a SceneGame.

	sGame->initFromPreGame(mapa, numLem, lemToSave, releaseRate, timeLvl);

	mapa->SetPositionTiles(475, -22);
	mapa->SetScaleTiles(scaleX, scaleY);
}

void ScenePreGame::clear(){
	digits.clear();
	digits.resize(0);
}

void ScenePreGame::update(){
	if (inputManager->CheckClickLeft() || inputManager->CheckClickRight()){
		inputManager->ResetClick();
		smManager->changeScene(smManager->GAME);
	}
	/*else if (inputManager->CheckEnter()){
		smManager->changeScene(smManager->GAME);
	}*/
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