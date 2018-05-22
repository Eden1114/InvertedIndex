#include "stdafx.h"
#include "BasicIndex.h"


BasicIndex::BasicIndex(void)
{

}

BasicIndex::~BasicIndex(void)
{

}

//从指定位置读取Posting
PostingList* BasicIndex::readPosting(ifstream& in, streampos streampos) {
	//TODO:从指定偏移量开始读取文件
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

//读取整个postinglist
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

//写一个postinglist
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

//写入所有的postinglist,并构建posDict
void BasicIndex::writePostings(ofstream & out, list<PostingList*>& postinglists, map<int, streampos>& postingDict)
{
	out << postinglists.size() << endl;
	for (PostingList * postinglist : postinglists) {

		//记录位置，便于readPosting
		streampos streampos = out.tellp();
		postingDict[postinglist->getTermId()] = streampos;

		writePosting(out, postinglist);
	}
}
