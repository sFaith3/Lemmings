#include "Utils.h"
#include "SingletonManager.h"


int main(int argc, char* args[]){

	int scene = 0;

	cin >> scene;

	SingletonManager* sManager;
	sManager = sManager->getInstanceSingleton();

	/* --- INIT ESCENA --- */
	sManager->sceneManager->Init(scene);

	bool fi = false;
	while (!fi){

		/* --- UPDATE DELTATIME --- */
		sManager->videoManager->UpdateTime();
		
		//input->Update();
		
		/* --- UPDATE GAME --- */
		sManager->sceneManager->Update();
		
		/* --- RENDER --- */
		sManager->videoManager->clearScreen(0xFFFFFF);
		sManager->sceneManager->Render();

		sManager->videoManager->updateScreen();
	}


	sManager->videoManager->close();
	return 0;
}