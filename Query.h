#pragma once
#include <map>
#include <string>
#include <list>
#include <fstream>
#include "baseIndex.h"
#include "postingList.h"
#include "util/file.h"

using namespace std;

class Query
{
private:
	// Term id -> position in index file
	 map<int, long> posDict;

	// Term id -> document frequency
	map<int, int> freqDict;
	
	// Doc id -> doc name dictionary
	map<int, string> docDict;
	
	// Term -> term id dictionary
	map<string, int> termDict;
	
	// Index
	BaseIndex* pIndex;
	File inputDir;

private:
	PostingList* readPosting(ifstream& in, int termId);
	list<int> * intersect(list<int>& p1, list<int>& p2);

public:
	Query(BaseIndex* index, File& input);
	~Query(void);

	void execute();

};
