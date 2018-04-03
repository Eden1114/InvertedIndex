#include "StdAfx.h"
#include "Index.h"
#include <iostream>
#include "postingList.h"
#include "indexCompression.h"

Index::Index(BaseIndex * index, File& root, File& out) : pIndex(index), rootdir(root),outdir(out)
{
	totalFileCount = 0;
	docIdCounter = 0;
	wordIdCounter = 0;
}

Index::~Index(void)
{

}

void Index::writePosting(ofstream &out, PostingList* posting) {
	/*
	* TODO: Your code here
	*	 
	*/
}

/* BSBI indexing algorithm */
void Index::BSBI() {

	File block = rootdir.firstFileInDir();
	while(block.exists()) {

		/*
		  *     postinglists is used to store postinglist for each term in a block.
		  *    
		  */
		list<PostingList*> postinglists;   //Here you can use any data structure  you want other than list.
 
		File blockFile (outdir, block.getName());
		blockQueue.push(blockFile);

		File  blockDir(rootdir, block.getName());
		File file = blockDir.firstFileInDir();
		while(file.exists())
		{
			++totalFileCount;
			docDict[file.getPathName()] =  docIdCounter++;

			ifstream reader(file.getPathName().c_str());
			
			while(!reader.eof()) {
				string line;
				getline(reader, line);
				//cout << line << endl;
				/*
				* TODO: Your code here
				*       Read terms from reader.
				*       For each term, build up a list of
				*       documents in which the term occurs
				*/
			}

			reader.close();
			//get next file
			file = blockDir.nextFileInDir();
		} //end while(file.exists())

		/* Sort and output */
		if (!blockFile.createNewFile()) {
			cerr << "Create new block failure."  << endl;
			return;
		}
		ofstream writer(blockFile.getPathName().c_str());
		/*
		* TODO: Your code here
		*       Write all posting lists for all terms to file (blockFile) 
		*       Be attention that termIds in  blockFile MUST be ordered.
		*       DO NOT forget to release memories of postinglists.
		*/
		writer.close();

		//get next block
		block = rootdir.nextFileInDir();
	} //end while(block.exists()) 


	/* Required: output total number of files. */
	cout << totalFileCount << endl;

	/* Merge blocks */
	while (true) {
		if (blockQueue.size() <= 1)
			break;

		File b1 = blockQueue.front();
		blockQueue.pop();
		File b2 = blockQueue.front();
		blockQueue.pop();
		File combfile(outdir.getPathName(), b1.getName() + "+" + b2.getName());

		if (!combfile.createNewFile()) {
			cerr << "Create new block failure."  << endl;
			return;
		}

		ifstream bf1(b1.getPathName().c_str());
		ifstream bf2(b2.getPathName().c_str());
		ofstream mf(combfile.getPathName().c_str());

		/*
		* TODO: Your code here
		*       Combine blocks bf1 and bf2 into our combined file, mf
		*       You will want to consider in what order to merge
		*       the two blocks (based on term ID, perhaps?).
		*       
		*/


		bf1.close();
		bf2.close();
		mf.close();
		b1.deleteFile();
		b2.deleteFile();
		blockQueue.push(combfile);
	}


	/* Dump constructed index back into file system */
	File indexFile = blockQueue.front();
	blockQueue.pop();
	indexFile.renameTo(outdir.getPathName() + "/corpus.index");


	ofstream termWriter((outdir.getPathName()+ "/term.dict").c_str());
	/*
	  * TODO: write  term dictionary to disc.
	  */
	termWriter.close();


	ofstream docWriter((outdir.getPathName() +  "/doc.dict").c_str());
	/*
	  * TODO: write  document dictionary to disc.
	  */
	docWriter.close();


	ofstream postWriter((outdir.getPathName() + "/posting.dict").c_str());
	/*
	  * TODO: write  postingLists to disc.
	  */
	postWriter.close();

}
