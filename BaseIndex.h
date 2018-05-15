#pragma once
#include "postingList.h"

using namespace std;

/*
	����һ����BasicIndex��VBIndex�̳е���
	������ PostingList �Ķ�д����
	����ȫ���ô��麯��ʵ��
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
