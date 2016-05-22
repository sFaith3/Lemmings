#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//! ResourceManager class
/*!
Handles the load and management of the graphics in the game.
*/
class ResourceManager{
public:

	//! Destructor.
	~ResourceManager();

	//! Gets Singleton instance
	/*!
	\return Instance of ResourceManager (Singleton).
	*/
	static ResourceManager* getInstanceResourceManager();


	/*--- SURFACE ---*/

	//! Create a new surface graphic to the ResourceManager
	/*!
	\param name for the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name, SDL_Surface* newSurface);


	//! Create a new surface graphic to the ResourceManager
	/*!
	\param name for the graphic
	\param width Width for the graphic
	\param height Height for the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name, SDL_Surface* newSurface, Uint16 width, Uint16 height);


	//! Deletes a graphic from the ResourceManager map
	/*!
	\param file Filepath to the graphic
	*/
	void removeGraphic(const char* file);


	//! Deletes a graphic from the ResourceManager map
	/*!
	\param ID to the graphic
	*/
	void removeGraphic(Sint32 ID);


	//! Gets the graphic ID
	/*!
	\param file Filepath to the graphic
	\return ID of the graphic
	*/
	Sint32 getGraphicID(const char* file);


	//! Gets the graphic path given an ID graphic
	/*!
	\param ID of the graphic
	\return Filepath to the graphic
	*/
	string getGraphicPathByID(Sint32 ID);


	//! Returns width and Height of a Surface
	/*!
	*	\param img ID graphic
	*	\param width Return variable for width value
	*	\param height Return variable for height value
	*/
	void getGraphicSize(Sint32 img, int &width, int &height);


	//! Returns width of a graphic
	/*!
	*	\param img ID graphic
	* 	\return Width of graphic
	*/
	int getGraphicWidth(Sint32 img);


	//! Returns Height of a graphic
	/*!
	*	\param img ID graphic
	*  \return Height of graphic
	*/
	int getGraphicHeight(Sint32 img);


	//! Return the RGB color of the surface
	/*!
	\param ID ID of the graphic
	\param color_value From 0 to 255, in R, G, B
	*/
	void getColorGraphic(Sint32 ID, Uint8* R, Uint8* G, Uint8* B);


	//! Returns the SDL_Surface of the graphic
	/*!
	\param ID ID of the graphic
	\return SDL_Surface
	*/
	SDL_Surface* getGraphicByID(Sint32 ID);


	//! Change general Alpha value to paint a concrete surface
	/*!
	\param ID ID of the graphic
	\param alpha_value From SDL_ALPHA_TRANSPARENT(0) to SDL_ALPHA_OPAQUE(255)
	*/
	void setAlphaGraphic(Sint32 ID, Uint8 alpha_value);


	bool GetAlphaXY(int surface, int x, int y);

	void EditSurfaceMuroBullet(int ID, int x, int y);

	void EditSurfaceMuroEnemy(int ID, int x, int y, int w, int h);

	void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
	

	//! Change general Color value to paint a concrete surface
	/*!
	\param ID ID of the graphic
	\param color_value From 0 to 255, in R, G, B
	*/
	void setColorGraphic(Sint32 ID, Uint8 R, Uint8 G, Uint8 B);


	//! Prints the path to loaded graphics
	void printLoadedGraphics();
	/*--- END SURFACE ---*/


	/*--- TEXTURE ---*/

	//! Create a new texture to the ResourceManager
	/*!
	\param name for the texture
	\return -1 if there's an error when loading
	*/
	Sint32 createTexture(const char* name, SDL_Texture* newTexture);

	
	//! Deletes a texture from the ResourceManager mapTextures
	/*!
	\param file Filepath to the texture
	*/
	void removeTexture(const char* file);


	//! Deletes a texture from the ResourceManager mapTextures
	/*!
	\param ID to the texture
	*/
	void removeTexture(Sint32 ID);


	//! Gets the texture ID
	/*!
	\param file Filepath to the texture
	\return ID of the texture
	*/
	Sint32 getTextureID(const char* file);


	//! Gets the texture path given an ID texture
	/*!
	\param ID of the texture
	\return Filepath to the texture
	*/
	string getTexturePathByID(Sint32 ID);


	//! Return the RGB color of the texture
	/*!
	\param ID ID of the texture
	\param color_value From 0 to 255, in R, G, B
	*/
	void getColorTexture(Sint32 ID, Uint8* R, Uint8* G, Uint8* B);


	//! Returns the SDL_Texture of the texture
	/*!
	\param ID ID of the texture
	\return SDL_Texture
	*/
	SDL_Texture* getTextureByID(Sint32 ID);


	//! Change general Alpha value to paint a concrete texture
	/*!
	\param ID ID of the texture
	\param alpha_value From SDL_ALPHA_TRANSPARENT(0) to SDL_ALPHA_OPAQUE(255)
	*/
	void setAlphaTexture(Sint32 ID, Uint8 alpha_value);


