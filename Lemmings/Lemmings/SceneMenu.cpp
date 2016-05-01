#include "SceneMenu.h"


SceneMenu::SceneMenu(){
	smManager = SceneManager::getInstanceSM();
}


SceneMenu::~SceneMenu(){
}


void SceneMenu::init(){
	fons = new Background();
	fons->init(0, 0, "Assets/Images/menu.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Button button;
	button.init(PLAYER, 30, SCREEN_HEIGHT / 2, 50, 50, 0, 0, NULL);
	buttons.push_back(button);
	button.init(NEW_LEVEL, 70, SCREEN_HEIGHT / 2, 0, 0, 0, 0, NULL);
	buttons.push_back(button);
}


void SceneMenu::update(){
	for (itBut = buttons.begin(); itBut != buttons.end(); itBut++){
		if ((itBut)->update()){
			switch ((itBut)->GetId()){
			case PLAYER:
				smManager->changeScene(smManager->GAME);
				break;
			case NEW_LEVEL:

				break;
			}
		}
	}
}


void SceneMenu::render(){
	fons->render();

	for (itBut = buttons.begin(); itBut != buttons.end(); itBut++){
		(itBut)->render();
	}
}