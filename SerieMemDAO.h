
#ifndef SERIEMEMDAO_H_
#define SERIEMEMDAO_H_

#include "AbstractSerieDAO.h"
#include "MemoryDBConnection.h"

class SerieMemDAO : public AbstractSerieDAO
{
private:
	MemoryDBConnection *memoryDBConnection;
	static int lastSerieId;

public:
	SerieMemDAO(MemoryDBConnection *memoryDBConnection);
	virtual ~SerieMemDAO();

	vector<Serie *> getAllSeries();
	Serie *getSerieId(int serieId);
	void addSerie(Serie *serie);
	void updateSerie(Serie *serie);
	void deleteSerie(int serieId);
};

#endif