#include "Word.h"


Word::Word()
{
}


Word::~Word()
{
}


void Word::init(int x, int y, int scaleX, int scaleY, int separationX, string word){
	ElementHUD::init(x, y, NULL, false, 0, 0, 0, 0, static_cast<float>(scaleX), static_cast<float>(scaleY));

	int _x = x;
	int _y = y;
	for (int i = 0; i < word.length(); i++){
		lettersNums.push_back(new ABCsAlphaNum());
		lettersNums.back()->init(_x, _y, static_cast<float>(scaleX), static_cast<float>(scaleY), word[i]);
		_x += separationX;
	}
}

void Word::clear(){
	lettersNums.clear();
	lettersNums.resize(0);
}

void Word::render(){
	for (itLettersNum = lettersNums.begin(); itLettersNum != lettersNums.end(); itLettersNum++){
		(*itLettersNum)->render();
	}
}