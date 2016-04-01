#include "ResourceManager.h"

#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>


ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::ResourceManager(){
	mFirstFreeSlotGraphics = -1;
	mFirstFreeSlotTextures = -1;
	mFirstFreeSlotAudios = -1;
}

ResourceManager::~ResourceManager(){

}

ResourceManager* ResourceManager::getInstanceResourceManager(){
	if (pInstance == NULL){

		pInstance = new ResourceManager();
	}

	return pInstance;

}


/*--- SURFACE ---*/

Sint32 ResourceManager::createGraphic(const char* name, SDL_Surface* newSurface){
	return addGraphic(name, newSurface);
}


Sint32 ResourceManager::createGraphic(const char* name, SDL_Surface* newSurface, Uint16 width, Uint16 height){
	Sint32 pos = addGraphic(name, newSurface);
	if (pos != -1){
		mGraphicsVector[pos]->h = height;
		mGraphicsVector[pos]->w = width;
	}
	return pos;

}


Sint32 ResourceManager::addGraphic(const char* file, SDL_Surface* newSurface){
	Sint32 pos = -1;
	if (mFirstFreeSlotGraphics != -1){
		mGraphicsVector[mFirstFreeSlotGraphics] = newSurface;
		mIDMapGraphics.emplace(file, mFirstFreeSlotGraphics);
		pos = mFirstFreeSlotGraphics;
		updateFirstFreeSlotGraphic();
	}
	else{
		mGraphicsVector.push_back(newSurface);
		pos = mGraphicsVector.size() - 1;
		mIDMapGraphics.emplace(file, pos);
	}
	return pos;

}


void ResourceManager::removeGraphic(const char* file){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMapGraphics.begin(); it != mIDMapGraphics.end(); it++){
		if (it->first == file){
			pos = it->second;
			mIDMapGraphics.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_FreeSurface(mGraphicsVector[pos]);
		mGraphicsVector[pos] = NULL;
		if (pos < mFirstFreeSlotGraphics)
			mFirstFreeSlotGraphics = pos;
	}

}


void ResourceManager::removeGraphic(Sint32 ID){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMapGraphics.begin(); it != mIDMapGraphics.end(); it++){
		if (it->second == ID){
			pos = it->second;
			mIDMapGraphics.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_FreeSurface(mGraphicsVector[pos]);
		mGraphicsVector[pos] = NULL;
		if (pos < mFirstFreeSlotGraphics)
			mFirstFreeSlotGraphics = pos;
	}

}


Sint32 ResourceManager::getGraphicID(const char* file, SDL_Surface* newSurface){
	for (map<string, Sint32>::iterator it = mIDMapGraphics.begin(); it != mIDMapGraphics.end(); it++){
		if (it->first == file)
			return it->second;
	}
	return addGraphic(file, newSurface);

}


string ResourceManager::getGraphicPathByID(Sint32 ID){
	for (map<string, Sint32>::iterator it = mIDMapGraphics.begin(); it != mIDMapGraphics.end(); it++){
		if (it->second == ID)
			return (string)it->first;
	}
	return "Error";

}


void ResourceManager::getGraphicSize(Sint32 img, int &width, int &height){
	width = mGraphicsVector[img]->w;
	height = mGraphicsVector[img]->h;
}


int ResourceManager::getGraphicWidth(Sint32 img){
	return mGraphicsVector[img]->w;
}


int ResourceManager::getGraphicHeight(Sint32 img){
	return mGraphicsVector[img]->h;
}


void ResourceManager::getColorGraphic(Sint32 ID, Uint8* R, Uint8* G, Uint8* B){
	SDL_GetSurfaceColorMod(mGraphicsVector[ID], R, G, B);
}


SDL_Surface* ResourceManager::getGraphicByID(Sint32 ID){
	return mGraphicsVector[ID];
}


void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value){
	SDL_SetSurfaceAlphaMod(mGraphicsVector[ID], alpha_value);
}


Sint32 ResourceManager::searchGraphic(SDL_Surface* img){
	for (unsigned int i = 0; i < mGraphicsVector.size(); i++){
		if (mGraphicsVector[i] == img){
			return i;
		}
	}
	return -1;
}


//Comprova si el píxel no té molta transparència en la posisió X-Y de la surface ID
bool  ResourceManager::GetAlphaXY(int ID, int x, int y){
	SDL_Surface* surface = mGraphicsVector[ID];

	if (x >= 0 && y >= 0 && x < surface->w && y < surface->h){
		if (SDL_MUSTLOCK(surface)){
			//Lock the surface
			SDL_LockSurface(surface);
		}
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		Uint32 pixelColor = 0;

		switch (bpp){
		case 1:
			pixelColor = *p;
			break;
		case 2:
			pixelColor = *(Uint16*)p;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelColor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelColor = p[0] | p[1] << 8 | p[2] << 16;
			break;
		case 4:
			pixelColor = *(Uint32*)p;
			break;
		}

		Uint8 red, green, blue, alpha;
		SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);
		if (SDL_MUSTLOCK(surface))
			SDL_UnlockSurface(surface);
		return alpha > 220;
	}
	return false;
}


