#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include <vector>
#include <iostream>

#include "MemoryDBConnection.h"
#include "AbstractSerieDAO.h"

using namespace std;

class Controller final
{
private:
	MemoryDBConnection *memoryDBConnection;
	AbstractSerieDAO *serieMemDAO;

	void seriesMenu(void);
	void reports(void);
	void help(void);
	void credits(void);
	void launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions);
	void launchReport(string title, vector<string> menuItens);

	void addSerie(void);
	void consultSerie(void);
	void editSerie(void);
	void deleteSerie(void);

	void reportOrderBy(int option);

	void showRegisteredSeries(void);

public:
	Controller();
	virtual ~Controller();
	void start();
};

#endif /* CONTROLLER_H_ */
