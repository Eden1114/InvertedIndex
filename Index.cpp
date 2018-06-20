#include "stdafx.h"
#include "postingList.h"
#include "Index.h"
#include "Terms.h"
using namespace std;


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
   block中建立postinglist.
   然后合并.

 */
void Index::BSBI() {
	File block = rootdir.firstFileInDir();
	while (block.exists()) {
		map<int, PostingList*> blockpostinglists;
		File blockFile(outdir, block.getName());
		cout << blockFile.getName() << endl;
		if (!blockFile.exists()) {
			if (!blockFile.createNewFile()) {
				cerr << "Create new block file failed" << endl;
			}
		}
		blockQueue.push_back(blockFile);
		
		File blockDir(rootdir, block.getName());
		File file = blockDir.firstFileInDir();
		
		while (file.exists()) {
			totalFileCount++;
			cout << file.getName() << endl;
			docDict[file.getPathName()] = ++docIdCounter;
			Terms terms(file);

			for (string term : terms.getTerms()) {
				//给term添加termid
				if (termDict[term] == 0) {
					wordIdCounter++;
					termDict[term] = wordIdCounter;
				}

				//把docCounter插入到指定termid的postinglists中
				if (blockpostinglists[termDict[term]] == NULL) {
					list<int> posting;
					posting.push_back(docIdCounter);
					PostingList *pos = new PostingList(termDict[term], posting);
					blockpostinglists[termDict[term]] = pos;
				}
				else {
					PostingList *pos = blockpostinglists[termDict[term]];
					list<int> *list = pos->getList();
					list->push_back(docIdCounter);
				}

			}
			file = blockDir.nextFileInDir();
		}

		//输出到文件
		ofstream writer(blockFile.getPathName());
		pIndex->writePostings(writer, blockpostinglists, postingDict);
		writer.close();

		//释放内存
		for (auto postinglist : blockpostinglists) {
			delete postinglist.second;
		}
		
		block = rootdir.nextFileInDir();
	}// end while(block.exists())

	
	/* Required: output total number of files. */
	cout << blockQueue.size() << endl;
	std::cout << "文件总数为：";
	std::cout << totalFileCount << std::endl;

	/* Merge Blocks */

	while (true) {
		if (blockQueue.size() <= 1) {
			break;
		}
		File b1 = blockQueue.front();
		blockQueue.pop_front();
		File b2 = blockQueue.front();
		blockQueue.pop_front();
		cout << "11111111" << endl;
		string combfilename = b1.getName() + "+" + b2.getName();
		//cout << combfilename << endl;
		File combfile(outdir.getPathName(), combfilename);

		//cout << combfile.getPathName() << endl;

		if (!combfile.exists()) {
			if (!combfile.createNewFile()) {
				cerr << "conbine file created failed!" << endl;
				return;
			}
		}

		ifstream bf1(b1.getPathName());
		ifstream bf2(b2.getPathName());
		ofstream mf(combfile.getPathName());

		map<int,PostingList *> postinglists;
		set<int> vis_termId;
		cout << "11111112" << endl;
		pIndex->readPostings(bf1,postinglists);
		cout << "11111113" << endl;
		pIndex->readPostings(bf2, postinglists);
		cout << "11111114" << endl;
		//输出到文件
		pIndex->writePostings(mf, postinglists, postingDict);
		cout << "11111115" << endl;
		//释放内存
		for (auto postinglist : postinglists) {
			delete postinglist.second;
		}

		bf1.close();
		bf2.close();
		mf.close();
		b1.deleteFile();
		b2.deleteFile();
		blockQueue.push_front(combfile);
	}

	File indexFile = blockQueue.front();
	blockQueue.pop_front();
	//cout << indexFile.getPathName() << endl;
	File indexDeleteFile(outdir.getPathName() + "/corpus.index");
	if (indexDeleteFile.exists()) {
		indexDeleteFile.deleteFile();
	}
	bool renameflag = indexFile.renameTo(outdir.getPathName() + "/corpus.index");
	//cout << "Renameflag:" << renameflag << endl;

	ofstream termWriter((outdir.getPathName() + "/term.dict").c_str());
	//TODO: write  term dictionary to disc.
	map<string, int>::iterator it = termDict.begin();
	for (; it != termDict.end(); ++it) {
		termWriter << it->second << " " << it->first << endl;
	}

	termWriter.close();


	//TODO: write  document dictionary to disc.
	ofstream docWriter((outdir.getPathName() + "/doc.dict").c_str());
	it = docDict.begin();
	for (; it != docDict.end(); ++it) {
		docWriter << it->second << " " << it->first << endl;
	}
	docWriter.close();


	//TDO: write streampos dictionary to disc.
	ofstream posWriter((outdir.getPathName() + "/pos.dict").c_str());

	map<int, streampos>::iterator iter = postingDict.begin();
	for (; iter != postingDict.end(); ++iter) {

		posWriter << iter->first << " " << iter->second << endl;
	}

	posWriter.close();
	std::cout << "索引构建完成!" << std::endl;
}
