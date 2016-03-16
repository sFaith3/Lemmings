#include "VideoManager.h"
#include "ResourceManager.h"
#include "SDL_image.h"
#include "Utils.h"
#include <iostream>

VideoManager* VideoManager::vInstance = NULL;

VideoManager::VideoManager(){
	gWindow = NULL;
	gScreenSurface = NULL;
	renderer = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("Examen SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
	else{
		//Create renderer for window
		renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
			cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
		else{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
				cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
		}
	}

	msFrame = (float)FPS / 1000.0f;
}

VideoManager::~VideoManager(){

}

VideoManager* VideoManager::getInstanceVideo(){
	if (vInstance == NULL)
		vInstance = new VideoManager();

	return vInstance;
}

void VideoManager::setCursorRelative(bool active){
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

Sint32 VideoManager::graphicID(const char* file){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
		cout << "Unable to load image %s! SDL_image Error: " << file << " " << IMG_GetError() << endl;
	else{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
			cout << "Unable to create texture from %s! SDL Error: " << file << " " << SDL_GetError() << endl;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return ResourceManager::getInstanceResourceManager()->getGraphicID(file, newTexture);
}

void VideoManager::renderTexture(int img, int src_posX, int src_posY, int src_width, int src_height, int dst_posX, int dst_posY, double angle, int centerX, int centerY){
	SDL_Rect r, rectAux;
	rectAux.x = src_posX;
	rectAux.y = src_posY;
	rectAux.w = src_width;
	rectAux.h = src_height;
	r.x = dst_posX;
	r.y = dst_posY;
	r.w = src_width;
	r.h = src_height;
	SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getGraphicByID(img);

	SDL_Point center;

	center.x = centerX;
	center.y = centerY;

	SDL_RenderCopyEx(renderer, origin, &rectAux, &r, angle, &center, SDL_FLIP_NONE);
}

void VideoManager::clearScreen(unsigned int color_key){
	//Clear screen
	SDL_SetRenderDrawColor(renderer, color_key, color_key, color_key, color_key);
	SDL_RenderClear(renderer);
}
void VideoManager::updateScreen(){
	//Update screen
	SDL_RenderPresent(renderer);
}

int VideoManager::getTime(){
	return SDL_GetTicks();
}

void VideoManager::waitTime(int ms){
	deltaTime = 0;
	lastTime = -1;
	SDL_Delay(ms);
	lastTime = getTime();
}

void VideoManager::close(){
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

float VideoManager::getDeltaTime(){
	return deltaTime;
}

void VideoManager::UpdateTime(){
	if (lastTime != -1){
		int currentTime = getTime();
		deltaTime = (float)(currentTime - lastTime) / 1000;

		//Para evitar que el input del raton se ralentize, se elima la restriccion de FPS.
		if (deltaTime < msFrame){
			//waitTime((msFrame - deltaTime) * 1000);
			//deltaTime = msFrame;
		}
		lastTime = currentTime;
	}
}