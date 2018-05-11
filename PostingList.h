#pragma once
#include "stdafx.h"
using namespace std;

/* 
 * ���ż�¼�� Posting List
 * termId ����id int
 * postings ���ż�¼�� list<int> 
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
