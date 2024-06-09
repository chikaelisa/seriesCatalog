#include "SerieMemDAO.h"

int SerieMemDAO::lastSerieId = 0;

SerieMemDAO::SerieMemDAO(MemoryDBConnection *memoryDBConnection) : memoryDBConnection(memoryDBConnection)
{
}

SerieMemDAO::~SerieMemDAO()
{
	// TODO Auto-generated destructor stub
}

vector<Serie *> SerieMemDAO::getAllSeries()
{
	return (memoryDBConnection->getSerieList());
}

Serie *SerieMemDAO::getSerieId(int serieId)
{
	vector<Serie *> &series = memoryDBConnection->getSerieList();
	vector<Serie *>::iterator seriesIterator = series.begin();
	Serie *buffer = NULL;
	bool found = false;

	while ((!found) && (seriesIterator != series.end()))
	{

		if ((*seriesIterator)->getId() == serieId)
		{
			found = true;
			buffer = *seriesIterator;
		}
		seriesIterator++;
	}

	return (buffer);
}

void SerieMemDAO::addSerie(Serie *serie)
{
	serie->setId(++lastSerieId);
	(memoryDBConnection->getSerieList()).push_back(serie);
}

void SerieMemDAO::updateSerie(Serie *serie)
{
	deleteSerie(serie->getId());
	addSerie(serie);
}

void SerieMemDAO::deleteSerie(int serieId)
{
	vector<Serie *> &series = memoryDBConnection->getSerieList();
	vector<Serie *>::iterator seriesIterator = series.begin();
	bool found = false;

	while ((!found) && (seriesIterator != series.end()))
	{
		if ((*seriesIterator)->getId() == serieId)
		{
			found = true;
			delete *seriesIterator;
			series.erase(seriesIterator);
		}
		seriesIterator++;
	}
}