#ifndef CODESAMPLE_H
#define CODESAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_codesample.h"

class ReportWidget;

class CodeSample : public QMainWindow
{
	Q_OBJECT

public:
	explicit CodeSample(QWidget *parent = 0);
	~CodeSample();

	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::CodeSampleClass ui;
	ReportWidget* m_report;
};

#endif // CODESAMPLE_H
