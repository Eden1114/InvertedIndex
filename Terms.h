#pragma once
#include "stdafx.h"
#include "util\File.h"

using namespace std;

class Terms {
private:
	vector<string> terms;

public:
	Terms(File file);
	vector<string>& getTerms();
	~Terms();
};

