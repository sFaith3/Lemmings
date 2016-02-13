#include "Utils.h"

class InputManager
{
private:
	static InputManager* iInstance;

	bool quit;
	bool back;
	bool next;
	bool play;
	bool pause;
	bool stop;
	bool click;

public:
	InputManager();
	~InputManager();

	static InputManager* getInstanceInput();

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
};