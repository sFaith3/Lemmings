#pragma once
#include "Button.h"
#include "ABCsAlphaNum.h"

class Skill :
	public Button
{
private:
	int usosRestants;
	int numPrimerDigit, numSegonDigit; // Igual que 'usosRestants'. Per�, cada xifra per separat, per tal de mostrar els n�meros a la HUD.

	int velMinimaSpawn; // Per el but� que controla el decrement de la velocitat en que ExitDoor instancia Lemmings.

	// Vector dels n�meros d'usos que t� cada habilitat.
	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

public:
	Skill();
	~Skill();

	void init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, string usos);
	bool update();
	void render();

	void SetMinVelocity(int vel);
	void LessVelocity();
	void MoreVelocity();

	int GetNumberUses();
	void OneUseLess();
};