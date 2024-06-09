#ifndef CONTROLLER_SERIES_H_
#define CONTROLLER_SERIES_H_

#include <string>
#include <iostream>

#include "MemoryDBConnection.h"
#include "AbstractSerieDAO.h"

using namespace std;

enum Messages
{
    GET_ID,
    GET_NAME,
    GET_YEAR,
    GET_SEASON,
    GET_EPISODES,
    GET_ACTORS,
    GET_CHARS,
    GET_STREAMING,
    GET_RATING,
    CONFIRM_INCLUSION,
    SUCCESS_INCLUSION,
    CANCELED_INCLUSION,
    REGISTERED_NOT_FOUND,

};

class ControllerSeries final
{
private:
    MemoryDBConnection *memoryDBConnection;

    void getName(Serie *serie);
    void getYear(Serie *serie);
    void getSeason(Serie *serie);
    void getEpisodes(Serie *serie);
    void getActors(Serie *serie);
    void getCharacters(Serie *serie);
    void getStreaming(Serie *serie);
    void getRating(Serie *serie);
    void showRegisteredSeries(vector<Serie *> allseries);
    void confirmInclusion(Serie *serie);
    string takeMessage(Messages type);

    void launchActionsGetInfo(string title, vector<string> menuItens, Serie *serie, vector<void (ControllerSeries::*)(Serie *serie)> functions);
    // void getInfoSerie(string title, vector<string> menuItens, Serie *serie, void (Serie::*)() function); -> passar o vector mesmo

public:
    AbstractSerieDAO *serieMemDAO;
    ControllerSeries();
    virtual ~ControllerSeries();
    void launchActionsSeries(string title, vector<string> menuItens, vector<void (ControllerSeries::*)()> functions);
    void addSerie(void);
    void consultSerie(void);
    void editSerie(void);
    void deleteSerie(void);
};

#endif /* CONTROLLER_SERIES_H_ */
