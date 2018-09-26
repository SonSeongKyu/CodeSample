#include "codesample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CodeSample w;
	//w.show();
	w.showMaximized();
	return a.exec();
}
