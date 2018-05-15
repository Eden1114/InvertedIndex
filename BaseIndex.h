#pragma once
#include "postingList.h"

using namespace std;

/*
	这是一个给BasicIndex和VBIndex继承的类
	抽象了 PostingList 的读写函数
	并且全部用纯虚函数实现
*/
class BaseIndex {
public:
	BaseIndex(void);
	~BaseIndex(void);

	virtual PostingList* readPosting(ifstream& in) = 0;
	virtual void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid) = 0;
	
	virtual void writePosting(ofstream& out, PostingList *p) = 0;
	virtual void writePostings(ofstream &out, list<PostingList*> &postinglists) = 0;
};
