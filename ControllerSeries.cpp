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

void ControllerSeries::addSerie(void)
{
    Utils::printFramedMessage("Cadastro de Serie", "-", 21);

    vector<Serie *> allSeries = serieMemDAO->getAllSeries();

    Serie *newSerie = new Serie("", 0, 0, 0, "", "", "", 0);

    getName(newSerie);
    getYear(newSerie);
    getSeason(newSerie);
    getEpisodes(newSerie);
    getActors(newSerie);
    getCharacters(newSerie);

    cout << endl;

    getStreaming(newSerie);
    getRating(newSerie);

    Utils::clearConsole();

    confirmInclusion(newSerie);
}

void ControllerSeries::consultSerie(void)
{
    showRegisteredSeries();

    int id;
    cout << takeMessage(GET_ID);
    cin >> id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Serie *serie = serieMemDAO->getSerieId(id);

    Utils::clearConsole();

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
    vector<string> menuItens{"Nome", "Ano", "Temporada", "Atores",
                             "Personages", "Streaming", "Nota", "Voltar"};
    vector<void (ControllerSeries::*)(Serie *serie)> functions{
        &ControllerSeries::getName,
        &ControllerSeries::getYear,
        &ControllerSeries::getSeason,
        &ControllerSeries::getActors,
        &ControllerSeries::getCharacters,
        &ControllerSeries::getStreaming,
        &ControllerSeries::getRating,
    };
    showRegisteredSeries();

    int id;
    cout << takeMessage(GET_ID);
    cin >> id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << endl;

    Serie *serie = serieMemDAO->getSerieId(id);

    if (serie != NULL)
    {
        launchActionsGetInfo("O que deseja editar?", menuItens, serie, functions);

        cout << endl;
        serie->getAllInfo();
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
    cout << takeMessage(GET_ID);
    cin >> id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Serie *serie = serieMemDAO->getSerieId(id);

    if (serie != NULL)
    {
        serie->getAllInfo();
        char confirmation;
        do
        {
            cout << "Deseja excluir esse registro?(S/N)\nEsta acao nao pode ser desfeita.\nR:";
            cin >> confirmation;
            // TODO: arrumar toupper
            toupper(confirmation);
            if (confirmation == 'S')
            {
                serieMemDAO->deleteSerie(id);
                cout << "Serie excluida com sucesso. Retornando ao menu de series..." << endl;
                Utils::sleep(3);
                Utils::clearConsole();
            }
            else if (confirmation == 'N')
            {
                cout << "Acao cancelada. Retornado ao menu de series..." << endl;
                Utils::sleep(3);
                Utils::clearConsole();
            }

        } while (confirmation != 'N' && confirmation != 'S');
    }
    else
    {
        cout << "Nao foi possivel encontrar esse registro." << endl;
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

void ControllerSeries::launchActionsGetInfo(string title, vector<string> menuItens, Serie *serie, vector<void (ControllerSeries::*)(Serie *serie)> functions)
{
    try
    {
        Menu menu(menuItens, title, "Sua opcao: ");
        menu.setSymbol("-");

        serie->getAllInfo();

        while (int choice = menu.getChoice())
        {
            (this->*functions.at(choice - 1))(serie);
        }
    }
    catch (const exception &myException)
    {
        cout << "Um problema ocorreu." << endl;
    }
}
void ControllerSeries::getName(Serie *serie)
{
    string name;
    cout << takeMessage(GET_NAME);
    getline(cin, name);
    serie->setName(name);
}

void ControllerSeries::getYear(Serie *serie)
{
    int year;
    cout << takeMessage(GET_YEAR);
    cin >> year;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    serie->setYear(year);
}

void ControllerSeries::getSeason(Serie *serie)
{
    int season;
    cout << takeMessage(GET_SEASON);
    cin >> season;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    serie->setSeason(season);
}

void ControllerSeries::getEpisodes(Serie *serie)
{
    int numberEp;
    cout << takeMessage(GET_EPISODES);
    cin >> numberEp;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    serie->setNumberEp(numberEp);
}

void ControllerSeries::getActors(Serie *serie)
{
    cout << endl;

    string actorsConcact;
    cout << "Para terminar de incluir atores, digite 0." << endl;
    Utils::concatString(&actorsConcact, takeMessage(GET_ACTORS));
    serie->setActors(actorsConcact);
}

void ControllerSeries::getCharacters(Serie *serie)
{
    cout << endl;

    string charactersConcat;
    cout << "Para terminar de incluir personagens, digite 0." << endl;
    Utils::concatString(&charactersConcat, takeMessage(GET_CHARS));
    serie->setCharacters(charactersConcat);
}

void ControllerSeries::getStreaming(Serie *serie)
{
    string streaming;
    cout << takeMessage(GET_STREAMING);
    getline(cin, streaming);
    serie->setStreaming(streaming);
}
void ControllerSeries::getRating(Serie *serie)
{
    int rating;
    cout << takeMessage(GET_RATING);
    cin >> rating;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    serie->setRating(rating);
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

void ControllerSeries::confirmInclusion(Serie *serie)
{
    char confirmation;
    do
    {
        serie->getAllInfo();
        cout << takeMessage(CONFIRM_INCLUSION);
        cin >> confirmation;

        cout << endl;

        toupper(confirmation);

        if (confirmation == 'N')
        {
            serieMemDAO->deleteSerie(serie->getId());
            cout << takeMessage(CANCELED_INCLUSION) << endl;
            cout << endl;
            Utils::sleep(3);
            Utils::clearConsole();
        }
        else if (confirmation == 'S')
        {
            serieMemDAO->addSerie(serie);
            cout << takeMessage(SUCCESS_INCLUSION) << endl;
            cout << endl;
            Utils::sleep(3);
            Utils::clearConsole();
        }
        else
        {
            Utils::clearConsole();
        }

    } while (confirmation != 'N' && confirmation != 'S');
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

    case CONFIRM_INCLUSION:
        return "Deseja confirmar a inclusão da serie? (S/N) \nR: ";

    case CANCELED_INCLUSION:
        return "Cadastro de serie cancelado. Retornando ao menu de series...";

    case SUCCESS_INCLUSION:
        return "Serie cadastrada com sucesso. Retornando ao menu de series...";

    default:
        return "";
    }
}