#include "StdAfx.h"
#include "Index.h"
#include <iostream>
#include "postingList.h"
#include "indexCompression.h"
#include "Terms.h"

Index::Index(BaseIndex * index, File& root, File& out) : pIndex(index), rootdir(root), outdir(out)
{
	totalFileCount = 0;
	docIdCounter = 0;
	wordIdCounter = 0;
}

Index::~Index(void)
{

}

void Index::writePosting(ofstream &out, PostingList* posting) {


}

/*
   BSBI indexing algorithm
   block中建立postinglist.
   然后合并.
 */
void Index::BSBI() {
	File block = rootdir.firstFileInDir();
	while (block.exists()) {
		list<PostingList*> postinglists;
		File blockFile(outdir, block.getName() + ".txt");
		if (!blockFile.exists()) {
			if (!blockFile.createNewFile()) {
				cerr << "Create new block file failed" << endl;
			}
		}
		blockQueue.push(blockFile);

		File blockDir(rootdir, block.getName());
		File file = blockDir.firstFileInDir();

		cout << blockDir.getPathName() << endl;
		cout << postinglists.size() << endl;

		while (file.exists()) {
			totalFileCount++;
			docDict[file.getPathName()] = docIdCounter++; //getPathName!

			Terms terms(file);

			for (string term : terms.getTerms()) {
				if (termDict[term] == 0) {
					wordIdCounter++;
					termDict[term] = wordIdCounter;
					list<int> posting;
					posting.push_back(docIdCounter);
					PostingList * pos = new PostingList(termDict[term], posting);
					postinglists.push_back(pos);
				}
				else {
					bool postinglist_flag = false;
					for (PostingList *t : postinglists) {
						if (t->getTermId() == termDict[term]) {
							postinglist_flag = true;
							list<int>* list = t->getList();
							bool docid_flag = false;
							for (int docid : *list) {
								if (docid == docIdCounter) {
									docid_flag = true;
									break;
								}
							}
							if (!docid_flag) {
								list->push_back(docIdCounter);
							}
						}
					}
					if (!postinglist_flag) {
						list<int> posting;
						posting.push_back(docIdCounter);
						PostingList * pos = new PostingList(termDict[term], posting);
						postinglists.push_back(pos);
					}
				}
			}
			file = blockDir.nextFileInDir();
		}
		cout << postinglists.size() << endl;

		//输出
		/*out << "BlockDir Name: " << blockDir.getPathName() << endl;
		for (PostingList* postinglist : postinglists) {
			cout << "termId:" << postinglist->getTermId() << endl;
			list<int> *p = postinglist->getList();
			cout << "docIDs: ";
			for (int docid : *p) {
				cout << docid << ' ';
			}
			cout << endl;
		}*/

		//输出到文件
		ofstream writer(blockFile.getPathName());
		writer << "BlockDir Name: " << blockDir.getPathName() << endl;
		for (PostingList* postinglist : postinglists) {
			writer << "termId: " << postinglist->getTermId() << endl;
			list<int> *p = postinglist->getList();
			writer << "docIDs: ";
			for (int docid : *p) {
				writer << docid << ' ';
			}
			writer << endl;
		}
		writer.close();

		//释放内存
		for (PostingList *postinglist : postinglists) {
			delete postinglist;
		}

		block = rootdir.nextFileInDir();
	}// end while(block.exists())

	 /* Required: output total number of files. */
	cout << totalFileCount << endl;
	/* Merge Blocks */
	while (true)
	{
		if (blockQueue.size() <= 1) {
			break;
		}
		File b1 = blockQueue.front();
		blockQueue.pop();
		File b2 = blockQueue.front();
		blockQueue.pop();
		
		string combfilename = b1.getName().substr(0, b1.getName().length() - 4) + "+" + b2.getName();
		cout << combfilename << endl;
		File combfile(outdir.getPathName(), combfilename);
		if (!combfile.exists()) {
			combfile.createNewFile();
		}
		
	}

}


