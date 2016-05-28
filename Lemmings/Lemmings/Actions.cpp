#include "Actions.h"


Actions::Actions(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}


Actions::~Actions()
{
}


int Actions::init(float scaleX, float scaleY, int velMinimaSpawn, string trepar, string paraigues, string explosio, string parat, string esgraons, string cavarLateral, string picar, string cavar){
	int hAction = 61;
	int x = 0;
	int y = SCREEN_HEIGHT - hAction;
	ElementHUD::init(x, y, "Assets/Images/hud.png", 0, 0, 480, hAction, scaleX, scaleY);
	
	currButton = TREPAR;

	int xSkill = x + 1;
	int wSkill = 40;
	int hSkill = 61;
	const char* imgSkillPressed = "Assets/Images/skillsPressed.png";
	skills.push_back(new Skill);
	skills.back()->init(REST_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "50");
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(PLUS_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "50");
	skills.back()->SetMinVelocity(velMinimaSpawn);
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
	skills.back()->init(PAUSA, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");
	xSkill += wSkill;
	skills.push_back(new Skill);
	skills.back()->init(MOAB, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");

	skills[currButton]->SetPressed(true);

	return currButton;
}


int Actions::update(){
	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		if ((*itSkills)->update()){
			if (currButton != -1){
				int pressedBut = (*itSkills)->GetId();
				if (pressedBut != REST_VEL_SPAWN && pressedBut != PLUS_VEL_SPAWN && pressedBut != PAUSA && pressedBut != MOAB){
					skills[currButton]->SetPressed(false);
					(*itSkills)->SetPressed(true);
					inputManager->ResetClick();

					return currButton = (*itSkills)->GetId();
				}

				return (*itSkills)->GetId();
			}

			return -1;
		}
	}

	int number = inputManager->CheckNumber();
	//if (number != -1 && currButton != REST_VEL_SPAWN && currButton != PLUS_VEL_SPAWN && currButton != PAUSA && currButton != MOAB)

	if (number != -1){
		if (number != REST_VEL_SPAWN && number != PLUS_VEL_SPAWN && number != PAUSA && number != MOAB){
			skills[currButton]->SetPressed(false);
			skills[number]->SetPressed(true);
			inputManager->ResetNumber();

			return currButton = skills[number]->GetId();
		}

		return skills[number]->GetId();
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


void Actions::DecrementVelocitySkill(){
	skills[PLUS_VEL_SPAWN]->LessVelocity();
}

void Actions::IncrementVelocitySkill(){
	skills[PLUS_VEL_SPAWN]->MoreVelocity();
}