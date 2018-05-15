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
 * Postinglist ���ż�¼�� 
 * termId �������� 
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
