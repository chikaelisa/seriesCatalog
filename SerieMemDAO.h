
#ifndef SERIEMEMDAO_H_
#define SERIEMEMDAO_H_

#include <string>
#include<iostream>
#include <vector>

#include "SerieMemDAO.h"
#include "MemoryDBConnection.h"

using namespace std;

class SerieMemDAO {
  private:
		MemoryDBConnection* memoryDBConnection;
		static int lastSerieId; //mudar isso aqui porque so faz sentido nos usuarios do projeto do angelis. Coloquei pra poder compilar sem erro

	public:
		SerieMemDAO(MemoryDBConnection* memoryDBConnection);
		virtual ~SerieMemDAO();

    //Retirei a herança da classe abstrata e removi os "virtual"
		vector<Serie*> getAllSeries();
	  Serie* getSerieId(int serieId);
		void addSerie(Serie *serie);
		void updateSerie(Serie *serie);
		void deleteSerie(int serieId);
};

#endif