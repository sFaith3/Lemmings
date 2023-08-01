#include "Counter.h"

Counter::Counter() {
	firstNum = secondNum = 0;

	separationX = 0;
	addPercent = false;
	addNumber = false;
}

Counter::~Counter() {
}


void Counter::init(int x, int y, const char* img, int widht, int height, int scaleX, int scaleY, int separationInitial, int separationX, bool addPercent) {
	firstNum = secondNum = 0;
	addNumber = false;

	ElementHUD::init(x, y, img, false, 0, 0, widht, height, static_cast<float>(scaleX), static_cast<float>(scaleY));
	initNums(x, y, separationInitial, separationX, addPercent);
}

void Counter::initNums(int x, int y, int separationInitial, int separationX, bool addPercent) {
	int xNum, yNum;

	// First number
	xNum = x + separationInitial;
	yNum = y + 2;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, scaleX, scaleY, firstNum);

	// Second number
	this->separationX = separationX;
	xNum += separationX;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->init(xNum, yNum, scaleX, scaleY, secondNum);

	// Optional percent
	this->addPercent = addPercent;
	if (addPercent) {
		nums.push_back(new ABCsAlphaNum());
		nums.back()->init(xNum, yNum, scaleX, scaleY, '%');
	}
}

void Counter::clear() {
	nums.clear();
	nums.resize(0);
}

void Counter::render() {
	ElementHUD::render();

	if (!addNumber) {
		nums[0]->render();
		if (addPercent)
			nums.back()->render();
	}
	else {
		for (int i = 0; i < nums.size(); i++)
			nums[i]->render();
	}
}


void Counter::incrementNumber() {
	if (!addNumber) {
		if (firstNum < 9)
			firstNum++;
		else {
			addNumber = true;
			firstNum = 1;
			if (nums.size() > 2)
				nums.back()->move(separationX, 0);
		}
	}
	else {
		if (secondNum < 9) {
			secondNum++;
		}
		else {
			firstNum++;
			secondNum = 9;
		}
	}

	changeValue();
}

void Counter::decrementNumber() {
	if (addNumber) {
		if (secondNum > 0)
			secondNum--;
		else {
			firstNum--;
			if (firstNum < 1) {
				addNumber = false;
				firstNum = 9;
			}
		}
	}
	else if (firstNum > 0)
		firstNum--;

	changeValue();
}

void Counter::setNumber(int num) {
	string _num = to_string(num);

	firstNum = (int)_num[0] - 48;
	if (_num.length() > 1) {
		secondNum = (int)_num[1] - 48;
		if (!addNumber) {
			addNumber = true;
			if (nums.size() > 2)
				nums.back()->move(separationX, 0);
		}
	}
	else if (addNumber)
		addNumber = false;

	changeValue();
}

void Counter::setNumber(string num) {
	firstNum = (int)num[0] - 48;
	secondNum = (int)num[1] - 48;

	if ((firstNum > 0 && secondNum > 0) && !addNumber)
		addNumber = true;
	else if (addNumber)
		addNumber = false;

	changeValue();
}

void Counter::changeValue() {
	if (addNumber) {
		nums[0]->changeValue(firstNum);
		nums[1]->changeValue(secondNum);
	}
	else
		nums[0]->changeValue(firstNum);
}
