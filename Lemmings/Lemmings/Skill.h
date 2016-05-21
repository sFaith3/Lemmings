#pragma once
#include "Button.h"

class Skill :
	public Button
{
private:
	int usosRestants;

public:
	Skill();
	~Skill();

	void init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, int usos);
	bool update();
	void render();

	int GetNumberUses();
	void OneUseLess();
};

