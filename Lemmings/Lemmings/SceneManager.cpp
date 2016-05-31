#include "SceneManager.h"

#include "SceneMenu.h"
#include "SceneCodeLevel.h"
#include "ScenePreGame.h"
#include "SceneGame.h"
#include "ScenePostGame.h"

SceneManager* SceneManager::smInstance = NULL;

SceneManager::SceneManager(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
}

SceneManager::~SceneManager(){
	videoManager->close();
}


SceneManager* SceneManager::getInstanceSM(){
	if (smInstance == NULL)
		smInstance = new SceneManager();
	
	return smInstance;
}


void SceneManager::init(){
	videoManager->clearScreen(0x000000);
	videoManager->updateScreen();

	mVectorScenes.clear();

	mVectorScenes.push_back(new SceneMenu());
	mVectorScenes.push_back(new SceneCodeLevel());
	mVectorScenes.push_back(new ScenePreGame());
	mVectorScenes.push_back(SceneGame::getInstanceSceneGame());
	mVectorScenes.push_back(new ScenePostGame());

	mCurrScene = MENU;
	mVectorScenes[mCurrScene]->init();
}


void SceneManager::update(){
	mVectorScenes[mCurrScene]->update();
	videoManager->updateTime();
}


void SceneManager::render(){
	videoManager->clearScreen(0x000000);
	mVectorScenes[mCurrScene]->render();
	videoManager->updateScreen();
}


void SceneManager::changeScene(int next_scene){
	reinitScene(mCurrScene);
	mCurrScene = next_scene;
	mVectorScenes[mCurrScene]->init();
}


void SceneManager::reinitScene(int scene){
	delete mVectorScenes[scene];
	switch (scene){
	case MENU:
		mVectorScenes[scene] = new SceneMenu();
		break;
	case PRE_GAME:
		mVectorScenes[scene] = new ScenePreGame();
		break;
	case GAME:
		delete mVectorScenes[PRE_GAME];
		mVectorScenes[scene] = SceneGame::getInstanceSceneGame();
		break;
	case POST_GAME:
		mVectorScenes[scene] = new ScenePostGame();
		break;
	default:
		break;
	}
}


int SceneManager::getNumCurrScene(){
	return mCurrScene;
}