#include <iostream>
#include <vector>
#include "Utils.h"
#include "SysInfo.h"

void Utils::printMessage(string text)
{
	cout << "* " << SysInfo::getSystemName() << " mensagem: " << text << endl;
}

void Utils::printFramedMessage(string text, string symbol, int length)
{
	cout << replicate(symbol, length) << endl;
	cout << text << endl;
	cout << replicate(symbol, length) << endl;
}

string Utils::replicate(string text, int times)
{
	string buffer;
	for (int count = 0; count < times; count++)
	{
		buffer += text;
	}
	return (buffer);
}

void Utils::clearConsole()
{
#ifdef _WIN32
	system("cls"); // Comando para limpar console no Windows
#else
	system("clear"); // Comando para limpar console no macOS e Linux
#endif
}