#include "Utils.h"
#include "SceneManager.h"


int main(int argc, char* args[]){

	int scene = 0;

	cin >> scene;

	SceneManager* sceneManager;
	sceneManager = SceneManager::getInstanceSM();

	/* --- INIT MANAGER D'ESCENES --- */
	sceneManager->Init(scene);

	bool fi = false;
	while (!fi){		
		//input->Update();
		
		/* --- UPDATE GAME --- */
		sceneManager->Update();
		
		/* --- RENDER --- */
		sceneManager->Render();
	}


	sceneManager->~SceneManager();
	return 0;
}