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


using namespace std;

class Controller final
	{
	private:
		void actionMovement(void);
		void actionRecurrent(void);
		void actionUsers(void);
		void actionReports(void);
		void actionHelp(void);
		void actionAbout(void);
		void launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions);

	public:
		Controller();
		virtual ~Controller();
		void start();
	};

#endif /* CONTROLLER_H_ */