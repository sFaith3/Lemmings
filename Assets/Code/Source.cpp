#include "Utils.h"
#include "SingletonManager.h"
#include "SceneManager.h"

InputManager* inputManager;
SceneManager* sceneManager;

bool IsGameClosed();

int main(int argc, char* args[]) {

	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
	sceneManager = SceneManager::getInstanceSM();

	sceneManager->init();

	bool end = false; // Game loop.
	while (!end) {
		sceneManager->update();

		inputManager->update();
		if (IsGameClosed())
			end = true;

		sceneManager->render();
	}

	sceneManager->~SceneManager();

	return 0;
}


bool IsGameClosed()
{
	return ((inputManager->isESC() || inputManager->getNumber() == 4) && sceneManager->getNumCurrScene() == sceneManager->MENU)
		|| inputManager->isQuit();
}