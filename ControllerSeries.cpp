#include <iomanip>
#include <memory>
#include <exception>
#include <cctype>

#include "ControllerSeries.h"

#include "Utils.h"
#include "Menu.h"
#include "Serie.h"
#include "MemoryDBConnection.h"
#include "SerieMemDAO.h"
#include "AbstractSerieDAO.h"

ControllerSeries::ControllerSeries()
{
    serieMemDAO = new SerieMemDAO(new MemoryDBConnection());

    serieMemDAO->addSerie(new Serie("Elementary", 2021, 3, 24, "Fernanda, Chika, Ste", "Enzo, Pietra", "Netflix", 10));
    serieMemDAO->addSerie(new Serie("Sex Education", 2024, 3, 16, "Rosa, Andre, Ste", "Enzo, Pietra", "Prime Video", 8));
    serieMemDAO->addSerie(new Serie("Flash", 2022, 3, 20, "Genilda, Chika, Amarildo", "Enzo, Pietra", "Max", 5));
    serieMemDAO->addSerie(new Serie("B99", 2022, 3, 20, "Márcia Aragão, Rosa da Silva, Fábio Porchat", "Jake Peral, Amy, Boyle", "HBO Max", 5));
}

ControllerSeries::~ControllerSeries()
{
    // nothing
}

void ControllerSeries::getInfoString(string *info, string message)
{
    string newInfo;
    cout << message;
    getline(cin, newInfo);
    *info = newInfo;
}

void ControllerSeries::getInfoInt(int *info, string message)
{
    int newInfo;
    cout << message;
    cin >> newInfo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    *info = newInfo;
}

void ControllerSeries::showRegisteredSeries(void)
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

string ControllerSeries::takeMessage(Messages type)
{
    switch (type)
    {
    case GET_ID:
        return "Digite o ID da serie: ";

    case GET_NAME:
        return "Digite o nome da serie: ";

    case GET_ACTORS:
        return "Digite um ator: ";

    case GET_CHARS:
        return "Digite um personagem: ";

    case GET_RATING:
        return "Digite a nota da serie: ";

    case GET_EPISODES:
        return "Digite o numero de episodios: ";

    case GET_SEASON:
        return "Digite a temporada: ";

    case GET_YEAR:
        return "Digite o ano da serie: ";

    case GET_STREAMING:
        return "Digite o streaming: ";

    default:
        return "";
    }
}

void ControllerSeries::addSerie(void)
{
    Utils::printFramedMessage("Cadastro de Serie", "-", 21);

    vector<Serie *> allSeries = serieMemDAO->getAllSeries();

    string name;
    getInfoString(&name, takeMessage(GET_NAME));

    int year;
    getInfoInt(&year, takeMessage(GET_YEAR));

    int season;
    getInfoInt(&season, takeMessage(GET_SEASON));

    int numberEp;
    getInfoInt(&numberEp, takeMessage(GET_EPISODES));

    cout << endl;
    cout << "Para terminar de incluir atores, digite 0." << endl;
    string actorsConcact;
    Utils::concatString(&actorsConcact, takeMessage(GET_ACTORS));

    cout << endl;
    cout << "Para terminar de incluir personagens, digite 0." << endl;
    string charactersConcat = "";
    Utils::concatString(&charactersConcat, takeMessage(GET_CHARS));

    cout << endl;

    string streaming;
    getInfoString(&streaming, takeMessage(GET_STREAMING));

    int rating;
    getInfoInt(&rating, takeMessage(GET_RATING));

    Utils::clearConsole();

    Serie *newSerie = new Serie(name, year, season, numberEp, actorsConcact, charactersConcat, streaming, rating);

    string confirmation;
    do
    {
        newSerie->getAllInfo();
        getInfoString(&confirmation, "Deseja confirmar a inclusão da serie? (S/N) \nR: ");
        cout << endl;

        for (char &c : confirmation)
            c = std::toupper(c);

        if (confirmation == "N")
        {
            serieMemDAO->deleteSerie(newSerie->getId());
            cout << "Cadastro de serie cancelado. Retornando ao menu de series..." << endl;
            cout << endl;
            Utils::sleep(3);
            Utils::clearConsole();
        }
        else if (confirmation == "S")
        {
            serieMemDAO->addSerie(newSerie);
            cout << "Serie cadastrada com sucesso. Retornando ao menu de series..." << endl;
            cout << endl;
            Utils::sleep(3);
            Utils::clearConsole();
        }
        else
        {
            Utils::clearConsole();
        }

    } while (confirmation != "N" && confirmation != "S");
}

void ControllerSeries::consultSerie(void)
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

void ControllerSeries::editSerie(void)
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

void ControllerSeries::deleteSerie(void)
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

void ControllerSeries::launchActionsSeries(string title, vector<string> menuItens, vector<void (ControllerSeries::*)()> functions)
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

// string ControllerSeries::messageText(Messages message)
// {
//     switch (message)
//     {
//     case GET_ID:
//         return "Digite o ID da serie: ";
//     case GET_NAME:
//         return "Digite o nome da serie: ";

//     default:
//         return "";
//     }
// }