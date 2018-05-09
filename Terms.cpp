#include "stdafx.h"
#include "Terms.h"


Terms::Terms(File file)
{
	ifstream reader(file.getPathName().c_str());
	while (!reader.eof()) {
		string line;
		getline(reader, line);
		size_t len = line.length() + 1;
		char * delim = " ";
		char * str = new char[len]();
		//memset(str, 0, sizeof(char) * len);
		memcpy(str, line.c_str(),len);
		for (size_t i = 0; i < len; i++) {
			if (str[i] >= 'a' && str[i] <= 'z') continue;
			else if (str[i] >= 'A' && str[i] <= 'Z') continue;
			else if (str[i] == '-' || str[i] == '\'') continue;
			else str[i] = ' ';
		}
		char * p = strtok(str, delim);
		while (p && p - str < len) {
			string term = p;
			terms.push_back(term);
			p = strtok(NULL, delim);
		}
		delete[] str;
	}
}

vector<string>& Terms::getTerms() {
	return terms;
}

Terms::~Terms()
{

}
