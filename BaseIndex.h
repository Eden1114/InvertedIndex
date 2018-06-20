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
	int type;
	BaseIndex(void);
	~BaseIndex(void);

	//virtual void readPostings(ifstream& in, list<PostingList *>& postinglists, set<int>& vis_termid)=0;
	//virtual void writePostings(ofstream &out, list<PostingList*>& postinglists, map<int, streampos>& postingDict) = 0;
	virtual PostingList* readPosting(ifstream& in, streampos streampos) = 0;
	virtual void writePosting(ofstream& out, PostingList *posting)=0;

	virtual void readPostings(ifstream & in, map<int, PostingList*>& postinglists) =0;
	virtual void writePostings(ofstream &out, map<int, PostingList*>& postinglists, map<int, streampos>& postingDict)=0;
	
};
