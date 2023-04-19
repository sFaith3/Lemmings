#pragma once
#include "ElementHUD.h"
#include "ABCsAlphaNum.h"

class Counter :
	public ElementHUD
{
private:
	int primerNum, segonNum;
	vector<ABCsAlphaNum*> nums;
	vector<ABCsAlphaNum*>::iterator itNums;

	int separationX;
	bool addPercent;
	bool addNumber;

public:
	Counter();
	~Counter();

	void init(int x, int y, const char* img, int widht, int height, int scaleX, int scaleY, int separationInital, int separationX, bool addPercent);
	void clear();
	void render();

	void incrementNumber();
	void decrementNumber();
	void setNumber(int num);
	void setNumber(string num);
};