#include "StdAfx.h"
#include "VBIndex.h"

VBIndex::VBIndex(void)
{
	type = 2;
}

VBIndex::~VBIndex(void)
{

}


PostingList* VBIndex::readPosting(ifstream& in, streampos streampos) {
	PostingList* posting = NULL;

	in.seekg(streampos);

	list<int> docids;

	int termid = readInt(in);
	int size = readInt(in);

	int docid = 0;

	for (int i = 0; i < size; i++) {
		int temp = readInt(in);
		docid += temp;
		docids.push_back(docid);
	}

	posting = new PostingList(termid, docids);
	return posting;
}
/*
void VBIndex::readPostings(ifstream & in, list<PostingList*>& postinglists, set<int>& vis_termid)
{
	int size;
	size = readInt(in);
	int termid, n;
	for (int i = 0; i < size; i++)
	{
		termid = readInt(in);
		n = readInt(in);

		if (vis_termid.count(termid)) {
			for (PostingList * postinglist : postinglists) {
				if (postinglist->getTermId() == termid) {
					list<int> *list = postinglist->getList();
					int docid = 0, temp;
					for (int i = 0; i < n; i++) {
						temp = readInt(in);
						docid += temp;
						list->push_back(docid);
					}
					break;
				}
			}
		}
		else {
			vis_termid.insert(termid);
			list<int> docids;
			int docid = 0, temp;
			for (int i = 0; i < n; i++) {
				temp = readInt(in);
				docid += temp;
				docids.push_back(docid);
			}
			PostingList * postinglist = new PostingList(termid, docids);
			postinglists.push_back(postinglist);
		}
	}

}
*/



void VBIndex::readPostings(ifstream & in, map<int, PostingList*>& postinglists)
{
	int size;
	size = readInt(in);
	int termid, n;
	for (int i = 0; i < size; i++)
	{
		termid = readInt(in);
		n = readInt(in);
		cout << termid <<' '<< n << endl;
		if (postinglists[termid] == NULL) {
			list<int> docids;
			int docid = 0, temp;
			for (int i = 0; i < n; i++) {
				temp = readInt(in);
				docid += temp;
				//cout << docid << ' ';
				docids.push_back(docid);
			}
			//cout << endl;
			PostingList * postinglist = new PostingList(termid, docids);
			postinglists[termid] = postinglist;
		}

		else {
			PostingList * postinglist = postinglists[termid];
			list<int>* docids = postinglist->getList();
			int docid = 0, temp;
			for (int i = 0; i < n; i++) {
				temp = readInt(in);
				docid += temp;
				docids->push_back(docid);
			}
		}
	}
}


void VBIndex::writePosting(ofstream& out, PostingList *posting) {

	writeInt(posting->getTermId(), out);
	//out << posting->getTermId() << ' ';
	writeInt(posting->getList()->size(), out);
	//out << posting->getList()->size() << endl;

	bool first_flag = true;
	int predocid;
	for (int docid : *posting->getList()) {

		if (first_flag) {
			predocid = docid;
			writeInt(docid, out);
			//out << docid;
			first_flag = false;
		}
		else {
			writeInt(docid - predocid, out);
			predocid = docid;
			//out << ' ' << docid;
		}

	}
	//out << endl;
}

void VBIndex::writePostings(ofstream &out, map<int, PostingList*>& postinglists, map<int, streampos>& postingDict)
{
	writeInt(postinglists.size(), out);
	//out << postinglists.size() << endl;
	for (auto postinglist : postinglists) {

		//记录位置，便于readPosting
		streampos streampos = out.tellp();
		postingDict[postinglist.second->getTermId()] = streampos;

		writePosting(out, postinglist.second);
	}
}

void VBIndex::writeInt(int n, ofstream & out)
{
	byte r;
	while (n >= 128) {
		r = n % 128;
		//cout << "write r:" << (int)r << endl;
		out.write((const char*)&r, sizeof(r));
		n /= 128;
	}

	r = (n % 128) + 128;

	//cout << "write r:" << (int)r << endl; 
	out.write((const char*)&r, sizeof(r));
}

int VBIndex::readInt(ifstream & in)
{
	byte r = 0;

	int ret = 0;
	bool flag = true;
	int zero = 0;
	int p = 1;
	do {
		in.read((char *)&r, sizeof(r));
		//cout << "read r:" << (int)r << endl;
		// 2 1  -> 2 + 1 * 128
		if (r >= 128) {
			flag = false;
			r -= 128;
		}
		ret += r * p;
		p *= 128;
	} while (flag);

	while (zero--) ret *= 128;
	return ret;
}
/*
void VBIndex::writePostings(ofstream &out, list<PostingList*> &postinglists, map<int, streampos>& postingDict)
{
	writeInt(postinglists.size(), out);
	//out << postinglists.size() << endl;
	for (PostingList * postinglist : postinglists) {
		//记录位置，便于readPosting
		streampos streampos = out.tellp();
		postingDict[postinglist->getTermId()] = streampos;

		writePosting(out, postinglist);
	}
}
*/