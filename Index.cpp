#include "stdafx.h"

#include "indexCompression.h"
#include "postingList.h"
#include "Index.h"
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

		while (file.exists()) {
			totalFileCount++;
			docDict[file.getPathName()] = ++docIdCounter; //getPathName!

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
		//writer << "BlockDir Name: " << blockDir.getPathName() << endl;
		writer << postinglists.size() << endl;
		for (PostingList* postinglist : postinglists) {
			//termid
			writer << postinglist->getTermId()<<' ';
			//num of docids
			list<int> *p = postinglist->getList();
			writer << p->size() << endl;
			bool first = true;
			for (int docid : *p) {
				if (first) {
					writer << docid;
					first = false;
				}
				else {
					writer << ' ' << docid;
				}
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
	cout << "文件总数为：" << endl;
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
			if (!combfile.createNewFile()) {
				cerr << "conbine file created failed!" << endl;
				return;
			}
		}

		ifstream bf1(b1.getPathName());
		ifstream bf2(b2.getPathName());
		ofstream mf(combfile.getPathName());
		
		/////////////////////////
		//TODO:
		list<PostingList *> postinglists;
		set<int> vis_termId;

		int size;
		bf1 >> size;
		
		for (int i = 0; i < size; i++)
		{
			int termid, n;
			bf1 >> termid >> n;
			if(vis_termId.count(termid)) {
				for (PostingList * postinglist : postinglists) {
					if (postinglist->getTermId() == termid) {
						list<int> *list = postinglist->getList();
						int docid;
						for (int i = 0; i < n; i++) {
							bf1 >> docid;
							list->push_back(docid);
						}
					}
					/*else {
						cout << "Error!" << endl;
					}*/
				}
			}
			else {
				vis_termId.insert(termid);
				list<int> docids;
				int docid;
				for (int i = 0; i < n; i++) {
					bf1 >> docid;
					docids.push_back(docid);
				}
				PostingList * postinglist = new PostingList(termid, docids);
				postinglists.push_back(postinglist);
			}
			
		}

		bf2 >> size;

		for (int i = 0; i < size; i++)
		{
			int termid, n;
			bf2 >> termid >> n;
			if (vis_termId.count(termid)) {
				for (PostingList * postinglist : postinglists) {
					if (postinglist->getTermId() == termid) {
						list<int> *list = postinglist->getList();
						int docid;
						for (int i = 0; i < n; i++) {
							bf2 >> docid;
							list->push_back(docid);
						}
					}
					/*else {
						cout << "Error!" << endl;
					}*/
				}
			}
			else {
				vis_termId.insert(termid);
				list<int> docids;
				int docid;
				for (int i = 0; i < n; i++) {
					bf2 >> docid;
					docids.push_back(docid);
				}
				PostingList * postinglist = new PostingList(termid, docids);
				postinglists.push_back(postinglist);
			}

		}


		//输出到文件
		mf << postinglists.size() << endl;
		for (PostingList* postinglist : postinglists) {
			//termid
			mf << postinglist->getTermId() << ' ';
			//num of docids
			list<int> *p = postinglist->getList();
			mf << p->size() << endl;
			bool first = true;
			for (int docid : *p) {
				if (first) {
					mf << docid;
					first = false;
				}
				else {
					mf << ' ' << docid;
				}
			}
			mf << endl;
		}
		

		//释放内存
		for (PostingList *postinglist : postinglists) {
			delete postinglist;
		}
		//
		bf1.close();
		bf2.close();
		mf.close();
		b1.deleteFile();
		b2.deleteFile();
		blockQueue.push(combfile);
	}


	
	///* Dump constructed index back into file system */
	
	
	File indexFile = blockQueue.front();
	blockQueue.pop();
	
	if (File(outdir.getPathName() + "/corpus.index").exists()) {
		File(outdir.getPathName() + "/corpus.index").deleteFile();
	}
	bool renameflag = indexFile.renameTo(outdir.getPathName() + "/corpus.index");
	//cout << "Renameflag:" << renameflag << endl;


	ofstream termWriter((outdir.getPathName()+ "/term.dict").c_str());
	 //TODO: write  term dictionary to disc.
	map<string, int>::iterator it = termDict.begin();
	for (;it != termDict.end(); ++it) {
		termWriter << it->second << " " << it->first << endl;
	}

	termWriter.close();


	ofstream docWriter((outdir.getPathName() +  "/doc.dict").c_str());
	//TODO: write  document dictionary to disc.
	it = docDict.begin();
	for (; it != docDict.end(); ++it) {
		docWriter << it->second << " " << it->first << endl;
	}
	docWriter.close();

	

	
	/*
	ofstream postWriter((outdir.getPathName() + "/posting.dict").c_str());
	map<string, int>::iterator it = postingDict.begin();
	for (; it != docDict.end(); ++it) {
		docWriter << it->second << " " << it->first << endl;
	}
	postWriter.close();
	*/
	
	
}


