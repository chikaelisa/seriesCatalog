
#include <string>
#include<iostream>
#include <vector>

#include "Serie.h"

using namespace std;



// Serie
// 	{
	// private:
    //     int id;
	// 	string name;
	// 	int year;
	// 	int season;
	// 	int numberEp;
	// 	vector<string> actors;
	// 	vector<string> characters;
	// 	string streamming;
    //     int rating;

	// public:
        // (4, Elementary, 2024, 3, 24, {"Fernanda", "Chika", "Ste"}, {"Enzo", "Pietra"}, "Netflix", 8)
        Serie::Serie(int id, string name, int year, int season, int numberEp, vector<string> actors, vector<string>characters, string streamming, int rating):
            id(id), name(name), year(year), season(season), numberEp(numberEp), actors(actors), characters(characters), streamming(streamming), rating(rating)
            {
            }
        //Serie(int id)
        Serie::~Serie()
        {
        }
		
        int Serie::getId() const
        {
            return id;
        }

       // void setId(int id);

		string Serie::getName()
        {
            return name;
        }
        void Serie::setName(string name)
        {
            this->name = name;
        }

        int  Serie::getYear()
        {
            return year;
        }
        void  Serie::setYear(int year)
        {
            this->year = year;
        }

        int  Serie::getSeason()
        {
            return season;
        }
        void  Serie::setSeason(int season)
        {
            this->season = season;
        }

        int  Serie::getNumberEp()
        {
            return numberEp;
        }
        void  Serie::setNumberEp(int numberEp)
        {
            this->numberEp = numberEp;
        }

	    vector<string>  Serie::getActors()
        {
            return actors;
        }
        void  Serie::setActors(vector<string> actors)
        {
            this->actors = actors;
        }

		vector<string>  Serie::getCharacters()
        {
            return characters;
        }
        void  Serie::setCharacters(vector<string> characters)
        {
            this->characters = characters;
        }

        string  Serie::getStreamming()
        {
            return streamming;
        }
        void  Serie::setStreamming(string streamming)
        {
            this->streamming = streamming;
        }

        int  Serie::getRating()
        {
            return rating;
        }
        void  Serie::setRating(int rating)
        {
            this->rating = rating;
        }
        
        // precisamos ter um metodo para formatar a exibição na tela? 

	//};