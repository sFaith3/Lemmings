#include "SceneMenu.h"


SceneMenu::SceneMenu(){
	smManager = SceneManager::getInstanceSM();

	fons = new Background();
	fons->init(0, 0, "Assets/Images/menu.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);

	Button button;
	int wButton = 132;
	int hButton = 48;
	button.init(PLAYER, 98, 188, wButton, hButton, 1, 1, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(NEW_LEVEL, 260, 188, wButton, hButton, 1, 1, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(AUDIO, 422, 188, wButton, hButton, 1, 1, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(FUN, 584, 188, wButton, hButton, 1, 1, 0, 0, NULL, NULL);
	buttons.push_back(button);
	button.init(EXIT, 260, 285, wButton, hButton - 1, 1, 1, 0, 0, NULL, NULL);
	buttons.push_back(button);
	//button.init(CONTROLLERS, 422, 285, wButton, hButton - 1, 1, 1, 0, 0, NULL, NULL);
	//buttons.push_back(button);

	int _idMusic = audioManager->getAudioID("Assets/Audios/Music/intro_00.wav");
	if (_idMusic != -1)
		idMusic = _idMusic;
	else
		idMusic = NULL;
}


SceneMenu::~SceneMenu(){
}


void SceneMenu::init(){
	audioManager->playSound(idMusic, -1);
}


void SceneMenu::update(){
	for (itBut = buttons.begin(); itBut != buttons.end(); itBut++){
		if ((itBut)->update()){
			switch ((itBut)->GetId()){
			case PLAYER:
				audioManager->pauseSound();
				smManager->changeScene(smManager->GAME);
				break;
			case NEW_LEVEL:

				break;
			case AUDIO:

				break;
			case FUN:

				break;
			//case CONTROLLERS:

				//break;
			}
		}
	}

	switch (inputManager->CheckNumber()){
	case PLAYER:
		audioManager->pauseSound();
		smManager->changeScene(smManager->GAME);
		break;
	case NEW_LEVEL:
		
		break;
	case AUDIO:
		
		break;
	case FUN:
		
		break;
	//case CONTROLLERS:

		//break
	}
}


void SceneMenu::render(){
	fons->render();

	for (itBut = buttons.begin(); itBut != buttons.end(); itBut++){
		(itBut)->render();
	}
}