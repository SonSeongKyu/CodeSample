#include "StringManager.h"

#include <QCoreApplication>

StringManager::~StringManager()
{
}

StringManager* StringManager::getSingleton()
{
	static StringManager instance;
	return &instance;
}

StringManager::StringManager()
{
	programPath = QCoreApplication::applicationDirPath();
	report_format_dir_path = programPath + "/report";
}
