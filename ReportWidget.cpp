#include "ReportWidget.h"

#include <qtoolbar.h>
#include <qlayout.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qfontcombobox.h>
#include <qfontdatabase.h>
#include <qbuttongroup.h>
#include <qabstractbutton.h>
#include <qscrollbar.h>
#include <qmessagebox.h>
#include <qapplication.h>

#include "ReportTextEdit.h"
#include "StyleManager.h"
#include "StringManager.h"

#include <iostream>

ReportWidget::ReportWidget(QWidget* parent)
	: QWidget(parent), m_textEdit(nullptr)
{
	toolBar_list.reserve(20);

	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(layout);

	m_textEdit = new ReportTextEdit(this);

	QToolBar* toolBar = createToolbar();
	layout->addWidget(toolBar, 0);

	QHBoxLayout* hLay = new QHBoxLayout;

	QWidget* editingPlace = createEditingPlace();
	hLay->addWidget(editingPlace, 1);

	QScrollArea* scrollArea = createScrollArea();
	hLay->addWidget(scrollArea, 0);

	layout->addItem(hLay);
}


ReportWidget::~ReportWidget()
{
}

void ReportWidget::addFormatAndShow()
{
	QComboBox* combo = dynamic_cast<QComboBox*>(toolBar_list[ComboReportFormat]);

	if (nullptr == combo) return;
	int result = combo->findText(QFileInfo(m_textEdit->getFileName()).baseName());

	if (result >= 0) return;
	combo->addItem(QFileInfo(m_textEdit->getFileName()).baseName());
	combo->setCurrentIndex(combo->count() - 1);
}

void ReportWidget::initFormatComboBox()
{
	QComboBox* combo = dynamic_cast<QComboBox*>(toolBar_list[ComboReportFormat]);
	if (nullptr == combo) return;

	combo->clear();

	QFileInfoList fileList;
	m_textEdit->openReportFormatDir(STRING_MANAGER->report_format_dir_path, fileList);
	for (auto iter = fileList.begin(); iter != fileList.end(); ++iter)
	{
		int result = combo->findText(iter->baseName());
		if (result >= 0) continue;
		combo->addItem(iter->baseName());
	}
}

void ReportWidget::OnNewFile()
{
	bool success = m_textEdit->newFormat();
	if (false == success) return;
	addFormatAndShow();
}

void ReportWidget::OnFileSave()
{
	bool success = m_textEdit->fileSave();
	if (false == success) return;
	addFormatAndShow();
}

void ReportWidget::OnDeleteFile()
{
	bool success = m_textEdit->deleteFormat();
	if (false == success) return;

	QComboBox* combo = dynamic_cast<QComboBox*>(toolBar_list[ComboReportFormat]);
	if (nullptr == combo) return;
	combo->removeItem(combo->currentIndex());
	combo->setCurrentIndex(0);
	OnReportFormatChange(combo->currentText());
}

void ReportWidget::OnFileImport()
{
	m_textEdit->fileImport();
}

void ReportWidget::OnFileExport()
{
	m_textEdit->fileExport();
}

void ReportWidget::OnPrintPreview()
{
	m_textEdit->printPreview();
}

void ReportWidget::OnTextBold()
{
	m_textEdit->textBold();
}

void ReportWidget::OnTextUnderline()
{
	m_textEdit->textUnderline();
}

void ReportWidget::OnTextItalic()
{
	m_textEdit->textItalic();
}

void ReportWidget::OnTextFamily(const QString& fontFamily)
{
	m_textEdit->textFontFamily(fontFamily);
}

void ReportWidget::OnTextSize(const QString &size)
{
	m_textEdit->textSize(size);
}

void ReportWidget::OnTextColor()
{
	QColor c = m_textEdit->textColorChange();
	QPixmap pix(16, 16);
	pix.fill(c);

	QPushButton* btn = dynamic_cast<QPushButton*>(toolBar_list[TextColor]);
	if (nullptr == btn) return;
	btn->setIcon(pix);
}

