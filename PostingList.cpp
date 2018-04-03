#include "StdAfx.h"
#include "PostingList.h"

PostingList::PostingList(int termId, list<int> &list) {
	this->termId = termId;
	this->postings = list;
}

PostingList::PostingList(int termId) {
	this->termId = termId;
}


int PostingList::getTermId() {
	return termId;
}

list<int> * PostingList::getList() {
	return &postings;
}
