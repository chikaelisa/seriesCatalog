#include <string>
#include <exception>
#include <memory>
#include <iostream>

#include "Controller.h"

using namespace std;

int main(int argc, char *argv[])
	{

	try
		{
		(make_unique<Controller>())->start();
		}
	catch (const exception &myException)
		{
		cout << "Um erro inesperado ocorreu. Programa finalizado " + string(myException.what()) << endl;
		exit(1);
		}

	cout << "Ate breve!" << endl;
	return (0);


	}

