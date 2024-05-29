
#ifndef SERIE_H_
#define SERIE_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Serie
{
private:
    int id;
    string name;
    int year;
    int season;
    int numberEp;
    string actors;
    string characters;
    string streamming;
    int rating;
    //void printVectorString(const vector<string> &vec, string sep);

public:
    Serie(int id, string name, int year, int season, int numberEp, string actors, string characters, string streamming, int rating);
    Serie(string name, int year, int season, int numberEp, string actors, string characters, string streamming, int rating);
    virtual ~Serie();

    int getId() const;
    void setId(int id);

    string getName();
    void setName(string name);

    int getYear();
    void setYear(int year);

    int getSeason();
    void setSeason(int season);

    int getNumberEp();
    void setNumberEp(int numberEp);

    string getActors();
    void setActors(string actors);

    string getCharacters();
    void setCharacters(string characters);

    string getStreamming();
    void setStreamming(string streamming);

    int getRating();
    void setRating(int rating);

    void getAllInfo();
};

#endif /* SERIE_H_ */
