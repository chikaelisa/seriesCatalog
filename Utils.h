#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Utils final
{
public:
	static void printMessage(string text);
	static void printFramedMessage(string text, string symbol, int length);
	static string replicate(string text, int times);
	static void clearConsole();
};

#endif /* UTILS_H_ */