#pragma once
#include "Utils.h"
#include "SingletonManager.h"


class ABCsAlphaNum
{
private:
	int posX, posY; // Where is rendered.
	Sint32 idImg;

	int xIni, yIni; // Position where the first spritesheet letter/number starts.
	int width, height;
	float scaleX, scaleY;
	int spacingX, spacingY; // Space between digits.
	int srcX, srcY; // Spritesheet piece to be taken.
	int digitsMaxRow; // Largest digit value in a row in the whole spritesheet.

	enum ABCsAlphaNumEnum{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
		ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO,
		EXCLAMATION, AT, HASH, DOLLAR, PERCENT
	};

	VideoManager* videoManager;

public:
	ABCsAlphaNum();
	~ABCsAlphaNum();

	void init(int x, int y, float scaleX, float scaleY, int alphaNum);
	void init(int x, int y, float scaleX, float scaleY, char alphaLetter);
	void render();

	void move(int x, int y);
	void changeValue(int num);
	void changeValue(char lletres);
};

