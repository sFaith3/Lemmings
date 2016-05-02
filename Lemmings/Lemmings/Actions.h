#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Button.h"

class Actions :
	public ElementHUD
{
private:
	vector<Button> actions;
	vector<Button>::iterator itActi;

	enum ActionEnum{
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, TREPAR, PARAIGUES, EXPLOSIO, PARAT, ESGRAONS, CAVAR_LATERAL, PICAR, CAVAR, DD, MOAB
	};

public:
	Actions();
	~Actions();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h);
	void update();
	void render();
};

