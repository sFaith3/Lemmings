#include "InputManager.h"

#include "SDL.h"

InputManager* InputManager::iInstance = NULL;

InputManager::InputManager(){
	number = -1;
	quit = false;
	esc = false;
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
	while (SDL_PollEvent(&test_event)) {
		switch (test_event.type) {
		case SDL_KEYDOWN:
			tecla = test_event.key.keysym.scancode;
			switch (tecla){
			case SDL_SCANCODE_ESCAPE:
				esc = true;
				break;
			case SDL_SCANCODE_0:
				number = ZERO;
				break;
			case SDL_SCANCODE_1:
				number = ONE;
				break;
			case SDL_SCANCODE_2:
				number = TWO;
				break;
			case SDL_SCANCODE_3:
				number = THREE;
				break;
			case SDL_SCANCODE_4:
				number = FOUR;
				break;
			case SDL_SCANCODE_5:
				number = FIVE;
				break;
			case SDL_SCANCODE_6:
				number = SIX;
				break;
			case SDL_SCANCODE_7:
				number = SEVEN;
				break;
			case SDL_SCANCODE_8:
				number = EIGHT;
				break;
			case SDL_SCANCODE_9:
				number = NINE;
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


int InputManager::CheckNumber(){
	int _number = number;
	number = -1;
	return _number;
}

bool InputManager::CheckQuit(){
	return quit;
}

bool InputManager::CheckESC(){
	return esc;
}

bool InputManager::CheckBack(){
	return back;
}

bool InputManager::CheckPause(){
	return pause;
}

bool InputManager::CheckClick(){
	if (click){
		return true;
	}
	return false;
}

void InputManager::ResetClick(){
	if (click)
		click = false;
}

void InputManager::GetMouseXY(int& x, int& y){
	SDL_GetMouseState(&x, &y);
}