	//! Change general Color value to paint a concrete texture
	/*!
	\param ID ID of the texture
	\param color_value From 0 to 255, in R, G, B
	*/
	void setColorTexture(Sint32 ID, Uint8 R, Uint8 G, Uint8 B);


	//! Prints the path to loaded graphics
	void printLoadedTextures();
	/*--- END TEXTURE ---*/


	/*--- AUDIO ---*/

	//! Adds a audio to the ResourceManager 
	/*!
	\param file Filepath to the audio
	\return -1 if there's an error when loading
	*/
	Sint32 addAudio(const char* file, Mix_Chunk* sound);

	//! Deletes a mixer from the ResourceManager mapAudios
	/*!
	\param ID to the audio
	*/
	void removeAudio(Sint32 ID);

	//! Gets the mixer ID
	/*!
	\param file Filepath to the mixer
	\return ID of the mixer
	*/
	Sint32 getAudioID(const char* file);

	//! Returns the Mix_Chunk of the mixer
	/*!
	\param ID ID of the mixer
	\return Mix_Chunk
	*/
	Mix_Chunk* getAudioByID(Sint32 ID);


	//! Prints the path to loaded graphics
	void printLoadedAudios();
	/*--- END AUDIO ---*/

protected:
	//! Constructor of an empty ResourceManager.
	ResourceManager();

private:

	/*--- SURFACE ---*/

	//! Adds a graphic to the ResourceManager 
	/*!
	\param file Filepath to the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 addGraphic(const char* file, SDL_Surface* newSurface);


	//! Searches in the ResourceManager and gets the graphic by its name. If it isn't there, loads it
	/*!
	\param file Filepath of the graphic
	\return SDL_Surface
	*/
	SDL_Surface* getGraphic(const char* file, SDL_Surface* newSurface);


	//! Searches the graphic in the vector and returns its ID
	/*!
	\param img SDL_Surface of the graphic
	\return ID of the graphic
	*/
	Sint32 searchGraphic(SDL_Surface* img);
	/*--- END SURFACE ---*/


	/*--- TEXTURE ---*/

	//! Adds a texture to the ResourceManager 
	/*!
	\param file Filepath to the texture
	\return -1 if there's an error when loading
	*/
	Sint32 addTexture(const char* file, SDL_Texture* newTexture);


	//! Searches in the ResourceManager and gets the texture by its name. If it isn't there, loads it
	/*!
	\param file Filepath of the texture
	\return SDL_Texture
	*/
	SDL_Texture* getTexture(const char* file, SDL_Texture* newTexture);


	//! Searches the texture in the vector and returns its ID
	/*!
	\param img SDL_Texture of the texture
	\return ID of the texture
	*/
	Sint32 searchTexture(SDL_Texture* img);
	/*--- END TEXTURE ---*/


	//! Searches the first NULL in mGraphicsVector and updates mFirstFreeSlotGraphics to store its position
	/*!
	\return Index of the first NULL in mGraphicsVector
	*/
	Uint32 updateFirstFreeSlotGraphic();

	//! Searches the first NULL in mTexturesVector and updates mFirstFreeSlotTextures to store its position
	/*!
	\return Index of the first NULL in mTexturesVector
	*/
	Uint32 updateFirstFreeSlotTexture();

	//! Searches the first NULL in mAudiosVector and updates mFirstFreeSlotAudio to store its position
	/*!
	\return Index of the first NULL in mAudiosVector
	*/
	Uint32 updateFirstFreeSlotAudio();


	vector<SDL_Surface*>		mGraphicsVector;		/*!<  Vector that stores Surfaces. Useful for sequential access*/
	vector<SDL_Texture*>		mTexturesVector;		/*!<  Vector that stores Textures. Useful for sequential access*/
	vector<Mix_Chunk*>			mAudiosVector;			/*!<  Vector that stores Mix_Chunks. Useful for sequential access*/


	map<string, Sint32>			mIDMapGraphics;					/*!<  Map that stores ID. Links strings to ID, useful for sequential access*/
	map<string, Sint32>			mIDMapTextures;					/*!<  Map that stores ID. Links strings to ID, useful for sequential access*/
	map<string, Sint32>			mIDMapAudios;					/*!<  Map that stores ID. Links strings to ID, useful for sequential access*/
	Sint32						mFirstFreeSlotGraphics;			/*!<  First free slot in the mGraphicsVector*/
	Sint32						mFirstFreeSlotTextures;			/*!<  First free slot in the mTexturesVector*/
	Sint32						mFirstFreeSlotAudios;			/*!<  First free slot int the mAudiosVector*/


	static ResourceManager*		pInstance;				/*!<  Singleton instance*/

};

#endif