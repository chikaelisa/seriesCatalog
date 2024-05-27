#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <vector>

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

	serieMemDAO->addSerie(new Serie("Elementary", 2021, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 10));
	serieMemDAO->addSerie(new Serie("Sex Education", 2024, 3, 16, {"Rosa", "Andre", "Ste"}, {"Enzo", "Pietra"}, "Prime Video", 8));
	serieMemDAO->addSerie(new Serie("Flash", 2022, 3, 20, {"Genilda", "Chika", "Amarildo"}, {"Enzo", "Pietra"}, "Max", 5));
}

Controller::~Controller()
{
	// nothing
}

void Controller::start()
{
	vector<string> menuItens{"Series", "Relatorios", "Ajuda", "Creditos", "Sair"};
	vector<void (Controller::*)()> functions{&Controller::seriesMenu, &Controller::reports, &Controller::help, &Controller::credits};
	launchActions("Main Menu", menuItens, functions);
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
	vector<void (Controller::*)()> functions{&Controller::orderByTitle, &Controller::orderByStreaming, &Controller::orderByYear, &Controller::orderByRating};
	launchActions("Gerenciar Series", menuItens, functions);
}

void Controller::addSerie(void)
{
	vector<Serie *> allSeries = serieMemDAO->getAllSeries();

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

	cout << "Para terminar de incluir atores, digite 0" << endl;
	string actors;
	vector<string> allActors;

	do
	{
		cout << "Digite um ator" << endl;
		getline(cin, actors);
		if (actors != "0")
			allActors.push_back(actors);

	} while (actors != "0");

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
		cout << "Digite a nota" << endl;
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
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	// report->orderByTitle(series);
	report->orderBy(series, 1);
}

void Controller::orderByStreaming(void)
{
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	// report->orderByTitle(series);
	report->orderBy(series, 2);
}

void Controller::orderByYear(void)
{
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	// report->orderByTitle(series);
	report->orderBy(series, 3);
}

void Controller::orderByRating(void)
{
	vector<Serie *> series = serieMemDAO->getAllSeries();
	Report *report = new Report();
	// report->orderByTitle(series);
	report->orderBy(series, 4);
}

void Controller::help(void)
{
	Utils::printMessage(SysInfo::getFullVersion() + " | Help");
	unique_ptr<TextFromFile> textFromFile(new TextFromFile(SysInfo::getHelpFile()));
	Utils::printFramedMessage(textFromFile->getFileContent(), "*", 120);
}

void Controller::credits(void)
{
	string text = "";
	text += SysInfo::getFullVersion() + "\n";
	text += SysInfo::getAuthor() + "\n";
	text += SysInfo::getInstitution() + "\n";
	text += SysInfo::getDepartment() + "\n";
	text += "Copyright " + SysInfo::getAuthor() + " " + SysInfo::getDate() + "\n";
	Utils::printMessage(SysInfo::getVersion() + " | About");
	Utils::printFramedMessage(text, "*", 120);
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
