#include "StyleManager.h"

StyleManager::~StyleManager()
{
}

StyleManager* StyleManager::getSingleton()
{
	static StyleManager instance;
	return &instance;
}

StyleManager::StyleManager()
{
	mainFrame = QString(
		"color: white;"
		"background-color: rgba(82, 82, 82, 255);;"
	);

	groupBox = QString("QGroupBox{"
		"background: rgba(82, 82, 82, 255);"
		"border: 3px solid rgba(48, 48, 48, 255);"
		"border - radius: 5px;"
		"}"
	);

	pushButton = QString("QPushButton{"
		"background-color: rgba(82, 82, 82, 255);"
		"border-style: outset;"
		"border-width: 0.5px;"
		"border-radius: 3px;"
		"image-position: top left;"
		"border-color:  rgba(150, 150, 150, 255);;}"
		"QPushButton:pressed{"
		"color: blue;}"
	);

	editBox = QString(
		"background-color: rgba(48, 48, 48, 255);"
		"border-style: outset;"
		"border-width: 0.5px;"
		"border-radius: 3px;"
		"border-color:  rgba(150, 150, 150, 255);;"
	);

	spinBox = QString(
		"QSpinBox{"
		"color: white;"
		"background-color: rgba(48, 48, 48, 255);"
		"border - style: outset;"
		"border-width: 0.5px;"
		"border-radius: 2px;"
		"padding: 1.5px;"
		"border-color: rgba(150, 150, 150, 255);;}"
		"QSpinBox::up-arrow{"
		"border-left: 3px solid none;"
		"border-right: 3px solid none; border-bottom: 3px solid white; width: 0px; height: 0px;;}"
		"QSpinBox::up-button{"
		"background-color: rgba(82, 82, 82, 255);"
		"border-style: outset;"
		"border-width: 0.5px;"
		"border-color: black;;}"
		"QSpinBox::down-arrow{"
		"border-left: 3px solid none;"
		"border-right: 3px solid none; border-top: 3px solid white; width: 0px; height: 0px;;}"
		"QSpinBox::down-button{"
		"background-color: rgba(82, 82, 82, 255);"
		"border-style: outset;"
		"border-width: 0.5px;"
		"border-color: black;;}"
	);

	reportToolbar = QString("QToolBar {"
		"background-color: rgba(48, 48, 48, 255);"
		"border-style: outset;"
		"padding: 3px;"
		"border-width: 0.5px;"
		"border-radius: 3px;"
		"border-color:  black;"
		"}"
	);

	reportEditingPlace = QString(
		"background-color : rgba(48, 48, 48, 255);"
		"border-color:  rgba(48, 48, 48, 255);;"
	);

	reportScrollArea = QString(
		"background-color : rgba(48, 48, 48, 255);"
		"border-style: outset;"
		"border-color: rgba(48, 48, 48, 255);;"
	);

	reportTextEdit = QString(
		"color: black;"
		"background-color : white;"
		"border-style: outset;"
		"border-color: rgba(48, 48, 48, 255);;"
	);
}