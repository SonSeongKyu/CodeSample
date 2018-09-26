#pragma once
#include <qstring.h>

class StyleManager
{
private:
	StyleManager();
	~StyleManager();

public:
	static StyleManager* getSingleton();

public:
	QString mainFrame;
	QString groupBox;
	QString pushButton;
	QString editBox;
	QString spinBox;

	QString reportToolbar;
	QString reportEditingPlace;
	QString reportScrollArea;
	QString reportTextEdit;
};

#define STYLE_MANAGER StyleManager::getSingleton()

