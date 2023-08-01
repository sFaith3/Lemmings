#pragma once
#include "ElementHUD.h"
#include "ABCsAlphaNum.h"

class Timer :
	public ElementHUD
{
private:
	Uint32 mStarTicks; // Time to start counting. It is needed to calculate the current time difference of the program and the
					   // time when the start() method has been activated. To show on the first run of the update() a 0 instead of
					   // the time the program has been running.
	Uint32 mPausedTicks; // Time in pause. To calculate the difference when the Timer is resumed.
	bool mStarted; // To start the time.
	bool mPaused; // To pause the time.

	bool timeOut; // The time has expired. In this case, it goes from X to 0. When it is 0, it is true. It is necessary to finish
				  // the game due to a lack of time.
	int remainingTime; // The remaining time in seconds. SDL_GetTicks() does this in ms.
	Uint32 lastTime; // Time, prior to the current, in that execution of the update() to get the difference.

	// Just like 'remainingTime'. But each number separately, to show the numbers to the HUD.
	int minutes, firstNumSeconds, secondNumSeconds;
	vector<ABCsAlphaNum*> nums;
	vector<ABCsAlphaNum*>::iterator itNums;

public:
	Timer(int x, int y, string remainingTime);
	~Timer();

	void start();
	void update();
	void render();

	void updateTimer();
	void pause();
	void unpause();
	void stop();

	bool getTimeOut();
	Uint32 getTime();
	Uint32 getTimeMs();

	bool isStarted();
	bool isPaused();
};

