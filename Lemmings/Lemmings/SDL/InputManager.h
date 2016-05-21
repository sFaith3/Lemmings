#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager
{
private:
	static InputManager* iInstance;

	enum numbers{
		ZERO, ONE, TWO, THREE, FOUR
	};
	int number;
	bool quit;
	bool esc;
	bool back;
	bool pause;
	bool click;

public:
	InputManager();
	~InputManager();

	static InputManager* getInstanceInput();

	void Update();

	int CheckNumber();
	bool CheckQuit();
	bool CheckESC();
	bool CheckBack();
	bool CheckPause();
	bool CheckClick();

	void GetMouseXY(int& x, int& y);
};

#endif