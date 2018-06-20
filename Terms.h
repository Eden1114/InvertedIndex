#pragma once
#include "stdafx.h"
#include "util\File.h"

using namespace std;

class Terms {
private:
	set<string> terms;

public:
	Terms(File file);
	Terms(string line);
	set<string>& getTerms();
	~Terms();
};

