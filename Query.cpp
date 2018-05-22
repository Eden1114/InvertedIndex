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


///* 
// * Write a posting list with a given termID from the file 
// * You should seek to the file position of this specific
// * posting list and read it back.
// */
//PostingList * Query::readPosting(ifstream& in, int termId)
//{
//	PostingList * posting = NULL;
//	
//	//posting = pIndex->readPosting(in, termId);
//	return posting;
//}


/*
 * Intersect two listings to one listing
 */
list<int> * Query::intersect(list<int>& p1, list<int>& p2)
{
	list<int> * p = new list<int>();
	/*
	 * TODO: Your code here
	 *
	 */


	list<int>::iterator it1 = p1.begin();
	list<int>::iterator it2 = p2.begin();

	while (it1 != p1.end() || it2 != p2.end()) {
		if (it1 != p1.end() && it2 != p2.end()) {
			if (*it1 == *it2) {
				p->push_back(*it1);
				it1++;
				it2++;
			}
			else if (*it1 > *it2) {
				p->push_back(*it2);
				it2++;
			}
			else {
				p->push_back(*it1);
				it1++;
			}
		}
		else if (it1 == p1.end() && it2 != p2.end()) {
			p->push_back(*it2);
			it2++;
		}
		else {
			p->push_back(*it1);
			it1++;
		}
	}
	return p;
}


void Query::execute()
{
	/* Index file */
	ifstream indexFile(inputDir.getPathName() + "/corpus.index");

	/* Term dictionary */
	ifstream termReader((inputDir.getPathName() + "/term.dict").c_str());
	{
		int termid;
		string term;
		while (termReader >> termid) {
			termReader >> term;
			termDict[term] = termid;
		}
		termReader.close();
	}

	{
		/* Doc dictionary */
		ifstream docReader((inputDir.getPathName() + "/doc.dict").c_str());
		int docid;
		string doc;
		while (docReader >> docid)
		{
			docReader >> doc;
			docDict[docid] = doc;
		}
		docReader.close();
	}

	/*
	{
		//Posting dictionary 
		ifstream postReader((inputDir.getPathName() + "/posting.dict").c_str());
		
		  * TODO: Build doc dictionary
		postReader.close();
	}
	*/
	/* Processing queries */

	string line;
	getline(cin, line);
	while (line != "") {
		Terms terms(line);


		/*
		 * TODO: Your code here
		 *       Perform query processing with the inverted index.
		 *       Make sure to print to stdout the list of documents
		 *       containing the query terms, one document file on each
		 *       line, sorted in lexicographical order.
		 */

		getline(cin, line);
	}

	indexFile.close();
}

