#include "GameStats.h"


GameStats* GameStats::pInstance = NULL;

GameStats::GameStats(){
	level = 2;
	sound = false;
	pause = false;
	win = false;
}


GameStats::~GameStats()
{
}


GameStats* GameStats::getInstanceGameStats(){
	if (pInstance == NULL)
		pInstance = new GameStats();

	return pInstance;
}


int GameStats::GetLevel(){
	return level;
}

bool GameStats::GetSound(){
	return sound;
}

bool GameStats::GetPause(){
	return pause;
}

bool GameStats::GetWin(){
	return win;
}


void GameStats::IncrementLevel(){
	level++;
}

void GameStats::SetSound(bool enabled){
	sound = enabled;
}

void GameStats::SetPause(bool paused){
	pause = paused;
}

void GameStats::SetWin(bool victory){
	win = victory;
}