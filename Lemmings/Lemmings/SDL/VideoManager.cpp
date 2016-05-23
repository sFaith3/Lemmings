#include "VideoManager.h"
#include "ResourceManager.h"
#include "..\Utils.h"

VideoManager* VideoManager::vInstance = NULL;

VideoManager::VideoManager(){
	gWindow = NULL;
	gScreenSurface = NULL;
	gScreenRenderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);

	gWindow = SDL_CreateWindow("Lemmings", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
	else{
		if (!texture){
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			if (gScreenSurface == NULL)
				cout << "Window surface could not be created! SDL Error: " << SDL_GetError() << endl;
		}
		else{
			//Create gScreenRenderer for window
			gScreenRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gScreenRenderer == NULL)
				cout << "gScreenRenderer could not be created! SDL Error: " << SDL_GetError() << endl;
			else{
				//Initialize gScreenRenderer color
				SDL_SetRenderDrawColor(gScreenRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
			}
		}
	}

	deltaTime = 0.0f;
	lastTime = 0;
	msFrame = FPS / 1000.0f;
}

VideoManager::~VideoManager(){

}


VideoManager* VideoManager::getInstanceVideo(){
	if (vInstance == NULL)
		vInstance = new VideoManager();

	return vInstance;
}


Sint32 VideoManager::addGraphic(const char* file){
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* surfaceFormatInfo = gScreenSurface;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL){
		cout << "Unable to load image " << file << "! SDL_image Error: " << IMG_GetError() << endl;
		return -1;
	}

	SDL_SetSurfaceBlendMode(surfaceFormatInfo, SDL_BLENDMODE_BLEND);
	//Convert surface to screen format
	// Save Alpha values from surface info
	Uint32 Old_Amask = surfaceFormatInfo->format->Amask;
	Uint32 Old_Aloss = surfaceFormatInfo->format->Aloss;
	Uint32 Old_Ashift = surfaceFormatInfo->format->Ashift;
	// Force Alpha values
	surfaceFormatInfo->format->Amask = 0xFF000000;
	surfaceFormatInfo->format->Aloss = 0;
	surfaceFormatInfo->format->Ashift = 24;
	// Convert to screen format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, surfaceFormatInfo->format, NULL);
	// Restore alpha values for surface info
	surfaceFormatInfo->format->Amask = (Uint8)Old_Amask;
	surfaceFormatInfo->format->Aloss = (Uint8)Old_Aloss;
	surfaceFormatInfo->format->Ashift = (Uint8)Old_Ashift;
	if (optimizedSurface == NULL){
		cout << "Unable to optimize image " << file << "! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return ResourceManager::getInstanceResourceManager()->createGraphic(file, optimizedSurface);
}

Sint32 VideoManager::getGraphicID(const char* file){
	Sint32 id = ResourceManager::getInstanceResourceManager()->getGraphicID(file);
	if (id != -1)
		return id;

	return addGraphic(file);
}

Sint32 VideoManager::addTexture(const char* file){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
		cout << "Unable to load image %s! SDL_image Error: " << file << " " << IMG_GetError() << endl;
	else{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gScreenRenderer, loadedSurface);
		if (newTexture == NULL)
			cout << "Unable to create texture from %s! SDL Error: " << file << " " << SDL_GetError() << endl;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return ResourceManager::getInstanceResourceManager()->createTexture(file, newTexture);

}

Sint32 VideoManager::getTextureID(const char* file){
	if (file == NULL)
		return -1;

	int id = ResourceManager::getInstanceResourceManager()->getTextureID(file);
	if (id != -1)
		return id;

	return addTexture(file);
}


int VideoManager::getTime(){
	return SDL_GetTicks();
}


void VideoManager::setCursorRelative(bool active){
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}


void VideoManager::renderGraphic(int img, int srcPosX, int srcPosY, int width, int height, int dstPosX, int dstPosY){
	SDL_Rect rectAux, r;
	rectAux.x = srcPosX;
	rectAux.y = srcPosY;
	rectAux.w = width;
	rectAux.h = height;
	r.x = dstPosX;
	r.y = dstPosY;
	r.w = width;
	r.h = height;
	
	SDL_Surface *origin = ResourceManager::getInstanceResourceManager()->getGraphicByID(img);

	SDL_BlitSurface(origin, &rectAux, gScreenSurface, &r);
}

void VideoManager::renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY,int dstPosX, int dstPosY, double angle, int centerX, int centerY){
	SDL_Rect rectAux, r;
	rectAux.x = srcPosX;
	rectAux.y = srcPosY;
	rectAux.w = width;
	rectAux.h = height;
	r.x = (int)(dstPosX* scaleX);
	r.y = (int)(dstPosY* scaleY);
	r.w = (int)(width * scaleX);
	r.h = (int)(height * scaleY);

	SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getTextureByID(img);

	SDL_Point center;
	center.x = centerX;
	center.y = centerY;

	SDL_RenderCopyEx(gScreenRenderer, origin, &rectAux, &r, angle, &center, SDL_FLIP_NONE);
}

void VideoManager::renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY, int dstPosX, int dstPosY, double angle, int centerX, int centerY, SDL_RendererFlip flip){
	SDL_Rect rectAux, r;
	rectAux.x = srcPosX;
	rectAux.y = srcPosY;
	rectAux.w = width;
	rectAux.h = height;
	r.x = (int)(dstPosX* scaleX);
	r.y = (int)(dstPosY* scaleY);
	r.w = (int)(width * scaleX);
	r.h = (int)(height * scaleY);

	SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getTextureByID(img);

	SDL_Point center;
	center.x = centerX;
	center.y = centerY;

	SDL_RenderCopyEx(gScreenRenderer, origin, &rectAux, &r, angle, &center, flip);
}

void VideoManager::clearScreen(unsigned int color_key){
	if (!texture)
		SDL_FillRect(gScreenSurface, NULL, color_key);
	else{
		//Clear screen
		SDL_SetRenderDrawColor(gScreenRenderer, color_key, color_key, color_key, color_key);
		SDL_RenderClear(gScreenRenderer);
	}
}

void VideoManager::updateScreen(){
	if (!texture)
		SDL_UpdateWindowSurface(gWindow);
	else{
		//Update screen
		SDL_RenderPresent(gScreenRenderer);
	}
}


void VideoManager::updateTime(){
	if (lastTime != -1){
		int currentTime = getTime();
		deltaTime = (float)(currentTime - lastTime);
		if (!texture){
			//Per a evitar que l'input del ratolí es ralentitzi, s'ha d'eliminar la restricció de FPS.
			if (deltaTime < msFrame){
				waitTime((msFrame - deltaTime) * 1000.0f);
				deltaTime = msFrame;
			}
		}
		lastTime = currentTime;
	}
	//cout << deltaTime << endl;
}

void VideoManager::waitTime(int ms){
	deltaTime = 0;
	lastTime = -1;
	SDL_Delay(ms);
	lastTime = getTime();
}


void VideoManager::close(){
	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}