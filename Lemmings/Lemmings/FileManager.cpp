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

		int i = 0;
		int pos = 0;
		string linia = "";
		while (getline(reader, linia, '\n')){
			map<string, string> dataFile;
			dataFile.clear();

			bool readedFile = false;
			while (!readedFile){
				while (linia[i] != ' '){
					if (i >= linia.length() - 1){
						readedFile = true;
						break;
					}
					i++;
				}
				pos = i + 1;

				while (linia[i] != '='){
					if (i >= linia.length() - 1){
						readedFile = true;
						break;
					}
					i++;
				}
				string key = linia.substr(pos, i - pos);
				pos = i + 2;

				while (linia[i] != ' '){
					if (i >= linia.length() - 1){
						readedFile = true;
						break;
					}
					i++;
					if (linia[i] == '>'){
						readedFile = true;
						break;
					}
				}
				i--;
				string value = linia.substr(pos, i - pos);

				dataFile.insert(pair<string, string>(key, value));
			}
			data.push_back(dataFile);
		}
		reader.close();
	}
	else
		cout << "Unable to open the file '" << name << "'!" << endl;
}

void FileManager::Read(const char* name, int line){
	data.clear();

	fstream reader;
	reader.open(name, ios::in);
	if (reader.is_open()){
		cout << "The file '" << name << "' has opened succesfully!" << endl;

		int i = 0;
		int pos = 0;
		string linia = "";

		for (int currLine = 0; currLine < line; currLine++){
			if (currLine == line - 1){
				getline(reader, linia, '\n');
				map<string, string> dataFile;
				dataFile.clear();

				bool readedFile = false;
				while (!readedFile){
					while (linia[i] != ' '){
						if (i >= linia.length() - 1){
							readedFile = true;
							break;
						}
						i++;
					}
					pos = i + 1;

					while (linia[i] != '='){
						if (i >= linia.length() - 1){
							readedFile = true;
							break;
						}
						i++;
					}
					string key = linia.substr(pos, i - pos);
					pos = i + 2;

					while (linia[i] != ' '){
						if (i >= linia.length() - 1){
							readedFile = true;
							break;
						}
						i++;
						if (linia[i] == '>'){
							readedFile = true;
							break;
						}
					}
					i--;

					string value = linia.substr(pos, i - pos);
					dataFile.insert(pair<string, string>(key, value));
				}
				data.push_back(dataFile);
			}
		}
		reader.close();
	}
	else
		cout << "Unable to open the file '" << name << "'!" << endl;
}


int FileManager::CheckFile(fstream reader){
	reader.seekg(0, reader.end); // De la posició inicial zero, considerant el 0 com la posició on es troba el punter fstream, cap a l'última dada del fitxer.
	int size = reader.tellg(); // 'tellg' retorna la posició de l'fstream 'lectura', a la qual està apuntant.
	reader.seekg(0, reader.beg); // Torna a ubicar el punter 'lectura' al principi del tot.

	return size;
}

int FileManager::ReadContents(vector<string> &words, fstream &in){
	int i = -1;
	while (!in.eof()){
		i++;
		in >> words[i];
	}

	return i + 1; // Size file.
}


string FileManager::GetValueFromData(string key){
	map<string, string>::iterator itMapFile;

	int size = data.size();
	for (int i = 0; i < size; i++){
		for (itMapFile = data[i].begin(); itMapFile != data[i].end(); itMapFile++){
			if (itMapFile->first == key)
				return itMapFile->second;
		}
	}

	return "";
}