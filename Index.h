#pragma once

#include <map>
#include <string>
#include <list>
#include <queue>
#include <fstream>
#include "BaseIndex.h"
#include "util/File.h"

using namespace std;

class Index
{
private:
	// Term id -> (position in index file, doc frequency) dictionary
	map<int, pair<long, int>> postingDict;
	// Doc name -> doc id dictionary
	map<string, int> docDict;
	// Term -> term id dictionary
	map<string, int> termDict;

	// Block queue
	queue<File> blockQueue;

	// Total file counter
	int totalFileCount;
	// Document counter
	int docIdCounter;
	// Term counter
	int wordIdCounter;

	// Index
	BaseIndex * pIndex;
	File rootdir, outdir;

private:
	void writePosting(ofstream &out, PostingList  * posting);

public:
	Index(BaseIndex * index, File& root, File& out);
	~Index(void);
	void BSBI();
};
