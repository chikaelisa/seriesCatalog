/*
 * MemoryDBConnection.cpp
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#include <vector>

#include "MemoryDBConnection.h"

using namespace std;

MemoryDBConnection::MemoryDBConnection()
{
	  seriesDB = vector<Serie*>();
}

MemoryDBConnection::~MemoryDBConnection()
{
	close();
}

vector<Serie*>& MemoryDBConnection::getSerieList()
{
	return seriesDB;
}

void MemoryDBConnection::close()
{

	for (Serie *buffer : seriesDB)
	{
		delete buffer;
		buffer = NULL;
	}
	  seriesDB.clear();
}