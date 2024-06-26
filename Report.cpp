#include <algorithm>

#include "Report.h"

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