#pragma once
#include <qstring.h>

class StringManager
{
private:
	StringManager();
	~StringManager();

public:
	static StringManager* getSingleton();

public:
	QString programPath;
	QString report_format_dir_path;
};

#define STRING_MANAGER StringManager::getSingleton()

