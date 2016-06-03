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
	mVectorScenes.clear();

	mVectorScenes.push_back(SceneMenu::getInstanceSceneMenu());
	mVectorScenes.push_back(SceneCodeLevel::getInstanceSceneCodeLevel());
	mVectorScenes.push_back(ScenePreGame::getInstanceScenePreGame());
	mVectorScenes.push_back(SceneGame::getInstanceSceneGame());
	mVectorScenes.push_back(ScenePostGame::getInstanceScenePostGame());

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


void SceneManager::changeScene(SceneEnum next_scene){
	mVectorScenes[mCurrScene]->clear();
	mCurrScene = next_scene;
	mVectorScenes[mCurrScene]->init();
}


int SceneManager::getNumCurrScene(){
	return mCurrScene;
}