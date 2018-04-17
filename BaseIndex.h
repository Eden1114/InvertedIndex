#pragma once
#include "postingList.h"

/*
	����һ����BasicIndex��VBIndex�̳е���
	������ PostingList �Ķ�д����
*/
class BaseIndex
{
public:
	BaseIndex(void);
	~BaseIndex(void);

	virtual PostingList* readPosting(ifstream& in) = 0;
	virtual void writePosting(ofstream& out, PostingList *p) = 0;
};
