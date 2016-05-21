#include "Utils.h"
#include "SingletonManager.h"
#include "SceneManager.h"

bool fi = false;

InputManager* inputManager = NULL;
SceneManager* sceneManager = NULL;

int main(int argc, char* args[]){

	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
	sceneManager = SceneManager::getInstanceSM();

	sceneManager->init();

	while (!fi){
		/* --- LOAD SCENE --- */
		sceneManager->update();

		/* --- CHECK INPUT --- */
		inputManager->ResetClick();
		inputManager->Update();
		if ((inputManager->CheckESC() && sceneManager->getCurrScene() == sceneManager->MENU) || inputManager->CheckQuit())
			fi = true;

		/* --- RENDER --- */
		sceneManager->render();
	}
	sceneManager->~SceneManager();

	return 0;
}