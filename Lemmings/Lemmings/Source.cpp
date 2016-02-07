#include "Utils.h"
#include "SceneManager.h"


int main(int argc, char* args[]){

	VideoManager* video = VideoManager::getInstanceVideo();
	InputManager* input = InputManager::getInstanceInput();
	SceneManager sceneManager;


	cout << "Introduce el numeor de la escena que quieres cargar:" << endl << "1 - Tank" << endl << "2 - Music Player" << endl;

	int scene = 0;

	cin >> scene;


	sceneManager.Init(scene);

	while (!input->CheckQuit()){

		/*UPDATE DELTATIME*/
		video->UpdateTime();
		
		/*CHECK INPUT*/
		input->Update();
		
		/*UPDATE GAME*/
		sceneManager.Update();
		
		/*RENDER*/
		video->clearScreen(0xFFFFFF);
		sceneManager.Render();

		video->updateScreen();
	}


	video->close();
	return 0;
}