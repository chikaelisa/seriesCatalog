
#include "Serie.h"
#include "Utils.h"

Serie::Serie(int id, string name, int year, int season, int numberEp, string actors, string characters, string streaming, int rating) : id(id), name(name), year(year), season(season), numberEp(numberEp), actors(actors), characters(characters), streaming(streaming), rating(rating)
{
}
Serie::Serie(string name, int year, int season, int numberEp, string actors, string characters, string streaming, int rating) : name(name), year(year), season(season), numberEp(numberEp), actors(actors), characters(characters), streaming(streaming), rating(rating)
{
    this->id = 0;
}
Serie::~Serie()
{
}

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

string Serie::getStreaming()
{
    return streaming;
}
void Serie::setStreaming(string streaming)
{
    this->streaming = streaming;
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
    if (this->getId() != 0)
        cout << "Id: " << this->getId() << endl;

    cout << "Nome: " << this->getName() << endl;
    cout << "Ano: " << this->getYear() << endl;
    cout << "Temporada: " << this->getSeason() << endl;
    cout << "Numero de episodios: " << this->getNumberEp() << endl;
    cout << "Atores: " << this->getActors() << endl;
    cout << "Personagens: " << this->getCharacters() << endl;
    cout << "Streaming: " << this->getStreaming() << endl;
    cout << "Nota: " << this->getRating() << endl;
    cout << endl;
}
