#include "stdafx.h"
#include "PostingList.h"

PostingList::PostingList(int termId, list<int> &list) {
	this->termId = termId;
	this->postings = list;
}

PostingList::PostingList(int termId) {
	this->termId = termId;
}

PostingList::~PostingList(void) {
	//? �Ƿ���Ҫ����this->postings

}


int PostingList::getTermId() {
	return this->termId;
}

list<int> * PostingList::getList() {
	return & this->postings;
}
