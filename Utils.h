#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <thread> // Necessário para std::this_thread::sleep_for
#include <chrono> // Necessário para std::chrono::seconds

using namespace std;

class Utils final
{
public:
	static void printMessage(string text);
	static void printFramedMessage(string text, string symbol, int length);
	static string replicate(string text, int times);
	static void clearConsole();
	static void concatString(string *info, string message);
	static void sleep(int seconds);
};

#endif /* UTILS_H_ */