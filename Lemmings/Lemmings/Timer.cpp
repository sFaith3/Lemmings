#include "Timer.h"
#include "SingletonManager.h"

// \param tempsRestant en format "minuts : segons". Els minuts inferiors a 10 han d'anar sense el 0 davant.
Timer::Timer(int x, int y, string tempsRestant){
	ElementHUD::init(x, y, /*"Assets/Images/Timer/Temps2.png"*/NULL, 0, 0, 150, 25, 1, 1);
	
	mStarTicks = 0;
	mPausedTicks = 0;

	mStarted = false;
	mPaused = false;

	tempsOut = false;
	lastTime = 0;

	minuts = tempsRestant[0] - 48;
	primerNumSegons = tempsRestant[2] - 48;
	segonNumSegons = tempsRestant[3] - 48;
	this->tempsRestant = ((minuts * 60) + primerNumSegons + segonNumSegons);

	int xNum, yNum;
	xNum = x + 150;
	yNum = y;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, minuts);
	xNum += 24;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, primerNumSegons);
	xNum += 17;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, 1, 1, segonNumSegons);
}


Timer::~Timer(){
}


void Timer::start(){
	mStarted = true;
	mPaused = false;

	mStarTicks = videoManager->getTime();
	mPausedTicks = 0;

	lastTime = tempsRestant;
}

void Timer::update(){
	if (!tempsOut){
		Uint32 time = tempsRestant - getTime();
		if (time >= 0){
			Uint32 diferenciaTemps = lastTime - time;
			lastTime = time;
			if (diferenciaTemps > 0){
				if (minuts == 0 && primerNumSegons == 0 && segonNumSegons == 0)
					tempsOut = true;
				else if (segonNumSegons > 0){
					segonNumSegons--;
					nums.back()->ChangeValue(segonNumSegons);
				}
				else if (primerNumSegons > 0){
					primerNumSegons--;
					segonNumSegons = 9;
					nums[1]->ChangeValue(primerNumSegons);
					nums.back()->ChangeValue(segonNumSegons);
				}
				else{
					minuts--;
					primerNumSegons = 9;
					segonNumSegons = 9;
					nums[0]->ChangeValue(minuts);
					nums[1]->ChangeValue(primerNumSegons);
					nums.back()->ChangeValue(segonNumSegons);
				}
			}
		}
	}
}

void Timer::render(){
	ElementHUD::render();

	for (itNums = nums.begin(); itNums != nums.end(); itNums++)
		(*itNums)->Render();
}


void Timer::pause(){
	if (mStarted && !mPaused){
		mPaused = true;

		mPausedTicks = videoManager->getTime() - mStarTicks;
		mStarTicks = 0;
	}
}

void Timer::unpause(){
	if (mStarted && mPaused){
		mPaused = false;

		mStarTicks = videoManager->getTime() - mPausedTicks;
		
		mPausedTicks = 0;
	}
}

void Timer::stop(){
	mStarted = false;
	mPaused = false;

	mStarTicks = 0;
	mPausedTicks = 0;
}


Uint32 Timer::getTime(){
	Uint32 time = 0;
	if (mStarted){
		if (!mPaused)
			time = (videoManager->getTime() - mStarTicks) / 1000;
	}

	return time;
}

Uint32 Timer::getTimeMs(){
	Uint32 time = 0;
	if (mStarted){
		if (!mPaused)
			time = videoManager->getTime() - mStarTicks;
	}

	return time;
}


bool Timer::isStarted(){
	return mStarted;
}

bool Timer::isPaused(){
	return mStarted && mPaused;
}


bool Timer::getTempsOut(){
	return tempsOut;
}