//Modifica l'alpha d'alguns píxels per a crear un efecte d'explosió
void ResourceManager::EditSurfaceMuroBullet(int ID, int x, int y){
	SDL_Surface* surface = mGraphicsVector[ID];
	//If the surface must be locked
	if (SDL_MUSTLOCK(surface)){
		//Lock the surface
		SDL_LockSurface(surface);
	}

	//Modificar l'alpha dels píxels
	Uint32 pixel = SDL_MapRGBA(surface->format, 0, 0, 0, 0);

	//Crea una espècie de rombe corbat, que es va esvaint en funció dels randoms
	for (int i = -10; i < 10; i++){
		for (int j = -20; j < 20; j++){

			if (x + i >= 0 && y + j >= 0 && x + i < surface->w && y + j < surface->h){
				if (abs(i * j) < 25 || (rand() % 2 == 0 && abs(i * j) < 100) || (abs(i * j) < 150 && rand() % 8 == 0))
					put_pixel32(surface, x + i, y + j, pixel);
			}
		}
	}

	//Unlock surface
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}


//Modifica l'alpha d'alguns píxels per a crear un efecte d'explosió
void ResourceManager::EditSurfaceMuroEnemy(int ID, int x, int y, int w, int h){
	SDL_Surface* surface = mGraphicsVector[ID];
	//If the surface must be locked
	if (SDL_MUSTLOCK(surface)){
		//Lock the surface
		SDL_LockSurface(surface);
	}

	//Modifica l'alpha dels píxels
	Uint32 pixel = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			if (x + i >= 0 && y + j >= 0 && x + i < surface->w && y + j < surface->h)
				put_pixel32(surface, x + i, y + j, pixel);

		}
	}

	//Unlock surface
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}


void ResourceManager::put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel){
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Set the pixel
	pixels[(y * surface->w) + x] = pixel;
}


void ResourceManager::setColorGraphic(Sint32 ID, Uint8 R, Uint8 G, Uint8 B){
	SDL_SetSurfaceColorMod(mGraphicsVector[ID], R, G, B);
}


void ResourceManager::printLoadedGraphics(){
	for (map<string, Sint32>::iterator it = mIDMapGraphics.begin(); it != mIDMapGraphics.end(); it++){
		cout << it->first << endl;
	}
}


Uint32 ResourceManager::updateFirstFreeSlotGraphic(){
	mFirstFreeSlotGraphics = -1;
	for (unsigned int i = 0; i < mGraphicsVector.size(); i++){
		if (mGraphicsVector[i] == NULL){
			mFirstFreeSlotGraphics = i;
			break;
		}
	}
	return mFirstFreeSlotGraphics;

}
/*--- END SURFACE ---*/


/*--- TEXTURE ---*/
Sint32 ResourceManager::createTexture(const char* name, SDL_Texture* newTexture){
	return addTexture(name, newTexture);
}


Sint32 ResourceManager::addTexture(const char* file, SDL_Texture* newTexture){
	Sint32 pos = -1;
	if (mFirstFreeSlotTextures != -1){
		mTexturesVector[mFirstFreeSlotTextures] = newTexture;
		mIDMapTextures.emplace(file, mFirstFreeSlotTextures);
		pos = mFirstFreeSlotTextures;
		updateFirstFreeSlotTexture();
	}
	else{
		mTexturesVector.push_back(newTexture);
		pos = mTexturesVector.size() - 1;
		mIDMapTextures.emplace(file, pos);
	}
	return pos;

}


void ResourceManager::removeTexture(const char* file){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMapTextures.begin(); it != mIDMapTextures.end(); it++){
		if (it->first == file){
			pos = it->second;
			mIDMapTextures.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_DestroyTexture(mTexturesVector[pos]);
		mTexturesVector[pos] = NULL;
		if (pos < mFirstFreeSlotTextures)
			mFirstFreeSlotTextures = pos;
	}

}


void ResourceManager::removeTexture(Sint32 ID){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMapTextures.begin(); it != mIDMapTextures.end(); it++){
		if (it->second == ID){
			pos = it->second;
			mIDMapTextures.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_DestroyTexture(mTexturesVector[pos]);
		mTexturesVector[pos] = NULL;
		if (pos < mFirstFreeSlotTextures)
			mFirstFreeSlotTextures = pos;
	}

}


