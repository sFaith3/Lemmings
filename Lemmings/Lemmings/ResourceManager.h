#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Utils.h"


//! ResourceManager class
/*!
Handles the load and management of the graphics in the game.
*/
class ResourceManager
{
public:

	//! Destructor.
	~ResourceManager();

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



	void removeAudio(Sint32 ID);


	//! Gets the graphic ID
	/*!
	\param file Filepath to the graphic
	\return ID of the graphic
	*/
	Sint32 getGraphicID(const char* file);


	Sint32 getAudioID(const char* file);



	//! Gets the graphic path given an ID graphic
	/*!
	\param ID of the graphic
	\return Filepath to the graphic
	*/
	string getGraphicPathByID(Sint32 ID);


	//! Returns width and Height of a Surface
	/*!
	*	\param img ID texture
	*	\param width Return variable for width value
	*	\param height Return variable for height value
	*/
	void getGraphicSize(Sint32 img, int &width, int &height);

	//! Returns width of a Surface
	/*!
	*	\param img ID texture
	* 	\return Width of Texture
	*/
	int getGraphicWidth(Sint32 img);

	//! Returns Height of a Texture
	/*!
	*	\param img ID texture
	*  \return Height of Texture
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
	SDL_Texture* getGraphicByID(Sint32 ID);
	
	Mix_Chunk* getAudioByID(Sint32 ID);

	//! Change general Alpha value to paint a concrete surface
	/*!
	\param ID ID of the graphic
	\param alpha_value From SDL_ALPHA_TRANSPARENT(0) to SDL_ALPHA_OPAQUE(255)
	*/
	void setAlphaGraphic(Sint32 ID, Uint8 alpha_value);


	bool  GetAlphaXY(int surface, int x, int y);

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

	//! Create a new surface graphic to the ResourceManager
	/*!
	\param name for the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name);

	//! Create a new surface graphic to the ResourceManager
	/*!
	\param name for the graphic
	\param width Width for the graphic
	\param height Height for the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name, Uint16 width, Uint16 height);

	//! Gets Singleton instance
	/*!
	\return Instance of ResourceManager (Singleton).
	*/
	static ResourceManager* getInstanceResourceManager();

protected:
	//! Constructor of an empty ResourceManager.
	ResourceManager();

private:

	//! Adds a graphic to the ResourceManager 
	/*!
	\param file Filepath to the graphic
	\return -1 if there's an error when loading
	*/
	Sint32 addGraphic(const char* file);


	Sint32 addAudio(const char* file);

	//! Searches in the ResourceManager and gets the graphic by its name. If it isn't there, loads it
	/*!
	\param file Filepath of the graphic
	\return SDL_Surface
	*/
	SDL_Surface* getGraphic(const char* file);

	//! Searches the Texture in the vector and returns its ID
	/*!
	\param img SDL_Surface of the graphic
	\return ID of the Texture
	*/
	Sint32 searchGraphic(SDL_Surface* img);

	//! Searches the first NULL in mGraphicsVector and updates mFirstFreeSlot to store its position
	/*!
	\return Index of the first NULL in mGraphicsVectorTexture
	*/
	Uint32 updateFirstFreeSlotGraphic();

	Uint32 updateFirstFreeSlotAudio();

	vector<SDL_Surface*>		mGraphicsVector;	/*!<  Vector that stores Surfaces. Useful for sequential access*/
	vector<SDL_Texture*>		mTextureVector;	/*!<  Vector that stores Surfaces. Useful for sequential access*/

	map<string, Sint32>		mIDMap;			/*!<  Map that stores ID. Links strings to ID, useful for sequential access*/
	Sint32					mFirstFreeSlot;		/*!<  First free slot in the mGraphicsVector*/
	Sint32					mFirstFreeSlotAudio;

	vector<Mix_Chunk*>		mAudioVector;	/*!<  Vector that stores Surfaces. Useful for sequential access*/

	static ResourceManager*			pInstance;		/*!<  Singleton instance*/

};

#endif
