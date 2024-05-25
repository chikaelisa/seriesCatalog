#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <vector>

#include "Menu.h"
#include "Controller.h"
#include "Serie.h"
#include "MemoryDBConnection.h"
#include "SerieMemDAO.h"
#include "AbstractSerieDAO.h"
#include "Report.h"

using namespace std;

Controller::Controller()
{
	cout << "Constructor" << endl;
	memoryDBConnection = new MemoryDBConnection();
	serieMemDAO = new SerieMemDAO(new MemoryDBConnection());

	serieMemDAO->addSerie(new Serie("Elementary", 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8));
	serieMemDAO->addSerie(new Serie("Sex Education", 2024, 3, 16, {"Rosa", "Andre", "Ste"}, {"Enzo", "Pietra"}, "Prime Vide", 8));
	serieMemDAO->addSerie(new Serie("Flash", 2024, 3, 20, {"Genilda", "Chika", "Amarildo"}, {"Enzo", "Pietra"}, "Max", 8));
}

Controller::~Controller()
{
	// nothing
}

void Controller::start()
{
	vector<string> menuItens{"Series", "Relatorios", "Ajuda", "Creditos", "Sair"};
	vector<void (Controller::*)()> functions{&Controller::seriesMenu, &Controller::reports, &Controller::actionReports, &Controller::actionHelp, &Controller::actionAbout};
	launchActions("Main Menu", menuItens, functions);
}

void Controller::seriesMenu(void)
{
	vector<string> menuItens{"Cadastrar nova serie", "Consultar serie", "Editar serie", "Excluir serie", "Voltar"};
	vector<void (Controller::*)()> functions{&Controller::addSerie, &Controller::consultSerie, &Controller::editSerie, &Controller::deleteSerie, &Controller::actionAbout};
	launchActions("Gerenciar Series", menuItens, functions);
}

void Controller::reports(void)
{
	vector<string> menuItens{"Ordenados por titulo", "Ordenados por streaming", "Ordenados por ano", "Ordenados por nota", "Voltar"};
	vector<void (Controller::*)()> functions{&Controller::orderByTitle, &Controller::consultSerie, &Controller::editSerie, &Controller::deleteSerie, &Controller::actionAbout};
	launchActions("Gerenciar Series", menuItens, functions);
}

void Controller::addSerie(void)
{
	vector<Serie *> allSeries = serieMemDAO->getAllSeries();
	cout << "Nome da serie numero 0: " << allSeries.at(0)->getId() << endl;

	string name;
	cout << "Digite o nome da serie" << endl;
	getline(cin, name);

	int year;
	cout << "Digite o ano da serie" << endl;
	cin >> year;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int season;
	cout << "Digite a temporada" << endl;
	cin >> season;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int numberEp;
	cout << "Digite o numero de episodios" << endl;
	cin >> numberEp;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string actors;
	cout << "Digite um ator" << endl;
	getline(cin, actors);

	vector<string> allActors;
	allActors.push_back(actors);

	string characters;
	cout << "Digite um personagem" << endl;
	getline(cin, characters);

	vector<string> allChars;
	allChars.push_back(characters);

	string streamming;
	cout << "Digite o streamming" << endl;
	getline(cin, streamming);

	int rating;
	cout << "Digite o rating" << endl;
	cin >> rating;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	serieMemDAO->addSerie(new Serie(name, year, season, numberEp, allActors, allChars, streamming, rating));
}

void Controller::consultSerie(void)
{
	vector<Serie *> allseries = serieMemDAO->getAllSeries();
	// for (int i = 0; i < allseries.size(); i++)
	// {
	// 	allseries[i]->getAllInfo();
	// }

	int id;
	cout << "Digite o ID da serie" << endl;
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Serie *serie = serieMemDAO->getSerieId(id);

	if (serie != NULL)
	{
		serie->getAllInfo();
	}
	else
	{
		cout << "Nao foi possivel encontrar esse registro" << endl;
	}
}

void Controller::editSerie(void)
{
	int id;
	cout << "Digite o ID da serie" << endl;
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Serie *serie = serieMemDAO->getSerieId(id);

	// Serie a = *serie; como passar um valor por copia e nao referencia?  como utilizar o update:

	if (serie != NULL)
	{
		string name;
		cout << "Digite o nome da serie" << endl;
		getline(cin, name);
		serie->setName(name);

		int year;
		cout << "Digite o ano da serie" << endl;
		cin >> year;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setYear(year);

		int season;
		cout << "Digite a temporada" << endl;
		cin >> season;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setSeason(season);

		int numberEp;
		cout << "Digite o numero de episodios" << endl;
		cin >> numberEp;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setNumberEp(numberEp);

		string actors;
		cout << "Digite um ator" << endl;
		getline(cin, actors);

		vector<string> allActors;
		allActors.push_back(actors);

		serie->setActors(allActors);

		string characters;
		cout << "Digite um personagem" << endl;
		getline(cin, characters);

		vector<string> allChars;
		allChars.push_back(characters);

		serie->setCharacters(allChars);

		string streamming;
		cout << "Digite o streamming" << endl;
		getline(cin, streamming);
		serie->setStreamming(streamming);

		int rating;
		cout << "Digite o rating" << endl;
		cin >> rating;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		serie->setRating(rating);

		// serieMemDAO->updateSerie(serie);
	}
	else
	{
		cout << "Nao foi possivel encontrar esse registro" << endl;
	}
}

void Controller::deleteSerie(void)
{
	int id;
	cout << "Digite o ID da serie" << endl;
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

void Controller::orderByTitle(void)
{
	vector<Serie*> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	report->orderByTitle(series);
}

void Controller::actionRecurrent(void)
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
