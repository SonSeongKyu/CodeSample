#include "ReportTabDialog.h"

#include <qlabel.h>
#include <qlineEdit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qgroupbox.h>

#include "StyleManager.h"


ReportDirNamingDialog::ReportDirNamingDialog(QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f), m_dirName(), nameEdit(nullptr)
{
	setFixedSize(250, 150);
	setStyleSheet(STYLE_MANAGER->mainFrame);
	setWindowTitle("Naming Dialog");

	createUI();
}


ReportDirNamingDialog::~ReportDirNamingDialog()
{
}

void ReportDirNamingDialog::createUI()
{
	QGroupBox* frame = new QGroupBox("Input Directory Name", this);
	frame->setStyleSheet(STYLE_MANAGER->groupBox);

	QVBoxLayout* vMainLay = new QVBoxLayout;
	setLayout(vMainLay);
	vMainLay->addWidget(frame);

	QVBoxLayout* vFrameLay = new QVBoxLayout;
	frame->setLayout(vFrameLay);

	QHBoxLayout* editLay = new QHBoxLayout;
	QLabel* inputName = new QLabel("Name: ", frame);
	editLay->addWidget(inputName);
	nameEdit = new QLineEdit(frame);
	nameEdit->setStyleSheet(STYLE_MANAGER->editBox);
	nameEdit->setFixedHeight(25);
	editLay->addWidget(nameEdit);
	vFrameLay->addItem(editLay);

	QHBoxLayout* btnLay = new QHBoxLayout;
	btnLay->setSpacing(5);
	QPushButton* okBtn = new QPushButton("OK", frame);
	okBtn->setStyleSheet(STYLE_MANAGER->pushButton);
	okBtn->setFixedHeight(25);
	btnLay->addWidget(okBtn);

	connect(okBtn, &QPushButton::clicked, this, &ReportDirNamingDialog::OnFinished);

	QPushButton* cancelBtn = new QPushButton("Cancel", frame);
	cancelBtn->setStyleSheet(STYLE_MANAGER->pushButton);
	cancelBtn->setFixedHeight(25);
	btnLay->addWidget(cancelBtn);

	connect(cancelBtn, &QPushButton::clicked, this, &ReportDirNamingDialog::OnCancel);

	vFrameLay->addItem(btnLay);
}

void ReportDirNamingDialog::OnFinished()
{
	if(nameEdit) m_dirName = nameEdit->text() + ".html";
	emit accept();
}

void ReportDirNamingDialog::OnCancel()
{
	this->close();
}