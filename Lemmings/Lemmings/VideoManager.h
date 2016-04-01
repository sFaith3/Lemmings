#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "SDL.h"

class VideoManager
{
private:
	VideoManager();

	static VideoManager* vInstance;

	bool texture = false;

	float deltaTime;
	int lastTime;
	float msFrame; 

public:
	~VideoManager();

	static VideoManager* getInstanceVideo();

	Sint32 getGraphicID(const char* file);
	Sint32 getTextureID(const char* file);
	
	int getTime();
	float getDeltaTime();

	void setCursorRelative(bool active);

	void renderGraphic(int img, int posX, int posY, int width, int height, int x0, int y0);
	void renderTexture(int img, int src_posX, int src_posY, int src_width, int src_height, int dst_posX, int dst_posY, double angle, int centerX, int centerY);
	
	void clearScreen(unsigned int color_key);
	void updateScreen();

	void updateTime();
	void waitTime(int ms);

	void close();

	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Renderer* gScreenRenderer;
};

#endif