#pragma once
#include <windows.h>
#include <string>
#include <list>
using namespace std;
class File
{
public:
	enum FileType 
	{
		FT_FILE = 1,
		FT_DIR = 2
	};

private: 
	string pathName;
	string fileName;
	bool exist;
	FileType type;
	
	//used to find files in the directory of pathName;
	HANDLE hFindFileInDir;
	WIN32_FIND_DATA findDataInDir;

public:
	File(string path = "");
	File(string parent, string child);
	File(File &parent, string child);
	File(const File& another);
	~File(void);

	File& operator= (const File & rh);
	void setToFile( string pathName);
	
	File firstFileInDir();
	File nextFileInDir();

	bool exists() { return exist; }
	bool isDirectory() {return type == FT_DIR;}

	//create a  directory of pathName
	bool mkdir();
	//create a new file of pathName
	bool createNewFile();
	bool renameTo(string newName);
	bool deleteFile();

	string getName() {return fileName;}
	string getPathName() {return pathName;}

private:
	void initFile();
};