SDL_Texture* ResourceManager::getTexture(const char* file, SDL_Texture* newTexture){
	map<string, Sint32>::iterator it = mIDMapTextures.find(file);

	if (it != mIDMapTextures.end()){
		Sint32 pos = it->second;
		return mTexturesVector[pos];
	}
	return mTexturesVector[addTexture(file, newTexture)];

}


void ResourceManager::getColorTexture(Sint32 ID, Uint8* R, Uint8* G, Uint8* B){
	SDL_GetTextureColorMod(mTexturesVector[ID], R, G, B);
}


SDL_Texture* ResourceManager::getTextureByID(Sint32 ID){
	return mTexturesVector[ID];
}


void ResourceManager::setAlphaTexture(Sint32 ID, Uint8 alpha_value){
	SDL_SetTextureAlphaMod(mTexturesVector[ID], alpha_value);
}


Sint32 ResourceManager::getTextureID(const char* file, SDL_Texture* newTexture){
	for (map<string, Sint32>::iterator it = mIDMapTextures.begin(); it != mIDMapTextures.end(); it++){
		if (it->first == file)
			return it->second;
	}
	return addTexture(file, newTexture);

}


string ResourceManager::getTexturePathByID(Sint32 ID){
	for (map<string, Sint32>::iterator it = mIDMapTextures.begin(); it != mIDMapTextures.end(); it++){
		if (it->second == ID)
			return (string)it->first;
	}
	return "Error";

}


Sint32 ResourceManager::searchTexture(SDL_Texture* img){
	for (unsigned int i = 0; i < mTexturesVector.size(); i++){
		if (mTexturesVector[i] == img){
			return i;
		}
	}
	return -1;

}


void ResourceManager::setColorTexture(Sint32 ID, Uint8 R, Uint8 G, Uint8 B){
	SDL_SetTextureColorMod(mTexturesVector[ID], R, G, B);
}


void ResourceManager::printLoadedTextures(){
	for (map<string, Sint32>::iterator it = mIDMapTextures.begin(); it != mIDMapTextures.end(); it++){
		cout << it->first << endl;
	}
}


Uint32 ResourceManager::updateFirstFreeSlotTexture(){
	mFirstFreeSlotTextures = -1;
	for (unsigned int i = 0; i < mTexturesVector.size(); i++){
		if (mTexturesVector[i] == NULL){
			mFirstFreeSlotTextures = i;
			break;
		}
	}
	return mFirstFreeSlotTextures;

}
/*--- END TEXTURE ---*/


/*--- AUDIO ---*/
Sint32 ResourceManager::addAudio(const char* file){
	Mix_Chunk* sound = Mix_LoadWAV(file);
	if (sound == NULL){
		cout << "Failed to load sound effect! SDL_mixer Error:" << Mix_GetError() << endl;
		return -1;
	}
	Sint32 pos = -1;
	if (mFirstFreeSlotAudios != -1){
		mAudiosVector[mFirstFreeSlotAudios] = sound ;
		mIDMapAudios.emplace(file, mFirstFreeSlotAudios);
		pos = mFirstFreeSlotAudios;
		updateFirstFreeSlotAudio();
	}
	else{
		mAudiosVector.push_back(sound);
		pos = mAudiosVector.size() - 1;
		mIDMapAudios.emplace(file, pos);
	}
	return pos;
}


void ResourceManager::removeAudio(Sint32 ID){
	Mix_FreeChunk(mAudiosVector[ID]);
	mAudiosVector[ID] = NULL;
	if (ID < mFirstFreeSlotAudios)
		mFirstFreeSlotAudios = ID;
	
}


Sint32 ResourceManager::getAudioID(const char* file){
	for (map<string, Sint32>::iterator it = mIDMapAudios.begin(); it != mIDMapAudios.end(); it++){
		if (it->first == file)
			return it->second;
	}
	return addAudio(file);
}


Mix_Chunk* ResourceManager::getAudioByID(Sint32 ID){
	return mAudiosVector[ID];
}


void ResourceManager::printLoadedAudios(){
	for (map<string, Sint32>::iterator it = mIDMapAudios.begin(); it != mIDMapAudios.end(); it++){
		cout << it->first << endl;
	}
}


Uint32 ResourceManager::updateFirstFreeSlotAudio(){
	mFirstFreeSlotAudios = -1;
	for (unsigned int i = 0; i < mAudiosVector.size(); i++){
		if (mAudiosVector[i] == NULL){
			mFirstFreeSlotAudios = i;
			break;
		}
	}
	return mFirstFreeSlotAudios;
}
/*--- END AUDIO ---*/