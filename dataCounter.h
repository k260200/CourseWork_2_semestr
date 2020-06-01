#pragma once

#include <vector>
#include <string>
#include "MovieLibrary.h"

using namespace std;

class dataCounter
{
public:
	dataCounter(Movie* );
	~dataCounter();

	int analyse();
	void clear();
	int getAmountOfStats();
	string getStatAt(int);
	int getPointAt(int);

private:
	Movie* head;
	int amountOfStats;
	vector<string> stats;
	vector<int> points;

	int thereIsSameStat(string);
};

