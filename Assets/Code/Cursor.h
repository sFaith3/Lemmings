#pragma once
#include "ElementHUD.h"

class Cursor :
	public ElementHUD
{
private:
	Cursor();

	static Cursor* cInstance; /*!<	Singleton instance*/

	Sint32 idImgNormal, idImgHover;
	int widthNormal, heightNormal, widthHover, heightHover;

	bool changedCursor; // To change the cursor between normal and hover.

	InputManager* inputManager;

public:
	~Cursor();

	//! Gets Singleton instance
	static Cursor* getInstanceCursor();

	void Update();

	bool GetChangedCursor();
	void ChangeCursor();
};