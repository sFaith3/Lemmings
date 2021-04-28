#include "Skill.h"


Skill::Skill(){
	for (int i = 0; i < 2; i++)
		digits.push_back(new ABCsAlphaNum());
}


Skill::~Skill()
{
}


void Skill::init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, string usos){
	Button::init(id, posX, posY, width, height, 1, 1, posXini, posYini, pathNormal, pathPressed);

	if (usos != "NULL"){
		if (usos.length() > 1){
			usosRestants = (int)(((usos[0] - 48) * 10) + (usos[1] - 48));
			numPrimerDigit = (int)usos[0] - 48;
			numSegonDigit = (int)usos[1] - 48;
		}
		else{
			usosRestants = (int)usos[0] - 48;
			numPrimerDigit = 0;
			numSegonDigit = (int)usos[0] - 48;
		}

		velMinimaSpawn = NULL;

		int spacingX = 12;
		int xDigit = posX + 4;
		int spacingY = 8;
		int yDigit = posY + spacingY;
		float digScaleX = 1;
		float digScaleY = 1;
		digits[0]->Init(xDigit, yDigit, digScaleX, digScaleY, numPrimerDigit);
		xDigit += 10;
		digits[1]->Init(xDigit, yDigit, digScaleX, digScaleY, numSegonDigit);
	}
}

bool Skill::update(){
	return Button::update();
}

void Skill::render(){
	Button::render();

	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++)
		(*itDigits)->Render();
}


void Skill::SetMinVelocity(int vel){
	velMinimaSpawn = vel;
}

void Skill::LessVelocity(){
	if (usosRestants > velMinimaSpawn){
		usosRestants--;
		if (numSegonDigit > 0){
			numSegonDigit--;
			digits.back()->ChangeValue(numSegonDigit);
		}
		else{
			numPrimerDigit--;
			numSegonDigit = 9;
			digits[0]->ChangeValue(numPrimerDigit);
			digits[1]->ChangeValue(numSegonDigit);
		}
	}
}

void Skill::MoreVelocity(){
	if (usosRestants < 99){
		usosRestants++;
		if (numSegonDigit < 9){
			numSegonDigit++;
			digits.back()->ChangeValue(numSegonDigit);
		}
		else{
			numPrimerDigit++;
			numSegonDigit = 0;
			digits[0]->ChangeValue(numPrimerDigit);
			digits[1]->ChangeValue(numSegonDigit);
		}
	}
}


int Skill::GetNumberUses(){
	return usosRestants;
}

void Skill::OneUseLess(){
	if (usosRestants > 0){
		usosRestants--;
		if (numSegonDigit > 0){
			numSegonDigit--;
			digits.back()->ChangeValue(numSegonDigit);
		}
		else{
			numPrimerDigit--;
			numSegonDigit = 9;
			digits[0]->ChangeValue(numPrimerDigit);
			digits[1]->ChangeValue(numSegonDigit);
		}
	}
}