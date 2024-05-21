
#ifndef SERIE_H_
#define SERIE_H_


#include <string>
#include<iostream>
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
		vector<string> actors;
		vector<string> characters;
		string streamming;
        int rating;

	public:

        Serie(int id, string name, int year, int season, int numberEp, vector<string> actors, vector<string>characters, string streamming, int rating);
       // Serie(int id);
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

	    vector<string> getActors();
        void setActors(vector<string> actors);

		vector<string> getCharacters();
        void setCharacters(vector<string> characters);

        string getStreamming();
        void setStreamming(string streamming);

        int getRating();
        void setRating(int rating);
        
	};

#endif /* SERIE_H_ */
