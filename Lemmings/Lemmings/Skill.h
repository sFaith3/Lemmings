#pragma once
#include "Button.h"
#include "ABCsAlphaNum.h"

class Skill :
	public Button
{
private:
	int usosRestants;
	int numPrimerDigit, numSegonDigit; // Igual que 'usosRestants'. Però, cada xifra per separada, per tal de mostrar els números a la HUD.

	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

public:
	Skill();
	~Skill();

	void init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, string usos);
	bool update();
	void render();

	int GetNumberUses();
	void OneUseLess();
};

