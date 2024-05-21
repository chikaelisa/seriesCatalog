/*
 * Controller.cpp
 *
 *  Created on: Mar 11, 2024
 *      Author: andre
 */

#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <vector>

#include "Menu.h"
#include "Controller.h"
#include "Serie.h"
#include "MemoryDBConnection.h"

using namespace std;

Controller::Controller()
{
	cout << "Constructor" << endl;
	memoryDBConnection = new MemoryDBConnection();

	vector<Serie> series {  
		Serie(4, "Elementary", 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8),
		Serie(4, "Elementary", 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8),
		Serie(4, "Elementary", 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8),
	};

	serieDAO = new SerieMemDAO(new MemoryDBConnection());
	
}

Controller::~Controller()
{
	// nothing
}

void Controller::start()
{
	vector<string> menuItens{"Series", "Relatorios", "Ajuda", "Creditos", "Sair"};
	vector<void (Controller::*)()> functions{&Controller::actionMovement, &Controller::actionUsers, &Controller::actionReports, &Controller::actionHelp, &Controller::actionAbout};
	launchActions("Main Menu", menuItens, functions);
}

void Controller::actionMovement(void)
{
	Serie serie1(4, "Elementary", 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8);
	int rate = serie1.getRating();
	cout << "Nome da serie: " << serie1.getName() << endl;
	cout << "Nota da serie: " << to_string(rate) << endl;
	// cout << "Nome dos personagens: " << serie1.getCharacters() << endl;
}

void Controller::actionRecurrent(void)
{
	cout << "actionUsers" << endl;
}

void Controller::actionUsers(void)
{
	cout << "actionUsers" << endl;
}

void Controller::actionReports(void)
{
	cout << "actionReports" << endl;
}

void Controller::actionHelp(void)
{
	cout << "actionHelp" << endl;
}

void Controller::actionAbout(void)
{
	cout << "actionAbout" << endl;
}

void Controller::launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions)
{
	try
	{
		Menu menu(menuItens, title, "Your option: ");
		menu.setSymbol("*");

		while (int choice = menu.getChoice())
		{
			(this->*functions.at(choice - 1))();
		}
	}
	catch (const exception &myException)
	{
		cout << " ERRRRRRRRou!" << endl;
	}
}
