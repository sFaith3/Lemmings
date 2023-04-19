#include "InputManager.h"
#include "SDL.h"

InputManager* InputManager::iInstance = NULL;

InputManager::InputManager(){
	number = -1;
	quit = false;
	esc = false;
	back = false;
	pause = false;
	clickLeft = false;
	clickRight = false;
	enter = false;
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
				/*case SDL_SCANCODE_:
					enter = true;
					break;*/
			case SDL_SCANCODE_PAUSE:
				pause = true;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			tecla = test_event.key.keysym.scancode;
			switch (tecla){
			case SDL_SCANCODE_0:
			case SDL_SCANCODE_1:
			case SDL_SCANCODE_2:
			case SDL_SCANCODE_3:
			case SDL_SCANCODE_4:
			case SDL_SCANCODE_5:
			case SDL_SCANCODE_6:
			case SDL_SCANCODE_7:
			case SDL_SCANCODE_8:
			case SDL_SCANCODE_9:
				number = -1;
				break;
				/*case SDL_SCANCODE_:
					enter = false;
					break;*/
			default:
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (test_event.button.button == SDL_BUTTON_LEFT)
				clickLeft = true;
			else
				clickRight = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (test_event.button.button == SDL_BUTTON_LEFT)
				clickLeft = false;
			else
				clickRight = false;
			break;
		}
	}
}


void InputManager::SetCursorRelative(bool active){
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}


int InputManager::CheckNumber(){
	return number;
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

bool InputManager::CheckClickLeft(){
	return clickLeft;
}

bool InputManager::CheckClickRight(){
	return clickRight;
}

/*bool InputManager::CheckEnter(){
	return enter;
}*/


void InputManager::ResetNumber(){
	number = -1;
}

void InputManager::ResetESC(){
	esc = false;
}

void InputManager::ResetClick(){
	if (clickLeft)
		clickLeft = false;
	if (clickRight)
		clickRight = false;
}

void InputManager::ResetPause(){
	if (pause)
		pause = false;
}


void InputManager::SetNumber(int num){
	number = num;
}


void InputManager::GetMouseXY(int& x, int& y){
	SDL_GetMouseState(&x, &y);
}