#include "ABCsAlphaNum.h"


ABCsAlphaNum::ABCsAlphaNum(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
	idImg = videoManager->getTextureID("Assets/Images/ABCsAlphaNum/alphabet.png");
}


ABCsAlphaNum::~ABCsAlphaNum(){
}


void ABCsAlphaNum::init(int x, int y, float scaleX, float scaleY, int alphaNum){
	posX = x;
	posY = y;

	xIni = yIni = 3;
	width = 16;
	height = 15;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	spacingX = 1;
	spacingY = 1;
	digitsMaxRow = 13;

	ChangeValue(alphaNum);
}

void ABCsAlphaNum::init(int x, int y, float scaleX, float scaleY, char alphaLetter){
	posX = x;
	posY = y;

	xIni = yIni = 3;
	width = 16;
	height = 15;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	spacingX = 1;
	spacingY = 1;
	digitsMaxRow = 13;

	ChangeValue(alphaLetter);
}

void ABCsAlphaNum::ChangeValue(int num){
	int pos = NULL;
	switch (num){
	case 0:
		pos = ZERO;
		break;
	case 1:
		pos = ONE;
		break;
	case 2:
		pos = TWO;
		break;
	case 3:
		pos = THREE;
		break;
	case 4:
		pos = FOUR;
		break;
	case 5:
		pos = FIVE;
		break;
	case 6:
		pos = SIX;
		break;
	case 7:
		pos = SEVEN;
		break;
	case 8:
		pos = EIGHT;
		break;
	case 9:
		pos = NINE;
		break;
	}
	
	int row = 4;
	pos -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * pos);
	srcY = yIni + ((height + spacingY) * row);
}


void ABCsAlphaNum::ChangeValue(char lletres){
	int pos = -1;
	switch (lletres){
	case 'A': pos = A;
		break;
	case 'B': pos = B;
		break;
	case 'C': pos = C;
		break;
	case 'D': pos = D;
		break;
	case 'E': pos = E;
		break;
	case 'F': pos = F;
		break;
	case 'G': pos = G;
		break;
	case 'H': pos = H;
		break;
	case 'I': pos = I;
		break;
	case 'J': pos = J;
		break;
	case 'K': pos = K;
		break;
	case 'L': pos = L;
		break;
	case 'M': pos = M;
		break;
	case 'N': pos = N;
		break;
	case 'O': pos = O;
		break;
	case 'P': pos = P;
		break;
	case 'Q': pos = Q;
		break;
	case 'R': pos = R;
		break;
	case 'S': pos = S;
		break;
	case 'T': pos = T;
		break;
	case 'U': pos = U;
		break;
	case 'V': pos = V;
		break;
	case 'W': pos = W;
		break;
	case 'X': pos = X;
		break;
	case 'Y': pos = Y;
		break;
	case 'Z': pos = Z;
		break;

	case 'a': pos = a;
		break;
	case 'b': pos = b;
		break;
	case 'c': pos = c;
		break;
	case 'd': pos = d;
		break;
	case 'e': pos = e;
		break;
	case 'f': pos = f;
		break;
	case 'g': pos = g;
		break;
	case 'h': pos = h;
		break;
	case 'i': pos = i;
		break;
	case 'j': pos = j;
		break;
	case 'k': pos = k;
		break;
	case 'l': pos = l;
		break;
	case 'm': pos = m;
		break;
	case 'n': pos = n;
		break;
	case 'o': pos = o;
		break;
	case 'p': pos = p;
		break;
	case 'q': pos = q;
		break;
	case 'r': pos = r;
		break;
	case 's': pos = s;
		break;
	case 't': pos = t;
		break;
	case 'u': pos = u;
		break;
	case 'v': pos = v;
		break;
	case 'w': pos = w;
		break;
	case 'x': pos = x;
		break;
	case 'y': pos = y;
		break;
	case 'z': pos = z;
		break;

	case '!': pos = EXCLAMATION;
		break;

	default:
		break;
	}

	int row = 0;
	if (pos >= N && pos <= Z)
		row = 1;
	else if (pos >= a && pos <= m)
		row = 2;
	else if (pos >= n && pos <= z)
		row = 3;
	else if (pos >= EXCLAMATION){
		row = 5;
		// Canvis per a l'spritesheet posat.
		pos += 3;
	}

	if (row > 0)
		pos -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * pos);
	srcY = yIni + ((height + spacingY) * row);
}


void ABCsAlphaNum::Render(){
	videoManager->renderTexture(idImg, srcX, srcY, width, height, scaleX, scaleY, posX, posY, 0, 0, 0);
}