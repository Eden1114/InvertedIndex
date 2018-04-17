#include "stdafx.h"
#include <windows.h>
#include "File.h"

/*
 构造函数
 参数：路径名称(string)
 */
File::File(string path) 
{
	pathName = path;
		
	if (pathName == "") {
		exist = false;
		hFindFileInDir = INVALID_HANDLE_VALUE;
	} else {
		initFile();
	}
}



/*
构造函数
参数：父路径(string)，子路径(string)
等价于File(parent + "/" + "child");
*/
File::File(string parent, string child) 
{
	pathName = parent + "/" + child;
	initFile();
}


File::File(File& parent, string child) 
{
	pathName = parent.getPathName() + "/" + child;
	initFile();
}


void File::setToFile( string path) {
	if(hFindFileInDir != INVALID_HANDLE_VALUE) {
		FindClose(hFindFileInDir);
	}
	pathName = path;
	initFile();
}

/*
 初始化文件
 */
void File::initFile() {
	
	//从路径名称中提取文件名
	int index = pathName.find_last_of('/');
	if(index < 0) {
		fileName = pathName;
	} else {
		fileName = pathName.substr(index + 1);
	}

	HANDLE hFind;
	WIN32_FIND_DATA fd;
	hFind = FindFirstFile(pathName.c_str(), &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		exist = false;
		return;
	}
	//
	this->exist = true;
	type =  fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  ? FT_DIR : FT_FILE;	
	fileName = fd.cFileName;

	hFindFileInDir = INVALID_HANDLE_VALUE;
}


File::~File(void)
{
	if(hFindFileInDir != INVALID_HANDLE_VALUE) {
		FindClose(hFindFileInDir);
	}
}

File::File(const File& another) 
{
	pathName = another.pathName;
	fileName = another.fileName;
	type = another.type;
	exist = another.exist;
	hFindFileInDir = INVALID_HANDLE_VALUE;
}

File& File::operator= (const File & rh)
{
	pathName = rh.pathName;
	fileName = rh.fileName;
	exist = rh.exist;
	type = rh.type;
	return *this;
}


bool File::mkdir()
{
	return (_mkdir(pathName.c_str()) == 0);
	initFile();
}


bool File::renameTo(string newPathName) 
{
	int ret = rename(pathName.c_str(), newPathName.c_str());
	if(ret != 0) return false;
	
	pathName = newPathName;
	initFile();
	return true;
}

bool File::deleteFile()
{
	int ret = DeleteFile(pathName.c_str());
	initFile();
	return (ret == TRUE);
}

bool File::createNewFile()
{
	if(exist) return false;

	FILE * pf;
	fopen_s(&pf, pathName.c_str(), "w");
	if (!pf) {
		return false;
	}
	fclose(pf);
	initFile();
	return true;
}


File File::firstFileInDir() {
	
	assert(exist && type == FT_DIR);
	
	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.
	char szDir[MAX_PATH];
	strcpy_s(szDir, MAX_PATH, pathName.c_str());
	strcat_s(szDir, MAX_PATH, "/*");

	File file;
	hFindFileInDir = FindFirstFile(szDir, &findDataInDir);

	if (hFindFileInDir == INVALID_HANDLE_VALUE) { 
		return file;
	}
	
	file.exist = true;
	file.type =  findDataInDir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  ? FT_DIR : FT_FILE;	
	file.fileName = findDataInDir.cFileName;
	file.pathName = pathName + "/" + file.fileName;
	 
	while(file.fileName == "." || file.fileName == "..") {
		file = nextFileInDir();
	}

	return file;
}


File File::nextFileInDir() {
	assert(hFindFileInDir != INVALID_HANDLE_VALUE);
	File file;
	file.exist = (FindNextFile(hFindFileInDir, &findDataInDir) == TRUE);
	if (file.exist ) {
		file.fileName = findDataInDir.cFileName;
		file.pathName = pathName + "/" + file.fileName;
		file.type =  findDataInDir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  ? FT_DIR : FT_FILE;	
	}
	return file;
}