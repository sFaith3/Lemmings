#include "Actions.h"


Actions::Actions(){
	inputManager = sManager->getInputManager();
}


Actions::~Actions()
{
}


void Actions::init(int trepar, int paraigues, int explosio, int parat, int esgraons, int cavarLateral, int picar, int cavar){
	int hAction = 61;
	int x = 0;
	int y = SCREEN_HEIGHT - hAction;
	ElementHUD::init(x, y, "Assets/Images/hud.png", 0, 0, 480, hAction);
	
	currButton = -1;

	Skill skill;
	int xSkill = x + 1;
	int wSkill = 40;
	int hSkill = 61;
	const char* imgSkillPressed = "Assets/Images/skillsPressed.png";
	skill.init(REST_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, 0);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(PLUS_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, 0);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(TREPAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, trepar);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(PARAIGUES, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, paraigues);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(EXPLOSIO, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, explosio);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(PARAT, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, parat);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(ESGRAONS, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, esgraons);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(CAVAR_LATERAL, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavarLateral);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(PICAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, picar);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(CAVAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavar);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(DD, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, -1);
	skills.push_back(skill);
	xSkill += wSkill;
	skill.init(MOAB, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, 0);
	skills.push_back(skill);
}


int Actions::update(){
	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		if (itSkills->update()){
			if (currButton != -1)
				skills[currButton].SetPressed(false);

			itSkills->SetPressed(true);
			return currButton = itSkills->GetId();
		}
	}

	int number = inputManager->CheckNumber();
	if (number != -1){
		if (currButton != -1)
			skills[currButton].SetPressed(false);

		skills[number].SetPressed(true);
		return currButton = skills[number].GetId();
	}

	return -1;
}


void Actions::render(){
	ElementHUD::render();

	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		itSkills->render();
	}
}

int Actions::GetNumberUsesSkill(int skill){
	if (skill >= 0)
		return skills[skill].GetNumberUses();

	return 0;
}

void Actions::DetractUseSkill(int skill){
	skills[skill].OneUseLess();
}