void ReportWidget::OnTextAlign(QAbstractButton* btn)
{
	if (btn->objectName().contains("Left"))
		m_textEdit->textLeftAlign();
	else if (btn->objectName().contains("Center"))
		m_textEdit->textCenterAlign();
	else if (btn->objectName().contains("Right"))
		m_textEdit->textRightAlign();
	else if (btn->objectName().contains("Justify"))
		m_textEdit->textJustifyAlign();
}

void ReportWidget::OnInsertTable()
{
	m_textEdit->insertTable();
}

void ReportWidget::OnMergeCell()
{
	m_textEdit->mergeCell();
}

void ReportWidget::OnSplitCell()
{
	m_textEdit->splitCell();
}

void ReportWidget::OnOpenCellProperty()
{
	m_textEdit->openCellProperty();
}

void ReportWidget::OnReportFormatChange(const QString& dirName)
{
	bool result = m_textEdit->loadFromDirName(dirName);
	if (false == result)
		QMessageBox::warning(nullptr, "Report Tab", tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(dirName)));
}

QToolBar* ReportWidget::createToolbar()
{
	QToolBar* toolBar = new QToolBar(this);
	toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	toolBar->setOrientation(Qt::Horizontal);
	toolBar->setStyleSheet(STYLE_MANAGER->reportToolbar);

	QComboBox* comboReportFormat = new QComboBox(toolBar);
	toolBar_list.push_back(comboReportFormat);
	comboReportFormat->setMinimumWidth(100);
	comboReportFormat->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	comboReportFormat->setEditable(false);
	initFormatComboBox();

	toolBar->addWidget(comboReportFormat);
	connect(comboReportFormat, QOverload<const QString &>::of(&QComboBox::activated), this, &ReportWidget::OnReportFormatChange);

	toolBar->addSeparator();

	QPushButton* newFormat = new QPushButton("New", toolBar);
	toolBar->addWidget(newFormat);
	connect(newFormat, &QPushButton::clicked, this, &ReportWidget::OnNewFile);

	QPushButton* save = new QPushButton("Save", toolBar);
	toolBar->addWidget(save);
	connect(save, &QPushButton::clicked, this, &ReportWidget::OnFileSave);

	QPushButton* del = new QPushButton("Delete", toolBar);
	toolBar->addWidget(del);
	connect(del, &QPushButton::clicked, this, &ReportWidget::OnDeleteFile);

	toolBar->addSeparator();

	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	QPushButton* textColor = new QPushButton(toolBar);
	toolBar_list.push_back(textColor);
	textColor->setIcon(QIcon(pix));
	//textColor->setFixedSize(24, 24);
	toolBar->addWidget(textColor);
	connect(textColor, &QPushButton::clicked, this, &ReportWidget::OnTextColor);

	QFontDatabase base;
	QStringList list = base.families();
	QFontComboBox* comboFont = new QFontComboBox(toolBar);
	comboFont->setMaximumWidth(80);
	comboFont->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	comboFont->setFontFilters(QFontComboBox::FontFilter::ScalableFonts);
	toolBar->addWidget(comboFont);
	connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &ReportWidget::OnTextFamily);

	QComboBox* comboSize = new QComboBox(toolBar);
	comboSize->setMinimumWidth(30);
	comboSize->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	toolBar->addWidget(comboSize);
	comboSize->setEditable(true);
	const QList<int> standardSizes = QFontDatabase::standardSizes();
	foreach(int size, standardSizes)
		comboSize->addItem(QString::number(size));
	comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
	connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &ReportWidget::OnTextSize);

	QPushButton* textBold = new QPushButton("Bold", toolBar);
	toolBar->addWidget(textBold);
	connect(textBold, &QPushButton::clicked, this, &ReportWidget::OnTextBold);

	QPushButton* textUnderline = new QPushButton("Line", toolBar);
	toolBar->addWidget(textUnderline);
	connect(textUnderline, &QPushButton::clicked, this, &ReportWidget::OnTextUnderline);

	QPushButton* textItalic = new QPushButton("Italic", toolBar);
	toolBar->addWidget(textItalic);
	connect(textItalic, &QPushButton::clicked, this, &ReportWidget::OnTextItalic);

	toolBar->addSeparator();

	QButtonGroup* alignBtns = new QButtonGroup(toolBar);
	connect(alignBtns, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonReleased), this, &ReportWidget::OnTextAlign);

	QPushButton* textLeftAlign = new QPushButton("Left", toolBar);
	textLeftAlign->setObjectName("Left");
	alignBtns->addButton(textLeftAlign);
	toolBar->addWidget(textLeftAlign);

	QPushButton* textCenterAlign = new QPushButton("Center", toolBar);
	textCenterAlign->setObjectName("Center");
	alignBtns->addButton(textCenterAlign);
	toolBar->addWidget(textCenterAlign);

	QPushButton* textRightAlign = new QPushButton("Right", toolBar);
	textRightAlign->setObjectName("Right");
	alignBtns->addButton(textRightAlign);
	toolBar->addWidget(textRightAlign);

	QPushButton* textJustifyAlign = new QPushButton("Justify", toolBar);
	textJustifyAlign->setObjectName("Justify");
	alignBtns->addButton(textJustifyAlign);
	toolBar->addWidget(textJustifyAlign);

	toolBar->addSeparator();

	QPushButton* btnInsertTable = new QPushButton("Table", toolBar);
	toolBar->addWidget(btnInsertTable);
	connect(btnInsertTable, &QPushButton::clicked, this, &ReportWidget::OnInsertTable);

	QPushButton* btnMergeCell = new QPushButton("Merge", toolBar);
	toolBar->addWidget(btnMergeCell);
	connect(btnMergeCell, &QPushButton::clicked, this, &ReportWidget::OnMergeCell);

	QPushButton* btnSplitCell = new QPushButton("Split", toolBar);
	toolBar->addWidget(btnSplitCell);
	connect(btnSplitCell, &QPushButton::clicked, this, &ReportWidget::OnSplitCell);

	QPushButton* m_btnCellProperty = new QPushButton("Cell", toolBar);
	toolBar->addWidget(m_btnCellProperty);
	connect(m_btnCellProperty, &QPushButton::clicked, this, &ReportWidget::OnOpenCellProperty);

	toolBar->addSeparator();

	QPushButton* fileImport = new QPushButton("Import", toolBar);
	toolBar->addWidget(fileImport);
	connect(fileImport, &QPushButton::clicked, this, &ReportWidget::OnFileImport);

	QPushButton* fileExport = new QPushButton("Export", toolBar);
	toolBar->addWidget(fileExport);
	connect(fileExport, &QPushButton::clicked, this, &ReportWidget::OnFileExport);

	QPushButton* printPreview = new QPushButton("Preview", toolBar);
	toolBar->addWidget(printPreview);
	connect(printPreview, &QPushButton::clicked, this, &ReportWidget::OnPrintPreview);

	return toolBar;
}

QWidget* ReportWidget::createEditingPlace()
{
	QWidget* editingPlace = new QWidget(this);
	editingPlace->setStyleSheet(STYLE_MANAGER->reportEditingPlace);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignCenter);
	editingPlace->setLayout(layout);

	layout->addWidget(m_textEdit);

	return editingPlace;
}

QScrollArea* ReportWidget::createScrollArea()
{
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setFixedWidth(m_textEdit->verticalScrollBar()->sizeHint().width());
	scrollArea->setVerticalScrollBar(m_textEdit->verticalScrollBar());
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet(STYLE_MANAGER->reportScrollArea);

	return scrollArea;
}
