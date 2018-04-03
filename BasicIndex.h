#pragma once
#include "baseIndex.h"
#include <iostream>

class BasicIndex : public BaseIndex
{
public:
	BasicIndex(void);
	~BasicIndex(void);
	PostingList* readPosting(ifstream& in);
	void writePosting(ofstream& out, PostingList *p);
};
