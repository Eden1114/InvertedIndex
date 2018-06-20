#pragma once
#include "baseIndex.h"

using namespace std;
/*
	建立不进行压缩的索引表
*/
class BasicIndex : public BaseIndex {
public:
	BasicIndex(void);
	~BasicIndex(void);
	//void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid);
	//void writePostings(ofstream &out, list<PostingList*> &postinglists, map<int, streampos>& postingDict);
	PostingList* readPosting(ifstream& in, streampos streampos);
	void writePosting(ofstream& out, PostingList *posting);
	void writePostings(ofstream &out, map<int, PostingList*>& postinglists, map<int, streampos>& postingDict);
	void readPostings(ifstream & in, map<int, PostingList*>& postinglists);
};
