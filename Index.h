#pragma once
#include "stdafx.h"
#include "BaseIndex.h"
#include "util/File.h"

using namespace std;

/*
	���ڹ���������������
*/
class Index {
private:
	// Term id -> (position in index file, doc frequency) dictionary
	//map<int, pair<long, int>> postingDict;
	//�������ݽṹ����ά������Ϊ��corpus.index�ļ��У�����ֱ����O(1)�ĸ��Ӷ����ҵ���

	// Doc name -> doc id dictionary
	map<string, int> docDict;
	// Term -> term id dictionary
	map<string, int> termDict;

	// Block queue
	queue<File> blockQueue;

	// Total file counter
	int totalFileCount;
	// Document counter
	int docIdCounter;
	// Term counter
	int wordIdCounter;

	// Index pointer -> basicindex / vbindex
	BaseIndex * pIndex;
	File rootdir, outdir;

public:
	Index(BaseIndex* index, File& root, File& out);
	~Index(void);
	void BSBI();
};
