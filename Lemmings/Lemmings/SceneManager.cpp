#include "SceneManager.h"

#include "SceneLogo.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneCodeLevel.h"

SceneManager* SceneManager::smInstance = NULL;

SceneManager::SceneManager(){
	sManager = SingletonManager::getInstanceSingleton();
	init();
}

SceneManager::~SceneManager(){
	sManager->getVideoManager()->close();
}


SceneManager* SceneManager::getInstanceSM(){
	if (smInstance == NULL)
		smInstance = new SceneManager();
	
	return smInstance;
}


void SceneManager::init(){
	mVectorScenes.resize(NUM_SCENES);
	
	SceneLogo *logo = new SceneLogo();
	SceneMenu *menu = new SceneMenu();
	SceneCodeLevel *codeLevel = new SceneCodeLevel();
	SceneGame *game = new SceneGame();

	logo->init();
	menu->init();
	codeLevel->init();
	game->init();

	mVectorScenes[LOGO] = logo;
	mVectorScenes[MENU] = menu;
	mVectorScenes[CODE_LEVEL] = codeLevel;
	mVectorScenes[GAME] = game;

	//mCurrScene = LOGO;
	mCurrScene = GAME;
}


void SceneManager::update(){
	mVectorScenes[mCurrScene]->update();
}


void SceneManager::render(){
	mVectorScenes[mCurrScene]->render();
}


void SceneManager::changeScene(SceneEnum next_scene){
	mCurrScene = next_scene;
}