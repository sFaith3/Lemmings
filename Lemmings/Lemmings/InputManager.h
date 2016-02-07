#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Utils.h"

class InputManager
{
private:
	bool quit;
	bool back;
	bool next;
	bool play;
	bool pause;
	bool stop;
	bool click;
	static InputManager* instance;
public:
	InputManager();
	~InputManager();

	void Update();

	//bool CheckFire(int player);


	bool CheckQuit();
	bool CheckBack();

	bool CheckPlay();

	bool CheckPause();

	bool CheckStop();
	bool CheckNext();



	int GetDirection(int player);

	void GetMouseXY(int& x, int& y);

	bool MouseClick();

	static InputManager* getInstanceInput();
};

#endif