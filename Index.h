#pragma once
#include "stdafx.h"
#include "BaseIndex.h"
#include "util/File.h"

using namespace std;

/*
	用于构建倒排索引的类
*/
class Index {
private:
	//Term id -> (position in index file, doc frequency) dictionary
	map<int, streampos> postingDict;
	// Doc name -> doc id dictionary
	map<string, int> docDict;
	// Term -> term id dictionary
	map<string, int> termDict;

	// Block queue
	deque<File> blockQueue;

	// Total file counter
	int totalFileCount;
	// Document counter
	int docIdCounter;
	// Term counter
	int wordIdCounter;

	// Index pointer -> basicindex / vbindex
	BaseIndex * pIndex;
	File rootdir, outdir;

public:
	Index(BaseIndex* index, File& root, File& out);
	~Index(void);
	void BSBI();
};
