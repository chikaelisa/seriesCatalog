#include "MemoryDBConnection.h"

MemoryDBConnection::MemoryDBConnection()
{
	seriesDB = vector<Serie *>();
}

MemoryDBConnection::~MemoryDBConnection()
{
	close();
}

vector<Serie *> &MemoryDBConnection::getSerieList()
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