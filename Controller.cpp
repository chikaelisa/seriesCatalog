#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <vector>
#include <windows.h>

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
	vector<void (Controller::*)()> functions{&Controller::orderByTitle, &Controller::orderByStreaming, &Controller::orderByYear, &Controller::orderByRating};
	launchActions("Gerenciar Series", menuItens, functions);
}

void Controller::addSerie(void)
{
	Utils::printFramedMessage("Cadastro de Serie", "*", 21);

	vector<Serie *> allSeries = serieMemDAO->getAllSeries();

	string name;
	cout << "Digite o nome da serie: ";
	getline(cin, name);

	int year;
	cout << "Digite o ano da serie: ";
	cin >> year;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int season;
	cout << "Digite a temporada: ";
	cin >> season;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int numberEp;
	cout << "Digite o numero de episodios: ";
	cin >> numberEp;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << endl;

	cout << "Para terminar de incluir atores, digite 0." << endl;
	string actors;
	string actorsConcact;

	do
	{

		cout << "Digite um ator: ";
		getline(cin, actors);
		actorsConcact.append(actors).append(", ");
		if (actors == "0")
			actorsConcact.pop_back();

	} while (actors != "0");

	cout << endl;

	cout << "Para terminar de incluir personagens, digite 0." << endl;
	string characters;
	string charactersConcat = "";

	do 
	{

		cout << "Digite um personagem: ";
		getline(cin, characters);
		charactersConcat.append(characters).append(", ");
		if (characters == "0")
			charactersConcat.pop_back();

	} while (characters != "0");

	cout << endl;

	string streamming;
	cout << "Digite o streamming: ";
	getline(cin, streamming);

	int rating;
	cout << "Digite o rating: ";
	cin >> rating;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	system("cls");

	Serie *newSerie = new Serie(name, year, season, numberEp, actorsConcact, charactersConcat, streamming, rating);
	serieMemDAO->addSerie(newSerie);
	newSerie->getAllInfo();

	char confirmation;
	cout << endl;
	cout << "Deseja confirmar a inclusão da serie? (S/N)" << endl;
	cout << "R: ";
	cin >> confirmation;
	cout << endl;

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (confirmation == 'N')
	{
		serieMemDAO->deleteSerie(newSerie->getId());
		cout << "Cadastro de serie cancelado. Retornando ao menu de series...";
	}
	else
		cout << "Serie cadastrada com sucesso. Retornando ao menu de series...";

	Sleep(4000);

	system("cls");

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
		cout << "Digite o nome da serie: ";
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
		string actorsConcact;

		do
		{

			cout << "Digite um ator: ";
			getline(cin, actors);
			actorsConcact.append(actors).append(", ");
			if (actors == "0")
				actorsConcact.erase(actorsConcact.size() - 1);

		} while (actors != "0");

		serie->setActors(actorsConcact);

		string characters;
		string charactersConcat;

		do 
		{

			cout << "Digite um personagem: ";
			getline(cin, characters);
			charactersConcat.append(characters).append(", ");
			if (characters == "0")
				charactersConcat.erase(charactersConcat.size() - 1);

		} while (characters != "0");

		serie->setCharacters(charactersConcat);

		string streaming;
		cout << "Digite o streaming" << endl;
		getline(cin, streaming);
		serie->setStreamming(streaming);

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
