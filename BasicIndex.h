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
	
	PostingList* readPosting(ifstream& in);
	void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid);
	
	void writePosting(ofstream& out, PostingList *posting);
	void writePostings(ofstream &out, list<PostingList*> &postinglists);
};
