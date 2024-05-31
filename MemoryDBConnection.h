#ifndef MEMORYDBCONNECTION_H_
#define MEMORYDBCONNECTION_H_

#include <vector>
#include <iostream>

#include "Serie.h"

using namespace std;

class MemoryDBConnection
{
private:
	vector<Serie *> seriesDB;

public:
	MemoryDBConnection();
	virtual ~MemoryDBConnection();
	vector<Serie *> &getSerieList();
	void close();
};

#endif
