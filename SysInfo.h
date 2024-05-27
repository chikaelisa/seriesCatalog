/*
 * SysInfo.h
 *
 *  Created on: Mar 13, 2024
 *      Author: andre
 */

#ifndef SYSINFO_H_
#define SYSINFO_H_

#include <iostream>
#include <string>

using namespace std;
class SysInfo final
{
private:
	static const string authors;
	static const string date;
	static const string department;
	static const string institution;
	static const string systemName;
	static const string version;
	static const string helpFile;

public:
	static const string &getAuthor();
	static const string &getDate();
	static const string &getDepartment();
	static const string &getInstitution();
	static const string &getSystemName();
	static const string &getVersion();
	static const string &getHelpFile();

	static const string getFullVersion();
};

#endif /* SYSINFO_H_ */
