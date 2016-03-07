#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Utils.h"

class InputManager
{
private:
	static InputManager* iInstance;

	bool quit;
	bool back;
	bool pause;
	bool click;

public:
	InputManager();
	~InputManager();

	static InputManager* getInstanceInput();

	void Update();

	bool CheckQuit();
	bool CheckBack();
	bool CheckPause();
	bool CheckClick();

	void GetMouseXY(int& x, int& y);
};

#endif