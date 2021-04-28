#include "Counter.h"


Counter::Counter()
{
}


Counter::~Counter()
{
}


void Counter::init(int x, int y, const char* img, int widht, int height, int scaleX, int scaleY, int separationInitial, int separationX, bool addPercent){
	ElementHUD::init(x, y, img, false, 0, 0, widht, height, scaleX, scaleY);
	primerNum = segonNum = 0;

	int xNum, yNum;
	xNum = x + separationInitial;
	yNum = y + 2;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->Init(xNum, yNum, scaleX, scaleY, primerNum);
	this->separationX = separationX;
	xNum += separationX;
	nums.push_back(new ABCsAlphaNum());
	nums.back()->Init(xNum, yNum, scaleX, scaleY, segonNum);
	this->addPercent = addPercent;
	if (addPercent){
		nums.push_back(new ABCsAlphaNum());
		nums.back()->Init(xNum, yNum, scaleX, scaleY, '%');
	}

	addNumber = false;
}

void Counter::clear(){
	nums.clear();
	nums.resize(0);
}

void Counter::render(){
	ElementHUD::render();
	if (!addNumber){
		nums[0]->Render();
		if (addPercent)
			nums.back()->Render();
	}
	else{
		for (int i = 0; i < nums.size(); i++)
			nums[i]->Render();
	}
}


void Counter::incrementNumber(){
	if (!addNumber){
		if (primerNum < 9)
			primerNum++;
		else{
			addNumber = true;
			primerNum = 1;
			if (nums.size() > 2)
				nums.back()->Move(separationX, 0);
		}
	}
	else{
		if (segonNum < 9){
			segonNum++;
		}
		else{
			primerNum++;
			segonNum = 9;
		}
	}

	if (addNumber){
		nums[0]->ChangeValue(primerNum);
		nums[1]->ChangeValue(segonNum);
	}
	else
		nums[0]->ChangeValue(primerNum);
}

void Counter::decrementNumber(){
	if (addNumber){
		if (segonNum > 0)
			segonNum--;
		else{
			primerNum--;
			if (primerNum < 1){
				addNumber = false;
				primerNum = 9;
			}
		}
	}
	else if (primerNum > 0)
		primerNum--;

	if (addNumber){
		nums[0]->ChangeValue(primerNum);
		nums[1]->ChangeValue(segonNum);
	}
	else
		nums[0]->ChangeValue(primerNum);
}

void Counter::setNumber(int num){
	string _num = to_string(num);

	primerNum = (int)_num[0] - 48;
	if (_num.length() > 1){
		segonNum = (int)_num[1] - 48;
		if (!addNumber){
			addNumber = true;
			if (nums.size() > 2)
				nums.back()->Move(separationX, 0);
		}
	}
	else if (addNumber)
		addNumber = false;

	if (addNumber){
		nums[0]->ChangeValue(primerNum);
		nums[1]->ChangeValue(segonNum);
	}
	else
		nums[0]->ChangeValue(primerNum);
}

void Counter::setNumber(string num){
	primerNum = (int)num[0] - 48;
	segonNum = (int)num[1] - 48;

	if ((primerNum > 0 && segonNum > 0) && !addNumber)
		addNumber = true;
	else if (addNumber)
		addNumber = false;

	if (addNumber){
		nums[0]->ChangeValue(primerNum);
		nums[1]->ChangeValue(segonNum);
	}
	else
		nums[0]->ChangeValue(primerNum);
}