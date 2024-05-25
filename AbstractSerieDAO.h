#ifndef ABSTRACTSERIEDAO_H_
#define ABSTRACTSERIEDAO_H_

#include <vector>

#include "Serie.h"

using namespace std;

class AbstractSerieDAO
{
public:
	AbstractSerieDAO();
	virtual ~AbstractSerieDAO();

	virtual vector<Serie*> getAllSeries() = 0;
	virtual Serie *getSerieId(int serieId) = 0;
	virtual void addSerie(Serie *serie) = 0;
	virtual void updateSerie(Serie *serie) = 0;
	virtual void deleteSerie(int serieId) = 0;
};

#endif /* ABSTRACTSERIEDAO_H_ */
