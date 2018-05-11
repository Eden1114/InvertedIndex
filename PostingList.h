#pragma once
#include "stdafx.h"
using namespace std;

/* 
 * 倒排记录表 Posting List
 * termId 词项id int
 * postings 倒排记录表 list<int> 
 * postings is a list of docIDs 
 *
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
