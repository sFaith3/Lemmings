#include "InputManager.h"
#include "SDL.h"

InputManager *InputManager::iInstance = NULL;

InputManager::InputManager()
{
	number = -1;
	quit = false;
	esc = false;
	back = false;
	pause = false;
	clickLeft = false;
	clickRight = false;
	enter = false;
}

InputManager::~InputManager()
{
}

InputManager *InputManager::getInstanceInput()
{
	if (iInstance == NULL)
	{

		iInstance = new InputManager();
	}
	return iInstance;
}

void InputManager::update()
{
	back = false;

	SDL_Event test_event;
	SDL_Scancode key;

	while (SDL_PollEvent(&test_event))
	{
		switch (test_event.type)
		{
		case SDL_KEYDOWN:
			key = test_event.key.keysym.scancode;
			switch (key)
			{
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
			key = test_event.key.keysym.scancode;
			switch (key)
			{
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

void InputManager::getMouseXY(int& x, int& y)
{
	SDL_GetMouseState(&x, &y);
}

int InputManager::getNumber()
{
	return number;
}

void InputManager::setCursorRelative(bool active)
{
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

void InputManager::setNumber(int num)
{
	number = num;
}

bool InputManager::isQuit()
{
	return quit;
}

bool InputManager::isESC()
{
	return esc;
}

bool InputManager::isBack()
{
	return back;
}

bool InputManager::isPause()
{
	return pause;
}

bool InputManager::isClickLeft()
{
	return clickLeft;
}

bool InputManager::isClickRight()
{
	return clickRight;
}

/*bool InputManager::isEnter(){
	return enter;
}*/

void InputManager::resetNumber()
{
	number = -1;
}

void InputManager::resetESC()
{
	esc = false;
}

void InputManager::resetClick()
{
	if (clickLeft)
		clickLeft = false;
	if (clickRight)
		clickRight = false;
}

void InputManager::resetPause()
{
	if (pause)
		pause = false;
}