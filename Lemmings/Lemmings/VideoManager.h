#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "SDL.h"

class VideoManager
{
private:
	VideoManager();

	static VideoManager* vInstance;

	float deltaTime;
	int lastTime;
	float msFrame; 

public:
	~VideoManager();

	static VideoManager* getInstanceVideo();

	Sint32 graphicID(const char* file);
	void renderTexture(int img, int src_posX, int src_posY, int src_width, int src_height, int dst_posX, int dst_posY, double angle, int centerX, int centerY);
	
	void clearScreen(unsigned int color_key);
	void updateScreen();

	int getTime();
	float getDeltaTime();
	void UpdateTime();
	void waitTime(int ms);

	void setCursorRelative(bool active);

	void close();

	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Renderer* renderer;
};

#endif