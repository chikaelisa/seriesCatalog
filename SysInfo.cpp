#include "SysInfo.h"

const string SysInfo::authors = "Enzo A. T.; Fernanda R. G. M.; Francisca E. C. R.; Pietra F. A. P.; Stephani S. M.";
const string SysInfo::date = "2024, May";
const string SysInfo::department = "Faculdade de Tecnologia - Limeira/SP";
const string SysInfo::institution = "Universidade Estadual de Campinas (Unicamp)";
const string SysInfo::systemName = "Series Catalog (STVS) C++";
const string SysInfo::version = "0.01";
const string SysInfo::helpFile = "STVSHelp.txt";

const string& SysInfo::getAuthor()
	{
	return authors;
	}

const string& SysInfo::getDate()
	{
	return date;
	}

const string& SysInfo::getDepartment()
	{
	return department;
	}

const string& SysInfo::getInstitution()
	{
	return institution;
	}

const string& SysInfo::getSystemName()
	{
	return systemName;
	}

const string& SysInfo::getVersion()
	{
	return version;
	}

const string& SysInfo::getHelpFile()
	{
	return helpFile;
	}

const string SysInfo::getFullVersion()
	{
	return systemName + " | Ver. " + version + " (" + date + ")";
	}
