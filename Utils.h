/*
 * Utils.h
 *
 *  Created on: Mar 13, 2024
 *      Author: andre
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

using namespace std;

class Utils final
	{
	public:
		static void printMessage(string text);
		static void printFramedMessage(string text, string symbol, int length);
		static string replicate(string text, int times);
	};

#endif /* UTILS_H_ */
