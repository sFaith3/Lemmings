#include "Utils.h"
#include "SingletonManager.h"
#pragma once

class ABCsAlphaNum
{
private:
	VideoManager* videoManager;

	Sint32 idImg;

	int xIni, yIni; // Posició on comença la primera lletra/número de l'spritesheet.
	int width, height;
	float scaleX, scaleY;
	int spacingX, spacingY; // Espai entre dígit.
	int srcX, srcY; // Tros a agafar de l'spritesheet.
	int digitsMaxRow; // Valor més gran de dígits en una fila en tot l'spritesheet.

	enum ABCsAlphaNumEnum{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
		ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO,
		// Falten els caràcters/signes.
	};

public:
	ABCsAlphaNum(float scaleX, float scaleY, int alphaNumEnum);
	~ABCsAlphaNum();

	void Update(int num);
	void Update(string alpha);
	void Render(int x, int y);
};

