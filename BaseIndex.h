#pragma once
#include "postingList.h"

/*
	这是一个给BasicIndex和VBIndex继承的类
	抽象了 PostingList 的读写函数
*/
class BaseIndex
{
public:
	BaseIndex(void);
	~BaseIndex(void);

	virtual PostingList* readPosting(ifstream& in) = 0;
	virtual void writePosting(ofstream& out, PostingList *p) = 0;
};
