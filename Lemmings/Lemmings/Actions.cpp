#include "Actions.h"


Actions::Actions(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}


Actions::~Actions()
{
}


void Actions::init(float scaleX, float scaleY, string trepar, string paraigues, string explosio, string parat, string esgraons, string cavarLateral, string picar, string cavar){
	int hAction = 61;
	int x = 0;
	int y = SCREEN_HEIGHT - hAction;
	ElementHUD::init(x, y, "Assets/Images/hud.png", 0, 0, 480, hAction, scaleX, scaleY);
	
	currButton = -1;

	int xSkill = x + 1;
	int wSkill = 40;
	int hSkill = 61;
	const char* imgSkillPressed = "Assets/Images/skillsPressed.png";
	skills.push_back(new Skill);
	skills.back()->init(REST_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "50");
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(PLUS_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "50");
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(TREPAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, trepar);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(PARAIGUES, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, paraigues);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(EXPLOSIO, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, explosio);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(PARAT, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, parat);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(ESGRAONS, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, esgraons);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(CAVAR_LATERAL, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavarLateral);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(PICAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, picar);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(CAVAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavar);
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(DD, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(MOAB, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");
}


int Actions::update(){
	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		if ((*itSkills)->update()){
			if (currButton != -1)
				skills[currButton]->SetPressed(false);

			(*itSkills)->SetPressed(true);
			return currButton = (*itSkills)->GetId();
		}
	}

	int number = inputManager->CheckNumber();
	if (number != -1){
		if (currButton != -1)
			skills[currButton]->SetPressed(false);

		skills[number]->SetPressed(true);
		return currButton = skills[number]->GetId();
	}

	return -1;
}


void Actions::render(){
	ElementHUD::render();

	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		(*itSkills)->render();
	}
}

int Actions::GetNumberUsesSkill(int skill){
	if (skill >= 0)
		return skills[skill]->GetNumberUses();

	return 0;
}

void Actions::DetractUseSkill(int skill){
	skills[skill]->OneUseLess();
}