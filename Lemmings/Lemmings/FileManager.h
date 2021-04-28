#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class FileManager
{
private:
	FileManager();

	static FileManager* fInstance; /*!<	Singleton instance*/

	vector <map<string, string> > data; // Data of the readed file.

public:
	~FileManager();

	//! Gets Singleton instance.
	static FileManager* getInstanceFile();

	// Methods to save the data in a std::map to treat it then,
	void Read(const char* file);
	void Read(const char* file, int line);

	int SizeFile(fstream reader);
	int ReadContents(vector<string> &words, fstream &in); // Read all data to save them in a vector to treat it then.

	string GetValueFromData(string key); // Get the value of the correspondent key in the std::map.
};

#endif