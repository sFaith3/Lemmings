#include "Skill.h"


Skill::Skill()
{
}


Skill::~Skill()
{
}


void Skill::init(int id, int posX, int posY, int width, int height, int posXini, int posYini, const char* pathNormal, const char* pathPressed, int usos){
	Button::init(id, posX, posY, width, height, posXini, posYini, pathNormal, pathPressed);

	usosRestants = usos;
}

bool Skill::update(){
	return Button::update();
}

void Skill::render(){
	Button::render();
}

int Skill::GetNumberUses(){
	return usosRestants;
}

void Skill::OneUseLess(){
	if (usosRestants > 0)
		usosRestants--;
}