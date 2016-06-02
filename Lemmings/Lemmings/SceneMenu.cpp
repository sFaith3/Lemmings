#include "SceneMenu.h"


SceneMenu* SceneMenu::gInstance = NULL;

SceneMenu::SceneMenu(){
	sGame = SceneGame::getInstanceSceneGame();

	smManager = SceneManager::getInstanceSM();

	float scaleX = 0.65;
	float scaleY = 0.8;
	fons = new Background();
	fons->init(0, 0, "Assets/Images/menu.png", 0, 0, 809, 446, scaleX, scaleY);

	soJoc = false;

	Button button;
	int wButton = 132 * scaleX;
	int hButton = 48 * scaleY;
	button.init(PLAYER, 98, 188, wButton, hButton, scaleX, scaleY, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(NEW_LEVEL, 260, 188, wButton, hButton, scaleX, scaleY, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(MUTE_SOUND, 422, 188, wButton, hButton, scaleX, scaleY, 0, 0, NULL, NULL);
	buttons.push_back(button); // TECLA.
	/*button.init(FUN, 584, 188, wButton, hButton, scaleX, scaleY, 0, 0, NULL, NULL);
	buttons.push_back(button);*/ // TECLES AMUNT I AVALL.*/
	button.init(EXIT, 260, 285, wButton, hButton - 1, scaleX, scaleY, 0, 0, NULL, NULL);
	buttons.push_back(button);

	idMusic = audioManager->getMusicID("Assets/Audios/Music/intro_00.wav");
}


SceneMenu::~SceneMenu(){
}


SceneMenu* SceneMenu::getInstanceSceneMenu(){
	if (gInstance == NULL)
		gInstance = new SceneMenu();

	return gInstance;
}


void SceneMenu::init(){
	audioManager->playMusic(idMusic, -1);
}


void SceneMenu::update(){
	for (itBut = buttons.begin(); itBut != buttons.end(); itBut++){
		if (itBut->update()){
			switch (itBut->GetId()){
			case PLAYER:
				inputManager->ResetClick();
				audioManager->pauseMusic();
				sGame->setMuteigSo(soJoc);
				smManager->changeScene(smManager->PRE_GAME);
				return;
			case NEW_LEVEL:

				break;
			case MUTE_SOUND:
				soJoc = !soJoc;
				break;
			case EXIT:
				inputManager->SetNumber(EXIT);
				break;
			}
		}
	}
	inputManager->ResetClick();

	switch (inputManager->CheckNumber()){
	case PLAYER:
		inputManager->ResetNumber();
		audioManager->pauseMusic();
		sGame->setMuteigSo(soJoc);
		smManager->changeScene(smManager->PRE_GAME);
		break;
	case NEW_LEVEL:

		break;
	case MUTE_SOUND:
		soJoc = !soJoc;
		inputManager->ResetNumber();
		break;
	}
}



void SceneMenu::render(){
	fons->render();
}