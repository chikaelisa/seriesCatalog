#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <vector>
//#include <windows.h>
// #include <unistd.h>
#include <ctype.h>

#include "Utils.h"
#include "Menu.h"
#include "TextFromFile.h"
#include "Controller.h"
#include "Serie.h"
#include "MemoryDBConnection.h"
#include "SerieMemDAO.h"
#include "AbstractSerieDAO.h"
#include "Report.h"
#include "SysInfo.h"

using namespace std;

Controller::Controller()
{
	cout << "Boas vindas ao Catalogo de Series" << endl;
	memoryDBConnection = new MemoryDBConnection();
	serieMemDAO = new SerieMemDAO(new MemoryDBConnection());

	serieMemDAO->addSerie(new Serie("Elementary", 2021, 3, 24, "Fernanda, Chika, Ste", "Enzo, Pietra", "Netflix", 10));
	serieMemDAO->addSerie(new Serie("Sex Education", 2024, 3, 16, "Rosa, Andre, Ste", "Enzo, Pietra", "Prime Video", 8));
	serieMemDAO->addSerie(new Serie("Flash", 2022, 3, 20, "Genilda, Chika, Amarildo", "Enzo, Pietra", "Max", 5));
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
	vector<void (Controller::*)()> functions{&Controller::addSerie, &Controller::consultSerie, &Controller::editSerie, &Controller::deleteSerie};
	launchActions("Gerenciar Series", menuItens, functions);
}

void Controller::reports(void)
{
	vector<string> menuItens{"Ordenados por titulo", "Ordenados por streaming", "Ordenados por ano", "Ordenados por nota", "Voltar"};
	launchReport("Gerenciar Series", menuItens);
}

void Controller::getInfoString(string *info, string message) 
{
	string newInfo;
	cout << message;
	getline(cin, newInfo);
	*info = newInfo;
}

void Controller::getInfoInt(int *info, string message)
{
	int newInfo;
	cout << message;
	cin >> newInfo;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	*info = newInfo;
}

void Controller::addSerie(void)
{
	Utils::printFramedMessage("Cadastro de Serie", "-", 21);

	vector<Serie *> allSeries = serieMemDAO->getAllSeries();

	string name;
	getInfoString(&name, "Digite o nome da serie: ");

	int year;
	getInfoInt(&year, "Digite o ano da serie: ");

	int season;
	getInfoInt(&season, "Digite a temporada: ");

	int numberEp;
	getInfoInt(&numberEp, "Digite o numero de episodios: ");

	cout << endl;
	cout << "Para terminar de incluir atores, digite 0." << endl;
	string actorsConcact;
	Utils::concatString(&actorsConcact, "Digite um ator: ");

	cout << endl;
	cout << "Para terminar de incluir personagens, digite 0." << endl;
	string charactersConcat = "";
	Utils::concatString(&charactersConcat, "Digite um personagem: ");

	cout << endl;

	string streaming;
	getInfoString(&streaming, "Digite o streaming: ");

	int rating;
	getInfoInt(&rating, "Digite a nota: ");

	Utils::clearConsole();

	Serie *newSerie = new Serie(name, year, season, numberEp, actorsConcact, charactersConcat, streaming, rating);
	newSerie->getAllInfo();

	string confirmation;
	getInfoString(&confirmation, "Deseja confirmar a inclusão da serie? (S/N) \nR: ");
	cout << endl;

	Utils::clearConsole();

	if (confirmation == "N")
	{
		serieMemDAO->deleteSerie(newSerie->getId());
		cout << "Cadastro de serie cancelado. Retornando ao menu de series..." << endl;
		cout << endl;
	}
	else
	{
		serieMemDAO->addSerie(newSerie);
		cout << "Serie cadastrada com sucesso. Retornando ao menu de series..." << endl;
		cout << endl;
	}
}

void Controller::consultSerie(void)
{
	showRegisteredSeries();

	int id;
	cout << "Digite o ID da serie que deseja consultar: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Utils::clearConsole();

	Serie *serie = serieMemDAO->getSerieId(id);

	if (serie != NULL)
	{
		Utils::printFramedMessage(serie->getName(), "-", serie->getName().length());
		serie->getAllInfo();
	}
	else
	{
		cout << "Nao foi possivel encontrar esse registro" << endl;
	}
}

void Controller::editSerie(void)
{
	showRegisteredSeries();

	int id;
	cout << "Digite o ID da serie: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << endl;

	Serie *serie = serieMemDAO->getSerieId(id);

	if (serie != NULL)
	{
		string name;
		cout << "Digite o nome da serie: ";
		getline(cin, name);
		serie->setName(name);

		int year;
		cout << "Digite o ano da serie: ";
		cin >> year;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setYear(year);

		int season;
		cout << "Digite a temporada: ";
		cin >> season;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setSeason(season);

		int numberEp;
		cout << "Digite o numero de episodios: ";
		cin >> numberEp;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setNumberEp(numberEp);

		cout << endl;
		string actorsConcact;
		cout << "Para terminar de incluir atores, digite 0." << endl;
		Utils::concatString(&actorsConcact, "Digite um ator: ");
		serie->setActors(actorsConcact);
		cout << endl;

		string charactersConcat;
		cout << "Para terminar de incluir personagens, digite 0." << endl;
		Utils::concatString(&charactersConcat, "Digite um personagem: ");
		cout << endl;

		serie->setCharacters(charactersConcat);

		string streaming;
		cout << "Digite o streaming: ";
		getline(cin, streaming);
		serie->setStreaming(streaming);

		int rating;
		cout << "Digite a nota: ";
		cin >> rating;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setRating(rating);

		cout << endl;
	}
	else
	{
		cout << "Nao foi possivel encontrar esse registro" << endl;
	}
}

void Controller::deleteSerie(void)
{
	showRegisteredSeries();

	int id;
	cout << "Digite o ID da serie: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Serie *serie = serieMemDAO->getSerieId(id);

	if (serie != NULL)
	{
		serieMemDAO->deleteSerie(id);
		cout << "Serie excluida com sucesso" << endl;
	}
	else
	{
		cout << "Nao foi possivel encontrar esse registro" << endl;
	}
}

void Controller::reportOrderBy(int option)
{
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	report->orderBy(series, option);
}

void Controller::showRegisteredSeries(void)
{
	vector<Serie *> allseries = serieMemDAO->getAllSeries();

	Utils::printFramedMessage("Series Cadastradas", "*", 21);
	cout << endl;

	for (int i = 0; i < allseries.size(); i++)
	{
		cout << "ID: " << allseries[i]->getId() << " Nome: " << allseries[i]->getName() << endl;
	}
	cout << endl;
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
