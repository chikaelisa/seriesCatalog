#include <iostream>
#include <algorithm>

#include "Report.h"

using namespace std;

Report::Report() { }

bool Report::compareByTitle(Serie* serie1, Serie* serie2) 
{
    string nameSerie1 = serie1->getName();
    string nameSerie2 = serie2->getName();
    return nameSerie1 < nameSerie2;
}

void Report::orderByTitle(vector<Serie*> series) 
{
    sort(series.begin(), series.end(), compareByTitle);
    for (const auto& serie : series) 
    {
        serie->getAllInfo();
    }
}