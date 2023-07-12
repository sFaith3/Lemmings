#include "Actions.h"

Actions::Actions() {
	const int NumSkills = 12;
	for (int i = 0; i < NumSkills; i++)
		skills.push_back(new Skill());

	currButton = -1;

	gameStats = GameStats::getInstanceGameStats();
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}

Actions::~Actions() {
}


int Actions::init(float scaleX, float scaleY, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig) {
	currButton = CLIMB;

	int hAction = 61;
	int x = 0;
	int y = SCREEN_HEIGHT - hAction;
	ElementHUD::init(x, y, "Assets/Art/Images/HUD/Skills/hud.png", false, 0, 0, 480, hAction, scaleX, scaleY);

	initSkills(x, y, minVelSpawn, climb, umbrella, explosion, standing, steps, sideDig, chip, dig);

	return currButton;
}

void Actions::initSkills(int x, int y, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig) {
	int xSkill = x + 1;
	int wSkill = 40;
	int hSkill = 61;
	const char* imgSkillPressed = "Assets/Art/Images/HUD/Skills/skillsPressed.png";

	skills[0]->init(REST_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, minVelSpawn);
	xSkill += wSkill;
	skills[1]->init(PLUS_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, minVelSpawn);
	int i_minVelSpawn = 0;
	for (int i = 0; i < minVelSpawn.length(); i++) {
		if (i == 0)
			i_minVelSpawn += ((int)minVelSpawn[i] - 48) * 10;
		else
			i_minVelSpawn += (int)minVelSpawn[i] - 48;
	}
	skills[1]->SetMinVelocity(i_minVelSpawn);
	xSkill += wSkill;
	skills[2]->init(CLIMB, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, climb);
	xSkill += wSkill;
	skills[3]->init(UMBRELLA, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, umbrella);
	xSkill += wSkill;
	skills[4]->init(EXPLOSION, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, explosion);
	xSkill += wSkill;
	skills[5]->init(STANDING, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, standing);
	xSkill += wSkill;
	skills[6]->init(STEPS, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, steps);
	xSkill += wSkill;
	skills[7]->init(SIDE_DIG, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, sideDig);
	xSkill += wSkill;
	skills[8]->init(CHIP, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, chip);
	xSkill += wSkill;
	skills[9]->init(DIG, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, dig);
	xSkill += wSkill;
	skills[10]->init(PAUSE, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");
	xSkill += wSkill;
	skills[11]->init(MOAB, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");

	skills[currButton]->setPressed(true);
}


int Actions::update() {
	int actionToReturn = -1;

	actionToReturn = getPressButton();
	if (!isNextCheck(actionToReturn))
		return actionToReturn;

	actionToReturn = getPressNumber();

	return (!isNextCheck(actionToReturn)) ? actionToReturn : -1;
}

// To check if it needs to go to the next method in update()
bool Actions::isNextCheck(int actionToReturn) {
	const int NextCheck = -2;
	return actionToReturn == NextCheck;
}


void Actions::render() {
	ElementHUD::render();

	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++) {
		(*itSkills)->render();
	}
}


int Actions::getPressButton() {
	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++) {
		if ((*itSkills)->update()) {
			if (currButton == -1)
				return -1;

			int pressedBut = (*itSkills)->getId();
			if (!gameStats->GetPause() && (pressedBut != REST_VEL_SPAWN && pressedBut != PLUS_VEL_SPAWN && pressedBut != PAUSE && pressedBut != MOAB)) {
				skills[currButton]->setPressed(false);
				(*itSkills)->setPressed(true);
				inputManager->resetClick();

				return (currButton != pressedBut) ? currButton = (*itSkills)->getId() : -1;
			}

			return (*itSkills)->getId();
		}
	}

	return -2;
}

int Actions::getPressNumber() {
	int number = inputManager->getNumber();

	if (number == -1)
		return -2;

	if (number != REST_VEL_SPAWN && number != PLUS_VEL_SPAWN && number != MOAB) {
		skills[currButton]->setPressed(false);
		skills[number]->setPressed(true);
		inputManager->resetNumber();

		return (currButton != number) ? currButton = skills[number]->getId() : -1;
	}

	return skills[number]->getId();
}

int Actions::getNumberUsesSkill(int skill) {
	if (skill >= 0)
		return skills[skill]->GetNumberUses();

	return 0;
}

void Actions::detractUseSkill(int skill) {
	skills[skill]->OneUseLess();
}


void Actions::decrementVelocitySkill() {
	skills[PLUS_VEL_SPAWN]->LessVelocity();
}

void Actions::incrementVelocitySkill() {
	skills[PLUS_VEL_SPAWN]->MoreVelocity();
}