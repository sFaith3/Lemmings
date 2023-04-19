#pragma once
#include "ElementHUD.h"
#include "ABCsAlphaNum.h"

class Word :
	public ElementHUD
{
private:
	vector<ABCsAlphaNum*> lettersNums;
	vector<ABCsAlphaNum*>::iterator itLettersNum;

public:
	Word();
	~Word();

	void init(int x, int y, int scaleX, int scaleY, int separationX, string word);
	void clear();
	void render();
};