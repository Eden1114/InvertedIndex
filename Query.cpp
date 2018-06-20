#include "StdAfx.h"
#include "Query.h"
#include "Terms.h"
#include <iostream>

Query::Query(BaseIndex * index, File& input) : pIndex(index), inputDir(input)
{

}

Query::~Query(void)
{

}



/*
 * Intersect two listings to one listing
 */
list<int> * Query::intersect(list<int>& p1, list<int>& p2)
{
	list<int> * p = new list<int>();

	list<int>::iterator it1 = p1.begin();
	list<int>::iterator it2 = p2.begin();

	while (it1 != p1.end() && it2 != p2.end()) {
		if (*it1 < *it2)
		{
			it1++;
		}
		else if (*it1 == *it2) {
			p->push_back(*it1);
			it1++;
			it2++;
		}
		else {
			it2++;
		}
	}
	return p;
}


void Query::execute()
{
	/* Index file */
	//�����basicindex

	ifstream indexFile = ifstream(inputDir.getPathName() + "/corpus.index", pIndex->type == 1? ios::in : ios::binary);
	

	/* Term dictionary */
	{
		ifstream termReader((inputDir.getPathName() + "/term.dict").c_str());
		int termid;
		string term;
		while (termReader >> termid >>term) {
			termDict[term] = termid;
		}
		termReader.close();
	}

	/* Doc dictionary */
	{
		ifstream docReader((inputDir.getPathName() + "/doc.dict").c_str());
		int docid;
		string doc;
		while (docReader >> docid >> doc)
		{
			docDict[docid] = doc;
		}
		docReader.close();
	}

	/*pos dictionary*/
	{
		ifstream posReader((inputDir.getPathName() + "/pos.dict").c_str());
		int termid;
		long pos;
		
		while (posReader >> termid >> pos) {
			posDict[termid] = pos;
		}
		
		posReader.close();
	}
	
	
	string line;
	cout << "����Ϊ��ʱ���˳�����" << endl;
	cout << "������ؼ���:";
	getline(cin, line);

	while (line != "") {
		Terms terms(line);
		vector<PostingList*> postinglists;
		postinglists.clear();

		list<int> result_docid;
		for (string term : terms.getTerms()) {
			int termid = termDict[term];
			
			if (termid != 0) {
				long pos = posDict[termid];
				postinglists.push_back(pIndex->readPosting(indexFile, pos));
			}
		}
		list<int> *result = nullptr;
		bool one_flag = false;

		if (postinglists.size() == 1)
		{
			result = postinglists[0]->getList();
			one_flag = true;
		}
		else if(postinglists.size() >= 2)
		{
			sort(postinglists.begin(), postinglists.end(), [&](PostingList * const a, PostingList * const b) {
				return a->getList()->size() < b->getList()->size();
			});

			for (vector<PostingList*>::iterator it = postinglists.begin(); it != postinglists.end(); it++)
			{
				if (result == nullptr) {
					result = intersect(*((*it)->getList()), *((*(it + 1))->getList()));
					it++;
				}
				else {
					list<int> *t = result;
					result = intersect(*result, *((*it)->getList()));
					delete t;//�����ڴ�й©
				}

			}
		}
		
		if (result == nullptr) {
			cout << "�����ڸùؼ��֣�" << endl;
		}

		else {
			cout << "�������ļ��г��ֹ��ùؼ���" << endl;
			for (auto i : *result)
			{
				cout << docDict[i] << endl;
			}
			if (!one_flag)
			{
				delete result;
			}
		}

		for (auto postinglist : postinglists) {
			delete postinglist;
		}


		cout << "������ؼ���:";
		getline(cin, line);
	}

	indexFile.close();
}

