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

	Sint32 addGraphic(const char* file);
	Sint32 getGraphicID(const char* file);
	Sint32 addTexture(const char* file);
	Sint32 getTextureID(const char* file);
	
	int getTime();
	float getDeltaTime();

	void setCursorRelative(bool active);

	void renderGraphic(int img, int srcPosX, int srcPosY, int width, int height, int dstPosX, int dstPosY);
	void renderTexture(int img, int srcPosX, int srcPosY, int srcWidth, int srcHeight, int dstPosX, int dstPosY, double angle, int centerX, int centerY);
	
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