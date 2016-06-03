#ifndef GAMESTATS_H
#define GAMESTATS_H

#include "Utils.h"

class GameStats
{
private:
	GameStats();

	static GameStats* pInstance; /*<!	Singleton instance*/

	int level;
	bool sound;
	bool pause;
	bool win;

public:
	~GameStats();

	//!	Gets Singleton instance.
	static GameStats* getInstanceGameStats();

	int GetLevel();
	bool GetSound();
	bool GetPause();
	bool GetWin();

	void IncrementLevel();
	void SetSound(bool enabled);
	void SetPause(bool paused);
	void SetWin(bool victory);
};

#endif