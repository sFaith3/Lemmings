#include "SceneManager.h"

#include "SceneMenu.h"
#include "SceneCodeLevel.h"
#include "ScenePreGame.h"
#include "SceneGame.h"

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
	mVectorScenes.push_back(new SceneGame());

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
	mCurrScene = next_scene;
	mVectorScenes[mCurrScene]->init();
}


void SceneManager::reinitScene(int scene){
	delete mVectorScenes[scene];
	switch (scene){
	case GAME:
		mVectorScenes[scene] = new SceneGame();
		break;
	default:
		cout << "Error with 'reinitScene()' in the SceneManager!\n";
		break;
	}
}


int SceneManager::getCurrScene(){
	return mCurrScene;
}