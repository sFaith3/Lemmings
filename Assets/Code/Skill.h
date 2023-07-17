#pragma once
#include "Button.h"
#include "ABCsAlphaNum.h"

class Skill :
	public Button
{
private:
	int remainingUses;
	int firstDigitNum, secondDigitNum; // Like 'remainingUses', but each number separately, to show the numbers in the HUD.

	int minSpawnVelocity; // For the button that controls the speed decrease in which the ExitDoor class instantiates Lemmings.

	// Vector of the number of uses that each skill has.
	vector<ABCsAlphaNum*> digits;
	vector<ABCsAlphaNum*>::iterator itDigits;

public:
	Skill();
	~Skill();

	int GetNumberUses();

	void init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, string uses);
	bool update();
	void render();

	void SetMinVelocity(int vel);
	void LessVelocity();
	void MoreVelocity();
	void OneUseLess();
};