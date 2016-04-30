#include "Utils.h"
#include "SceneManager.h"

SceneManager* sceneManager = NULL;
InputManager* inputManager = NULL;

int main(int argc, char* args[]){

	sceneManager = SceneManager::getInstanceSM();
	inputManager = InputManager::getInstanceInput();

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