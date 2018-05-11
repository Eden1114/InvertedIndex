#pragma once
#include "baseIndex.h"

using namespace std;

class BasicIndex : public BaseIndex {
public:
	BasicIndex(void);
	~BasicIndex(void);
	PostingList* readPosting(ifstream& in);
	void writePosting(ofstream& out, PostingList *p);
};
