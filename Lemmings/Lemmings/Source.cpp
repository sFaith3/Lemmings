#include "Utils.h"
#include "SceneManager.h"


int main(int argc, char* args[]){

	int scene = 0;

	cin >> scene;

	static SingletonManager* sManager;
	sManager = sManager->getInstanceSingleton();

	/* --- INIT ESCENA --- */
	sManager->getScene()->Init(scene);

	bool fi = false;
	while (!fi){

		/* --- UPDATE DELTATIME --- */
		sManager->getVideo()->UpdateTime();
		
		//input->Update();
		
		/* --- UPDATE GAME --- */
		sManager->getScene()->Update();
		
		/* --- RENDER --- */
		sManager->getVideo()->clearScreen(0xFFFFFF);
		sManager->getScene()->Render();

		sManager->getVideo()->updateScreen();
	}


	sManager->getVideo()->close();
	return 0;
}