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
    MESSAGE_COUNT // para tamanho do array de mapeamento

};

class ControllerSeries final
{
private:
    MemoryDBConnection *memoryDBConnection;

    void getInfoString(string *info, string message);
    void getInfoInt(int *info, string message);

    void showRegisteredSeries(void);

    string takeMessage(Messages type);

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
