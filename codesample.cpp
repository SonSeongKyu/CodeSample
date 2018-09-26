#include "codesample.h"
#include "ReportWidget.h"

CodeSample::CodeSample(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_report = new ReportWidget(this);
}

CodeSample::~CodeSample()
{

}

void CodeSample::resizeEvent(QResizeEvent *event)
{
	m_report->resize(size());
}
