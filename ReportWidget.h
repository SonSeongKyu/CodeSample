#pragma once
#include <qwidget.h>
#include <qscrollarea.h>
#include <vector>

class QToolBar;
class ReportTextEdit;
class QAbstractButton;

class ReportWidget : public QWidget
{
	Q_OBJECT

public:
	enum ToolBar
	{
		ComboReportFormat, TextColor
	};

public:
	explicit ReportWidget(QWidget* parent = nullptr);
	~ReportWidget();

	void addFormatAndShow();
	void initFormatComboBox();

public slots:
	void OnNewFile();
	void OnFileSave();
	void OnDeleteFile();

	void OnFileImport();
	void OnFileExport();

	void OnPrintPreview();

	void OnTextBold();
	void OnTextUnderline();
	void OnTextItalic();

	void OnTextFamily(const QString& fontFamily);
	void OnTextSize(const QString &size);
	void OnTextColor();

	void OnTextAlign(QAbstractButton* btn);

	void OnInsertTable();
	void OnMergeCell();
	void OnSplitCell();
	void OnOpenCellProperty();

	void OnReportFormatChange(const QString& dirName);

private:
	QToolBar*	 createToolbar();
	QWidget*	 createEditingPlace();
	QScrollArea* createScrollArea();

private:
	ReportTextEdit* m_textEdit;
	std::vector<QWidget*> toolBar_list;
};

