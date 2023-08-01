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

	vector<map<string, string>> data; // Data of the readed file.

public:
	~FileManager();

	//! Gets Singleton instance.
	static FileManager* getInstanceFile();

	// Methods to save the data in a std::map to treat it later.
	void Read(const char* file);
	void ReadLines(fstream &reader);
	void Read(const char* file, int numLines);
	void ReadLines(fstream &reader, int numLines);

	int SizeFile(fstream &reader);
	int ReadContent(vector<string> &words, fstream &in); // Read all data to save them in a vector to treat it later.

	string GetValueFromData(string key); // Get the value of the correspondent key in the std::map.
};

#endif