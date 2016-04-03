#pragma once
#include "ElementGame.h"
class Lemming :
	public ElementGame
{
private:
	enum estats{
		IDLE, MOVE, FALL
	};
	int estat;
	int dir; //Direcció del Lemming a l'hora de moure's.

public:
	Lemming();
	~Lemming();

	void Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h);
	void Update();
};

