#include "Skill.h"


Skill::Skill(){
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

		float digScaleX = 0.48f;
		float digScaleY = 0.8f;
		digits.push_back(new ABCsAlphaNum(digScaleX, digScaleY, numPrimerDigit));
		digits.push_back(new ABCsAlphaNum(digScaleX, digScaleY, numSegonDigit));
	}
}

bool Skill::update(){
	return Button::update();
}

void Skill::render(){
	Button::render();

	int spacingX = 1;
	int spacingY = 8;
	for (itDigits = digits.begin(); itDigits != digits.end(); itDigits++){
		spacingX += 9;
		(*itDigits)->Render(posX + spacingX, posY + spacingY);
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
			digits.back()->Update(numSegonDigit);
		}
		else{
			numPrimerDigit--;
			numSegonDigit = 9;
			digits[0]->Update(numPrimerDigit);
			digits[1]->Update(numSegonDigit);
		}
	}
}