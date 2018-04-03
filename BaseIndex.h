#pragma once
#include "postingList.h"

class BaseIndex
{
public:
	BaseIndex(void);
	~BaseIndex(void);

	virtual PostingList* readPosting(ifstream& in) = 0;
	virtual void writePosting(ofstream& out, PostingList *p) = 0;
};
