#pragma once
#include "ElementHUD.h"

class Cursor :
	public ElementHUD
{
private:
	Cursor();

	static Cursor* cInstance; /*!<	Singleton instance*/

	Sint32 idImg1, idImg2;
	int width1, height1, width2, height2;

	/*enum CursorsEnum{
		NONE, NORMAL, LEMMING
	};
	int currCursor;*/
	bool changedCursor;

	InputManager* inputManager;

public:
	~Cursor();

	//! Gets Singleton instance
	static Cursor* getInstanceCursor();

	void Update();

	bool GetChangedCursor();
	void ChangeCursor();
};