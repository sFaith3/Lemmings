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

	vector <map<string, string> > data;

public:
	~FileManager();

	//! Gets Singleton instance.
	static FileManager* getInstanceFile();

	void Read(const char* file);
	void Read(const char* file, int line);

	int CheckFile(fstream reader);
	int ReadContents(vector<string> &words, fstream &in);

	string GetValueFromData(string key);
};

#endif