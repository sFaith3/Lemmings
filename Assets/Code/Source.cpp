#include "Utils.h"
#include "SingletonManager.h"
#include "SceneManager.h"

int main(int argc, char* args[]){

	InputManager* inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
	SceneManager* sceneManager = SceneManager::getInstanceSM();

	sceneManager->init();

	bool fi = false; // Bucle del joc.
	while (!fi){
		/* --- LOAD SCENE --- */
		sceneManager->update();

		/* --- CHECK INPUT --- */
		inputManager->update();
		if (((inputManager->isESC() || inputManager->getNumber() == 4) && sceneManager->getNumCurrScene() == sceneManager->MENU) || inputManager->isQuit())
			fi = true;

		/* --- RENDER --- */
		sceneManager->render();
	}

	sceneManager->~SceneManager();

	return 0;
}