#include "InputManager.h"


InputManager* InputManager::instance = NULL;
InputManager::InputManager()
{

	quit = false;
	back = false;
	next = false;
	play = false;
	pause = false;
	stop = false;
	click = false;
}


InputManager::~InputManager()
{

}

void InputManager::Update(){
	SDL_Event test_event;
	SDL_Scancode tecla;
	back = false;
	next = false;
	play = false;
	pause = false;
	stop = false;
	click = false;
	while (SDL_PollEvent(&test_event)) {
		switch (test_event.type) {
		case SDL_KEYDOWN:
			tecla = test_event.key.keysym.scancode;
			switch (tecla)
			{
			case SDL_SCANCODE_ESCAPE:
				quit = true;
				break;
			case SDL_SCANCODE_Z:
				back = true;
				break;
			case SDL_SCANCODE_X:
				play = true;
				break;
			case SDL_SCANCODE_C:
				pause= true;
				break;
			case SDL_SCANCODE_V:
				stop = true;
				break;
			case SDL_SCANCODE_B:
				next = true;
				break;
			default:
				break;
			}
			break;

		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			click = true;
			break;
		}
	}
}


bool InputManager::CheckQuit(){
	return quit;
}


bool InputManager::CheckBack(){
	return back;
}

bool InputManager::CheckPlay(){
	return play;
}

bool InputManager::CheckPause(){
	return pause;
}

bool InputManager::CheckStop(){
	return stop;
}
bool InputManager::CheckNext(){
	return next;
}


InputManager* InputManager::getInstanceInput(){
	if (instance == NULL){

		instance = new InputManager();
	}
	return instance;
}



void InputManager::GetMouseXY(int& x, int& y){

	SDL_GetMouseState(&x, &y);

}

bool InputManager::MouseClick(){
	//Fire1 = MouseClick
	if (click){
		click = false;
		return true;
	}
	return false;

}