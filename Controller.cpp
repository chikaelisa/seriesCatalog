#include <iomanip>
#include <memory>
#include <exception>
// #include <windows.h>
//  #include <unistd.h>
#include <ctype.h>

#include "Utils.h"
#include "Menu.h"
#include "TextFromFile.h"
#include "Controller.h"
#include "Serie.h"
#include "MemoryDBConnection.h"
#include "Report.h"
#include "SysInfo.h"
#include "ControllerSeries.h"

using namespace std;

Controller::Controller()
{
	cout << "Boas vindas ao Catalogo de Series" << endl;
	controllerSeries = new ControllerSeries();
	serieMemDAO = controllerSeries->serieMemDAO;
}

Controller::~Controller()
{
	// nothing
}

void Controller::start()
{
	vector<string> menuItens{"Series", "Relatorios", "Ajuda", "Creditos", "Sair"};
	vector<void (Controller::*)()> functions{&Controller::seriesMenu, &Controller::reports, &Controller::help, &Controller::credits};
	launchActions("Menu Principal", menuItens, functions);
}

void Controller::seriesMenu(void)
{
	vector<string> menuItens{"Cadastrar nova serie", "Consultar serie", "Editar serie", "Excluir serie", "Voltar"};
	vector<void (ControllerSeries::*)()> functions{&ControllerSeries::addSerie, &ControllerSeries::consultSerie, &ControllerSeries::editSerie, &ControllerSeries::deleteSerie};
	controllerSeries->launchActionsSeries("Gerenciar Series", menuItens, functions);
}

void Controller::reports(void)
{
	vector<string> menuItens{"Ordenados por titulo", "Ordenados por streaming", "Ordenados por ano", "Ordenados por nota", "Voltar"};
	launchReport("Gerenciar Series", menuItens);
}

void Controller::reportOrderBy(int option)
{
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	report->orderBy(series, option);
}

void Controller::help(void)
{
	Utils::printMessage(SysInfo::getFullVersion() + " | Ajuda");
	cout << endl;
	unique_ptr<TextFromFile> textFromFile(new TextFromFile(SysInfo::getHelpFile()));
	cout << textFromFile->getFileContent() << endl;
}

void Controller::credits(void)
{
	string text = "";
	text += SysInfo::getFullVersion() + "\n";
	text += SysInfo::getAuthor() + "\n";
	text += SysInfo::getInstitution() + "\n";
	text += SysInfo::getDepartment() + "\n";
	text += "Copyright " + SysInfo::getAuthor() + " " + SysInfo::getDate();
	Utils::printMessage(SysInfo::getVersion() + " | Sobre");
	cout << endl;
	cout << text << endl;
	cout << endl;
}

void Controller::launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions)
{
	try
	{
		Menu menu(menuItens, title, "Sua opcao: ");
		menu.setSymbol("*");

		while (int choice = menu.getChoice())
		{
			(this->*functions.at(choice - 1))();
		}
	}
	catch (const exception &myException)
	{
		cout << "Um problema ocorreu." << endl;
	}
}

void Controller::launchReport(string title, vector<string> menuItens)
{
	try
	{
		Menu menu(menuItens, title, "Sua opcao: ");
		menu.setSymbol("*");

		while (int choice = menu.getChoice())
		{
			(this->reportOrderBy(choice));
		}
	}
	catch (const exception &myException)
	{
		cout << "Um problema ocorreu." << endl;
	}
}
