/*
 * Controller.h
 *
 *  Created on: Mar 11, 2024
 *      Author: andre
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include <vector>

#include "MemoryDBConnection.h"
#include "AbstractSerieDAO.h"

using namespace std;

class Controller final
{
private:
	MemoryDBConnection *memoryDBConnection;
	AbstractSerieDAO *serieMemDAO;

	void seriesMenu(void);
	void actionRecurrent(void);
	void actionUsers(void);
	void actionReports(void);
	void actionHelp(void);
	void actionAbout(void);
	void launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions);

	void addSerie(void);
	void consultSerie(void);
	void editSerie(void);

public:
	Controller();
	virtual ~Controller();
	void start();
};

#endif /* CONTROLLER_H_ */
