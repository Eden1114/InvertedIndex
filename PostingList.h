#pragma once
#include "stdafx.h"
using namespace std;

/* 
 * Postinglist
 * termid : int
 * postings :list<int>
 * postings is a list of docIDs
 * Frequency is the size of postings
 *
 * Postinglist 倒排记录表 
 * termId 词项索引 
 */
class PostingList {
private:
	int termId;
	list<int> postings;

public:
	PostingList(int termId, list<int> &list);
	PostingList(int termId);
	~PostingList(void);

	int getTermId();
	list<int> * getList();
};
