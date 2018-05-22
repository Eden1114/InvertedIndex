#include "stdafx.h"
#include "BasicIndex.h"


BasicIndex::BasicIndex(void)
{

}

BasicIndex::~BasicIndex(void)
{

}

//��ָ��λ�ö�ȡPosting
PostingList* BasicIndex::readPosting(ifstream& in, streampos streampos) {
	//TODO:��ָ��ƫ������ʼ��ȡ�ļ�
	PostingList* posting = NULL;
	in.seekg(streampos);
	int termid;
	list<int> docids;
	in >> termid;

	int size;
	in >> size;
	
	for (int i = 0; i < size; i++)
	{
		int docid;
		in >> docid;
		docids.push_back(docid);
	}
	posting = new PostingList(termid, docids);

	return posting;
}

//��ȡ����postinglist
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

//дһ��postinglist
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

//д�����е�postinglist,������posDict
void BasicIndex::writePostings(ofstream & out, list<PostingList*>& postinglists, map<int, streampos>& postingDict)
{
	out << postinglists.size() << endl;
	for (PostingList * postinglist : postinglists) {

		//��¼λ�ã�����readPosting
		streampos streampos = out.tellp();
		postingDict[postinglist->getTermId()] = streampos;

		writePosting(out, postinglist);
	}
}
