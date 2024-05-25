#ifndef REPORT_H_
#define REPORT_H_

#include <iostream>
#include <vector>

#include "Serie.h"

using namespace std;

class Report {
  public:
    Report();
    /*static bool compareByTitle(Serie* serie1, Serie* serie2);
    static void orderByTitle(vector<Serie*> series);*/
    static bool compareBy(Serie* serie1, Serie* serie2, int type);
    static void orderBy(vector<Serie*> series, int type);
};

#endif