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

	//void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid);
	//void writePostings(ofstream &out, list<PostingList*> &postinglists, map<int, streampos>& postingDict);
	PostingList* readPosting(ifstream& in, streampos streampos);
	void writePosting(ofstream& out, PostingList *posting);
	void readPostings(ifstream & in, map<int, PostingList*>& postinglists);
	void writePostings(ofstream &out, map<int, PostingList*>& postinglists, map<int, streampos>& postingDict);

};


