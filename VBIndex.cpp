#include "StdAfx.h"
#include "VBIndex.h"

VBIndex::VBIndex(void)
{

}

VBIndex::~VBIndex(void)
{

}


PostingList* VBIndex::readPosting(ifstream& in) {
	PostingList* posting = NULL;
	/*
	 * TODO: Your code here
	 */
	return posting;
}

void VBIndex::readPostings(ifstream & in, list<PostingList*>& postinglists, set<int>& vis_termid)
{

}

void VBIndex::writePosting(ofstream& out, PostingList *p) {
	/*
	 * TODO: Your code here
	 */
}

void VBIndex::writePostings(ofstream & out, list<PostingList*>& postinglists)
{

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
