#include "InputManager.h"

#include "SDL.h"

InputManager* InputManager::iInstance = NULL;

InputManager::InputManager(){
	quit = false;
	back = false;
	pause = false;
	click = false;
}

InputManager::~InputManager(){

}

InputManager* InputManager::getInstanceInput(){
	if (iInstance == NULL){

		iInstance = new InputManager();
	}
	return iInstance;
}

void InputManager::Update(){
	SDL_Event test_event;
	SDL_Scancode tecla;
	back = false;
	pause = false;
	click = false;
	while (SDL_PollEvent(&test_event)) {
		switch (test_event.type) {
		case SDL_KEYDOWN:
			tecla = test_event.key.keysym.scancode;
			switch (tecla){
			case SDL_SCANCODE_ESCAPE:
				quit = true;
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

bool InputManager::CheckPause(){
	return pause;
}

bool InputManager::CheckClick(){
	if (click){
		click = false;
		return true;
	}
	return false;
}

void InputManager::GetMouseXY(int& x, int& y){
	SDL_GetMouseState(&x, &y);
}