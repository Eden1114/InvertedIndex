#pragma once
#include "baseIndex.h"
class VBIndex : public BaseIndex
{
public:
	VBIndex(void);
	~VBIndex(void);

	PostingList * readPosting(ifstream& in);
	void writePosting(ofstream& out, PostingList *p);
};


