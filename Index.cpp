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

/*
   BSBI indexing algorithm
   block�н���postinglist.
   Ȼ��ϲ�.


   ���ﻹ��Ҫ�ع���ʵ�ֶ�д���ļ��޹أ�
   TODO: 
		1.ȥ����׺����
		2.��дpostinglistͨ��
		pindex->readposting();
		pindex->writeposting();ʵ��
		
		������Ķ�������
		����Ҫ�õ�C++���������������
 */
void Index::BSBI() {
	File block = rootdir.firstFileInDir();
	while (block.exists()) {
		list<PostingList*> postinglists;
		cout << block.getName() << endl;
		File blockFile(outdir, block.getName());
		if (!blockFile.exists()) {
			if (!blockFile.createNewFile()) {
				cerr << "Create new block file failed" << endl;
			}
		}
		blockQueue.push(blockFile);

		File blockDir(rootdir, block.getName());
		File file = blockDir.firstFileInDir();

		//����Ե���
		cout << blockDir.getPathName() << endl;

		while (file.exists()) {
			totalFileCount++;
			docDict[file.getPathName()] = ++docIdCounter;
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
		
		//���
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

		//������ļ�
		ofstream writer(blockFile.getPathName());
		pIndex->writePostings(writer, postinglists);
		writer.close();
		//����������basicIndex��VBindex������

		//�ͷ��ڴ�
		for (PostingList *postinglist : postinglists) {
			delete postinglist;
		}

		block = rootdir.nextFileInDir();
	}// end while(block.exists())

	 /* Required: output total number of files. */
	cout << "�ļ�����Ϊ��";
	cout << totalFileCount << endl;

	/* Merge Blocks */
	
	while (true) {
		if (blockQueue.size() <= 1) {
			break;
		}
		File b1 = blockQueue.front();
		blockQueue.pop();
		File b2 = blockQueue.front();
		blockQueue.pop();
		
		string combfilename = b1.getName() + "+" + b2.getName();
		cout << combfilename << endl;
		File combfile(outdir.getPathName(), combfilename);

		cout << combfile.getPathName() << endl;

		if (!combfile.exists()) {
			if (!combfile.createNewFile()) {
				cerr << "conbine file created failed!" << endl;
				return;
			}
		}

		cout << b1.getPathName() << endl;
		cout << b2.getPathName() << endl;
		cout << combfile.getPathName() << endl;

		ifstream bf1(b1.getPathName());
		ifstream bf2(b2.getPathName());
		ofstream mf(combfile.getPathName());
		
		//postinglist * read = pIndex.readPosting(bf1, list<PostingList*> &postinglists);


		/////////////////////////
		//TODO:
		list<PostingList *> postinglists;
		set<int> vis_termId;

		pIndex->readPostings(bf1, postinglists, vis_termId);
		pIndex->readPostings(bf2, postinglists, vis_termId);

		//������ļ�
		pIndex->writePostings(mf, postinglists);

		//�ͷ��ڴ�
		for (PostingList *postinglist : postinglists) {
			delete postinglist;
		}
		
		bf1.close();
		bf2.close();
		mf.close();
		b1.deleteFile();
		b2.deleteFile();
		blockQueue.push(combfile);
	}
	
	File indexFile = blockQueue.front();
	blockQueue.pop();
	cout << indexFile.getPathName() << endl;
	File indexDeleteFile(outdir.getPathName() + "/corpus.index");
	if (indexDeleteFile.exists()) {
		indexDeleteFile.deleteFile();
	}
	bool renameflag = indexFile.renameTo(outdir.getPathName() + "/corpus.index");
	cout << "Renameflag:" << renameflag << endl;

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
	
}
