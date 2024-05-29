
#include <string>
#include <iostream>
#include <vector>

#include "Serie.h"
#include "Utils.h"

using namespace std;

Serie::Serie(int id, string name, int year, int season, int numberEp, string actors, string characters, string streamming, int rating) : id(id), name(name), year(year), season(season), numberEp(numberEp), actors(actors), characters(characters), streamming(streamming), rating(rating)
{
}
Serie::Serie(string name, int year, int season, int numberEp, string actors, string characters, string streamming, int rating) : name(name), year(year), season(season), numberEp(numberEp), actors(actors), characters(characters), streamming(streamming), rating(rating)
{
    this->id = 0;
}
Serie::~Serie()
{
}

/*
void Serie::printVectorString(const vector<string> &vec, string separator = ", ")
{
    for (auto elem : vec)
    {
        cout << elem;
        if (elem != vec.back())
            cout << separator;
    }

    cout << endl;
}
*/

int Serie::getId() const
{
    return id;
}

void Serie::setId(int id)
{
    if (this->id == 0)
    {
        this->id = id;
    }
    else
    {
        throw new runtime_error("Operacao invalida. Use um id valido.");
    }
}

string Serie::getName()
{
    return name;
}
void Serie::setName(string name)
{
    this->name = name;
}

int Serie::getYear()
{
    return year;
}
void Serie::setYear(int year)
{
    this->year = year;
}

int Serie::getSeason()
{
    return season;
}
void Serie::setSeason(int season)
{
    this->season = season;
}

int Serie::getNumberEp()
{
    return numberEp;
}
void Serie::setNumberEp(int numberEp)
{
    this->numberEp = numberEp;
}

string Serie::getActors()
{
    return actors;
}
void Serie::setActors(string actors)
{
    this->actors = actors;
}

string Serie::getCharacters()
{
    return characters;
}

void Serie::setCharacters(string characters)
{
    this->characters = characters;
}

string Serie::getStreamming()
{
    return streamming;
}
void Serie::setStreamming(string streamming)
{
    this->streamming = streamming;
}

int Serie::getRating()
{
    return rating;
}

void Serie::setRating(int rating)
{
    this->rating = rating;
}

void Serie::getAllInfo()
{
    cout << "------------------" << endl;
    cout << "Id: " << this->getId() << endl;
    cout << "Nome: " << this->getName() << endl;
    cout << "Ano: " << this->getYear() << endl;
    cout << "Temporada: " << this->getSeason() << endl;
    cout << "Numero de episodios: " << this->getNumberEp() << endl;
    cout << "Atores: " << this->getActors() << endl;
    cout << "Personagens: " << this->getCharacters() << endl;
    cout << "Streaming: " << this->getStreamming() << endl;
    cout << "Nota: " << this->getRating() << endl;
    cout << "------------------" << endl;
}
