#include "Skill.h"


Skill::Skill(){
	remainingUses = 0;
	firstDigitNum = secondDigitNum = 0;

	minSpawnVelocity = 0;

	for (int i = 0; i < 2; i++)
		digits.push_back(new ABCsAlphaNum());
}

Skill::~Skill()
{
}


int Skill::GetNumberUses() {
	return remainingUses;
}


void Skill::init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, string uses){
	Button::init(id, posX, posY, width, height, 1, 1, posXini, posYini, pathNormal, pathPressed);

	if (uses != "NULL"){
		if (uses.length() > 1){
			remainingUses = (int)(((uses[0] - 48) * 10) + (uses[1] - 48));
			firstDigitNum = (int)uses[0] - 48;
			secondDigitNum = (int)uses[1] - 48;
		}
		else{
			remainingUses = (int)uses[0] - 48;
			firstDigitNum = 0;
			secondDigitNum = (int)uses[0] - 48;
		}

		minSpawnVelocity = 0;

		int spacingX = 12;
		int xDigit = posX + 4;
		int spacingY = 8;
		int yDigit = posY + spacingY;
		float digScaleX = 1;
		float digScaleY = 1;
		digits[0]->init(xDigit, yDigit, digScaleX, digScaleY, firstDigitNum);
		xDigit += 10;
		digits[1]->init(xDigit, yDigit, digScaleX, digScaleY, secondDigitNum);
	}
}

bool Skill::update(){
	return Button::update();
}

void Skill::render(){
	Button::render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++)
		(*itDigits)->render();
}


void Skill::SetMinVelocity(int vel){
	minSpawnVelocity = vel;
}

void Skill::LessVelocity(){
	if (remainingUses > minSpawnVelocity){
		remainingUses--;
		if (secondDigitNum > 0){
			secondDigitNum--;
			digits.back()->changeValue(secondDigitNum);
		}
		else{
			firstDigitNum--;
			secondDigitNum = 9;
			digits[0]->changeValue(firstDigitNum);
			digits[1]->changeValue(secondDigitNum);
		}
	}
}

void Skill::MoreVelocity(){
	if (remainingUses < 99){
		remainingUses++;
		if (secondDigitNum < 9){
			secondDigitNum++;
			digits.back()->changeValue(secondDigitNum);
		}
		else{
			firstDigitNum++;
			secondDigitNum = 0;
			digits[0]->changeValue(firstDigitNum);
			digits[1]->changeValue(secondDigitNum);
		}
	}
}

void Skill::OneUseLess(){
	if (remainingUses > 0){
		remainingUses--;
		if (secondDigitNum > 0){
			secondDigitNum--;
			digits.back()->changeValue(secondDigitNum);
		}
		else{
			firstDigitNum--;
			secondDigitNum = 9;
			digits[0]->changeValue(firstDigitNum);
			digits[1]->changeValue(secondDigitNum);
		}
	}
}