// InvertedIndex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "baseIndex.h"
#include "basicIndex.h"
#include "VBIndex.h"
#include "index.h"
#include "query.h"
#include "util/File.h"

using namespace std;

//建立索引
//Index  Basic|VB data_dir output_dir
void BuildIndex(string indexType, string dataPath, string outPath)
{
	//输出中间信息以调试
	//std::cout << indexType << std::endl;
	//std::cout << dataPath << std::endl;
	//std::cout << outPath << std::endl;

	BaseIndex * pIndex;
	File rootdir, outdir;

	/* Get index */
	if (strcmp(indexType.c_str(), "Basic") == 0) {
		pIndex = new BasicIndex();
	}
	else if (strcmp(indexType.c_str(), "VB") == 0) {
		pIndex = new VBIndex();
	}

	else {
		cerr << "Index method must be \"Basic \" or  \"VB \"" << endl;
		return;
	}

	/* Get root directory */
	rootdir.setToFile(dataPath);
	if (!rootdir.exists()) {
		cerr << "Invalid data directory: " << dataPath << endl;
		delete pIndex;
		return;
	}

	/* Get output directory */
	outdir.setToFile(outPath);
	if ((!outdir.exists()) && (!outdir.mkdir())) {
		cerr << "Invalid output directory:" << outPath << endl;
		delete pIndex;
		return;
	}
	Index index(pIndex, rootdir, outdir);
	
	//输出中间信息以调试
	//cout << "1.执行到这啦！" << endl;
	
	index.BSBI();
	delete pIndex;
}

// Query Basic|VB index_dir
void ExecuteQuery(string indexTpye, string indexPath)
{
	BaseIndex * pIndex;

	/* Get index */
	if (strcmp(indexTpye.c_str(), "Basic") == 0) {
		pIndex = new BasicIndex();
	}
	else if (strcmp(indexTpye.c_str(), "VB") == 0) {
		pIndex = new VBIndex();
	}
	else {
		cerr << "Index method must be \"Basic \" or  \"VB \"" << endl;
		return;
	}

	/* Get index directory */
	File inputdir(indexPath);
	if (!inputdir.exists() || !inputdir.isDirectory()) {
		cerr << "Invalid index directory: " << indexPath << endl;
		delete pIndex;
		return;
	}

	Query query(pIndex, inputdir);
	query.execute();

	delete pIndex;
}

void main(int argc, char * argv[])
{
	std::cout << argc << std::endl;
	/* Parse command line */
	if (argc != 4 && argc != 5) {
		cerr << "Usage 1:  Index  Basic|VB data_dir output_dir" << endl;
		cerr << "Usage 2:  Query Basic|VB index_dir" << endl;
		return;
	}

	if (strcmp(argv[1], "Index") == 0 && argc == 5) {
		BuildIndex(argv[2], argv[3], argv[4]);
	}
	else if (strcmp(argv[1], "Query") == 0 && argc == 4) {
		ExecuteQuery(argv[2], argv[3]);
	}
	else {
		cerr << "Comamand must be Index or Query!" << endl;
	}
}



