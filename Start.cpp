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
		cout << "Unexpected problem. Program aborted. " + string(myException.what()) << endl;
		exit(1);
		}

	cout << "See you soon" << endl;
	return (0);


	}

