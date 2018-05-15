#include "stdafx.h"
#include "BasicIndex.h"


BasicIndex::BasicIndex(void)
{

}

BasicIndex::~BasicIndex(void)
{

}


PostingList* BasicIndex::readPosting(ifstream& in) {
	PostingList * posting = NULL;
	int termid, size, docid;
	in >> termid >> size;
	list<int> docids;

	for (int i = 0; i < size; i++)
	{
		cin >> docid;
		docids.push_back(docid);
	}

	posting = new PostingList(termid, docids);
	return posting;
}

void BasicIndex::readPostings(ifstream & in, list<PostingList*>& postinglists, set<int>& vis_termid)
{
	int size;
	in >> size;
	int termid, n;
	for (int i = 0; i < size; i++)
	{
		in >> termid >> n;
		if (vis_termid.count(termid)) {
			for (PostingList * postinglist : postinglists) {
				if (postinglist->getTermId() == termid) {
					list<int> *list = postinglist->getList();
					int docid;
					for (int i = 0; i < n; i++) {
						in >> docid;
						list->push_back(docid);
					}
					break;
				}

			}
		}
		else {
			vis_termid.insert(termid);
			list<int> docids;
			int docid;
			for (int i = 0; i < n; i++) {
				in >> docid;
				docids.push_back(docid);
			}
			PostingList * postinglist = new PostingList(termid, docids);
			postinglists.push_back(postinglist);
		}
	}
}

void BasicIndex::writePosting(ofstream& out, PostingList * posting) {
	out << posting->getTermId() << ' ';
	out << posting->getList()->size() << endl;
	bool first_flag = true;
	for (int docid : *posting->getList()) {
		if (first_flag) {
			out << docid;
			first_flag = false;
		}
		else {
			out << ' ' << docid;
		}
	}
	out << endl;
}

void BasicIndex::writePostings(ofstream & out, list<PostingList*>& postinglists)
{
	out << postinglists.size() << endl;
	for (PostingList * postinglist : postinglists) {
		writePosting(out, postinglist);
	}
}
