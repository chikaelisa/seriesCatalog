#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include <vector>
#include <iostream>

#include "AbstractSerieDAO.h"
#include "ControllerSeries.h"

using namespace std;

class Controller final
{
private:
	AbstractSerieDAO *serieMemDAO;
	ControllerSeries *controllerSeries;

	void seriesMenu(void);
	void reports(void);
	void help(void);
	void credits(void);
	void launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions);
	void launchReport(string title, vector<string> menuItens);

	void reportOrderBy(int option);

public:
	Controller();
	virtual ~Controller();
	void start();
};

#endif /* CONTROLLER_H_ */
