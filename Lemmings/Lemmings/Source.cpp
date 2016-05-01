#include "Utils.h"
#include "SingletonManager.h"
#include "SceneManager.h"

InputManager* inputManager = NULL;
SceneManager* sceneManager = NULL;

int main(int argc, char* args[]){

	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
	sceneManager = SceneManager::getInstanceSM();

	sceneManager->init();

	while (!inputManager->CheckQuit()){
		/* --- LOAD SCENE --- */
		sceneManager->update();

		/* --- CHECK INPUT --- */
		inputManager->Update();

		/* --- RENDER --- */
		sceneManager->render();
	}
	sceneManager->~SceneManager();

	return 0;
}