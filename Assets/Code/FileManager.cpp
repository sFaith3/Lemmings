#include "FileManager.h"
#include "SDL.h"

FileManager* FileManager::fInstance = NULL;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}


FileManager* FileManager::getInstanceFile(){
	if (fInstance == NULL){

		fInstance = new FileManager();
	}
	return fInstance;
}


void FileManager::Read(const char* name){
	data.clear();

	fstream reader;
	reader.open(name, ios::in);
	if (reader.is_open()){
		cout << "The file '" << name << "' has opened succesfully!" << endl;
		ReadLines(reader);
		reader.close();
	}
	else
		cout << "Unable to open the file '" << name << "'!" << endl;
}

void FileManager::ReadLines(fstream &reader)
{
	int i = 0;
	int pos = 0;
	string line = "";

	while (getline(reader, line, '\n')) {
		map<string, string> dataFile;
		dataFile.clear();

		bool lineReaded = false;
		while (!lineReaded) {
			while (line[i] != ' ') {
				if (i >= line.length() - 1) {
					lineReaded = true;
					break;
				}
				i++;
			}
			pos = i + 1;

			while (line[i] != '=') {
				if (i >= line.length() - 1) {
					lineReaded = true;
					break;
				}
				i++;
			}
			string key = line.substr(pos, i - pos);
			pos = i + 2;

			while (line[i] != ' ') {
				if (i >= line.length() - 1) {
					lineReaded = true;
					break;
				}
				i++;
				if (line[i] == '>') {
					lineReaded = true;
					break;
				}
			}
			i--;

			string value = line.substr(pos, i - pos);
			dataFile.insert(pair<string, string>(key, value));
		}
		data.push_back(dataFile);
	}
}

void FileManager::Read(const char* name, int numLines){
	data.clear();

	fstream reader;
	reader.open(name, ios::in);
	if (reader.is_open()){
		cout << "The file '" << name << "' has opened succesfully!" << endl;
		ReadLines(reader, numLines);		
		reader.close();
	}
	else
		cout << "Unable to open the file '" << name << "'!" << endl;
}

void FileManager::ReadLines(fstream &reader, int numLines)
{
	int i = 0;
	int pos = 0;
	string line = "";

	for (int currLine = 0; currLine < numLines; currLine++) {
		getline(reader, line, '\n');
		if (currLine == numLines - 1) {
			map<string, string> dataFile;
			dataFile.clear();

			bool lineReaded = false;
			while (!lineReaded) {
				while (line[i] != ' ') {
					if (i >= line.length() - 1) {
						lineReaded = true;
						break;
					}
					i++;
				}
				pos = i + 1;

				while (line[i] != '=') {
					if (i >= line.length() - 1) {
						lineReaded = true;
						break;
					}
					i++;
				}
				string key = line.substr(pos, i - pos);
				pos = i + 2;

				while (line[i] != ' ') {
					if (i >= line.length() - 1) {
						lineReaded = true;
						break;
					}
					i++;
					if (line[i] == '>') {
						lineReaded = true;
						break;
					}
				}
				i--;

				string value = line.substr(pos, i - pos);
				dataFile.insert(pair<string, string>(key, value));
			}
			data.push_back(dataFile);
		}
	}
}


int FileManager::SizeFile(fstream &reader){
	reader.seekg(0, reader.end); // From the initial position 0, where the pointer fstream is initially located, to the last data in the file.
	int size = static_cast<int>(reader.tellg()); // 'tellg' returns the position of the fstream 'reader', to which it is pointing.
	reader.seekg(0, reader.beg); // Put the 'reader' pointer back to the top of everything.

	return size;
}

int FileManager::ReadContent(vector<string> &words, fstream &in){
	int i = -1;
	while (!in.eof()){
		i++;
		in >> words[i];
	}

	return i + 1; // Size file.
}


string FileManager::GetValueFromData(string key){
	map<string, string>::iterator itMapFile;

	int size = static_cast<int>(data.size());
	for (int i = 0; i < size; i++){
		for (itMapFile = data[i].begin(); itMapFile != data[i].end(); itMapFile++){
			if (itMapFile->first == key)
				return itMapFile->second;
		}
	}

	return "";
}