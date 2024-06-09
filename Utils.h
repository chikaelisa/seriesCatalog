#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Utils final
{
public:
	static void printMessage(string text);
	static void printFramedMessage(string text, string symbol, int length);
	static string replicate(string text, int times);
	static void clearConsole();
	static void concatString(string *info, string message);
};

#endif /* UTILS_H_ */