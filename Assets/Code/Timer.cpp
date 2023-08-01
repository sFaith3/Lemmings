#include "Timer.h"
#include "SingletonManager.h"

// \param remainingTime in "minutes : seconds" format. Minutes below 10 must go without a 0 ahead.
Timer::Timer(int x, int y, string remainingTime)
{
	ElementHUD::init(x, y, "Assets/Art/Images/HUD/Timer/timer.png", false, 0, 0, 100, 19, 1, 1);

	mStarTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;

	timeOut = false;
	lastTime = 0;

	minutes = remainingTime[0] - 48;
	firstNumSeconds = remainingTime[2] - 48;
	secondNumSeconds = remainingTime[3] - 48;
	this->remainingTime = ((minutes * 60) + firstNumSeconds + secondNumSeconds);

	int xNum, yNum;
	xNum = x + 45;
	yNum = y + 2;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, minutes);
	xNum += 28;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, firstNumSeconds);
	xNum += 17;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, secondNumSeconds);
}

Timer::~Timer()
{
}


void Timer::start()
{
	mStarted = true;
	mPaused = false;

	mStarTicks = videoManager->getTime();
	mPausedTicks = 0;

	lastTime = remainingTime;
}

void Timer::update()
{
	if (!timeOut)
	{
		updateTimer();
	}
}

void Timer::render()
{
	ElementHUD::render();

	for (itNums = nums.begin(); itNums != nums.end(); itNums++)
		(*itNums)->render();
}


void Timer::updateTimer()
{
	Uint32 time = remainingTime - getTime();
	if (time >= 0)
	{
		Uint32 differenceTime = lastTime - time;
		lastTime = time;
		if (differenceTime > 0)
		{
			if (minutes == 0 && firstNumSeconds == 0 && secondNumSeconds == 0)
				timeOut = true;
			else if (secondNumSeconds > 0)
			{
				secondNumSeconds--;
				nums.back()->changeValue(secondNumSeconds);
			}
			else if (firstNumSeconds > 0)
			{
				firstNumSeconds--;
				secondNumSeconds = 9;
				nums[1]->changeValue(firstNumSeconds);
				nums.back()->changeValue(secondNumSeconds);
			}
			else
			{
				minutes--;
				firstNumSeconds = 9;
				secondNumSeconds = 9;
				nums[0]->changeValue(minutes);
				nums[1]->changeValue(firstNumSeconds);
				nums.back()->changeValue(secondNumSeconds);
			}
		}
	}
}

void Timer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;

		mPausedTicks = videoManager->getTime() - mStarTicks;
		mStarTicks = 0;
	}
}

void Timer::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;

		mStarTicks = videoManager->getTime() - mPausedTicks;

		mPausedTicks = 0;
	}
}

void Timer::stop()
{
	mStarted = false;
	mPaused = false;

	mStarTicks = 0;
	mPausedTicks = 0;
}


bool Timer::getTimeOut()
{
	return timeOut;
}

Uint32 Timer::getTime()
{
	Uint32 time = 0;
	if (mStarted)
	{
		if (!mPaused)
			time = (videoManager->getTime() - mStarTicks) / 1000;
	}

	return time;
}

Uint32 Timer::getTimeMs()
{
	Uint32 time = 0;
	if (mStarted)
	{
		if (!mPaused)
			time = videoManager->getTime() - mStarTicks;
	}

	return time;
}


bool Timer::isStarted()
{
	return mStarted;
}

bool Timer::isPaused()
{
	return mStarted && mPaused;
}