#pragma once
#include "baseIndex.h"

using namespace std;

class VBIndex : public BaseIndex
{
public:
	VBIndex(void);
	~VBIndex(void);

	PostingList * readPosting(ifstream& in);
	void writePosting(ofstream& out, PostingList *p);
};


