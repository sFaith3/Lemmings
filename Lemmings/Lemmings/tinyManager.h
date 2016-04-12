#ifndef TINYMANAGER_H
#define TINYMANAGER_H

#include "TinyXML\tinyxml.h"
#include "SDL\VideoManager.h"

class tinyManager
{
private:
	tinyManager();

	static tinyManager* tInstance;

	VideoManager* vManager;

public:
	~tinyManager();

	static tinyManager* getInstanceTinyManager();

	Sint32 loadTMX(const char* fileTMX, const char* tiles);
};

#endif