#pragma once
#include "baseIndex.h"

using namespace std;

class VBIndex : public BaseIndex
{
private:
	void writeInt(int n, ofstream &out);
	int readInt(ifstream &in);

public:
	VBIndex(void);
	~VBIndex(void);

	PostingList * readPosting(ifstream& in);
	void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid);

	void writePosting(ofstream& out, PostingList *p);
	void writePostings(ofstream &out, list<PostingList*> &postinglists);
};


