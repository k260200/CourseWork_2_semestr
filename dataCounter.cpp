#include "stdafx.h"
#include "dataCounter.h"


dataCounter::dataCounter(Movie* hd)
{
	head = hd;
	amountOfStats = 0;
}

dataCounter::~dataCounter()
{
	this->clear();
}

int dataCounter::analyse()
{
	if(head == NULL)
		return 1;
	else
	{
		Movie* current = head;
		while (current)
		{
			int add = -1;
			if (amountOfStats == 0)
			{
				stats.push_back(current->country);
				points.push_back(1);
				amountOfStats++;
			}
			else
			{
				add = thereIsSameStat(current->country);
				if (add != -1)
					points.at(add)++;
				else
				{
					stats.push_back(current->country);
					points.push_back(1);
					amountOfStats++;
				}
			}

			current = current->link;
		}
	}

	return 0;
}

void dataCounter::clear()
{
	stats.clear();
	points.clear();
	amountOfStats = 0;
}

int dataCounter::getAmountOfStats()
{
	return stats.size();
}

string dataCounter::getStatAt(int index)
{
	return stats.at(index);
}

int dataCounter::getPointAt(int index)
{
	return points.at(index);
}

int dataCounter::thereIsSameStat(string st)
{
	for (int i = 0; i < stats.size(); i++)
		if (stats.at(i) == st)
			return i;
	return -1;
}
