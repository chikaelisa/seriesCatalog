#include <iostream>
#include <algorithm>

#include "Report.h"

using namespace std;

Report::Report() {}

bool Report::compareBy(Serie *serie1, Serie *serie2, int type)
{
    if (type == 1)
        return serie1->getName() < serie2->getName();

    if (type == 2)
        return serie1->getStreaming() < serie2->getStreaming();

    if (type == 3)
        return serie1->getYear() < serie2->getYear();

    if (type == 4)
        return serie1->getRating() > serie2->getRating();

    return false; // opcao invalida
}

/*
bool Report::compareByTitle(Serie* serie1, Serie* serie2)
{
    return serie1->getName() < serie2->getName();
}

bool Report::compareByStreaming(Serie* serie1, Serie* serie2)
{
    return serie1->getStreaming() < serie2->getStreaming();
}

void Report::orderByTitle(vector<Serie*> series)
{
    sort(series.begin(), series.end(), compareByTitle);
    for (const auto& serie : series)
    {
        serie->getAllInfo();
    }
}

void Report::orderByStreaming(vector<Serie*> series)
{
    sort(series.begin(), series.end(), compareByStreaming);
    for (const auto& serie : series)
    {
        serie->getAllInfo();
    }
}
*/

void Report::orderBy(vector<Serie *> series, int type)
{
    auto compare = [type](Serie *s1, Serie *s2)
    {
        return Report::compareBy(s1, s2, type);
    };

    sort(series.begin(), series.end(), compare);

    for (const auto &serie : series)
    {
        serie->getAllInfo();
    }
}