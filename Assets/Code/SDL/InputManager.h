#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager
{
private:
	static InputManager *iInstance; /*!<	Singleton instance*/

	enum numbers
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE
	};
	int number;

	bool quit;
	bool esc;
	bool back;
	bool pause;
	bool clickLeft, clickRight;

public:
	InputManager();
	~InputManager();

	//! Gets Singleton instance.
	static InputManager *getInstanceInput();

	void update();

	void getMouseXY(int& x, int& y);
	int getNumber();

	void setCursorRelative(bool active);
	void setNumber(int num);

	bool isQuit();
	bool isESC();
	bool isBack();
	bool isPause();
	bool isClickLeft();
	bool isClickRight();

	void resetNumber();
	void resetESC();
	void resetClick();
	void resetPause();
};

#endif