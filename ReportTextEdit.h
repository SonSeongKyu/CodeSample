#pragma once
#include <qtextedit.h>
#include <qdir.h>
#include <vector>
#include <array>

class QFile;
class COLOR;
class QPrinter;

enum class ImageResizingPointer
{
	TopLeft, TopMid, TopRight, MidLeft, MidRight, BotLeft, BotMid, BotRight, None
};

class SelectedImageFormat
{
public:
	explicit SelectedImageFormat();
	~SelectedImageFormat();

private:
	static const QSize RESIZING_POINTER_SIZE;

	bool m_select;
	bool m_resizing;
	int m_fragmentPos;
	int m_fragmentLen;
	QRect m_imageRect;
	QString m_name;
	std::array<QRect, 8> m_resizingPointer;


public:
	void updateImage(const QTextCursor& cursor);
	void updateResizingPointer();
	void drawResizeController(QPainter& painter);

	ImageResizingPointer hitTest(const QPoint& mousePos);
	bool isHitResizingPointer(const QPoint& pos, const QRect& area);

	void setSelectedFormat(const QRect& imgRect, const QString& name, int fragmentPos, int fragmentLen);
	void releaseSelection();

	inline bool selectionFlag() { return m_select; }

	inline void setResizeFlag(bool val) { m_resizing = val; }
	inline bool resizingFlag() { return m_resizing; }

	inline QSize size() { return m_imageRect.size(); }
	inline const QRect& rect() { return m_imageRect; }
	inline int getFragmentPos() { return m_fragmentPos; }
	inline int getFragmentLen() { return m_fragmentLen; }
	inline void setImageRect(const QRect& rect) { m_imageRect = rect; };
};

class ReportTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	explicit ReportTextEdit(QWidget* parent = nullptr);
	~ReportTextEdit();

protected:
	bool canInsertFromMimeData(const QMimeData* source) const override;
	void insertFromMimeData(const QMimeData* source) override;

	void paintEvent(QPaintEvent *ev) override;
	void keyPressEvent(QKeyEvent *ev) override;
	void mousePressEvent(QMouseEvent * ev) override;
	void mouseMoveEvent(QMouseEvent * ev) override;
	void mouseReleaseEvent(QMouseEvent* ev) override;
	void scrollContentsBy(int dx, int dy) override;

public:
	bool newFormat(bool wantClear = true);
	bool fileSave();
	bool fileSaveAs();
	bool deleteFormat();
	bool openReportFormatDir(const QString& path, QFileInfoList& fileList);

	void textBold();
	void textUnderline();
	void textItalic();
	void textFontFamily(const QString &fontFamily);
	void textSize(const QString &size);
	QColor textColorChange();

	void textLeftAlign();
	void textCenterAlign();
	void textRightAlign();
	void textJustifyAlign();

	void insertTable();
	void mergeCell();
	void splitCell();

	void fileImport();
	bool fileExport();
	void printPreview();

	void openCellProperty();
	bool loadFromDirName(const QString& dirName);

	QString getFileName() { return m_fileName; }

public slots:
	void OnPrintPreview(QPrinter *printer);
	void OnPageWidthLimit();

private:
	ReportTextEdit(const ReportTextEdit& copy) {}
	const ReportTextEdit& operator=(const ReportTextEdit& rhs) {}

	bool load(const QString &fileName);
	void setCurrentFileName(const QString &fileName);
	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
	
	void dropImage(const QUrl& url, const QImage& image);

	void drawPageBoundaryLine(QPainter& painter);

	bool isImageFormat(const QPoint& mousePos, int& cursorPos);
	bool findImageFormat(QTextBlock& block, QTextImageFormat& imgFmt, int imgCursorPos, int& fragmentPos, int& fragmentLen);
	void setSeletedIamgeFormat(int imgCursorPos);
	void resizingImageFormat(const QPoint& pos, ImageResizingPointer pointer);
	void updateResizingPointer(const QSize& newSize);

	bool copyImageToReportDirectory(QString& htmlString, const std::vector<QString>& path_list);
	void imageResourcePath(const QString& htmlString, std::vector<QString>& path_list);
	void resourceCopyToReportDirectory();

	bool checkSpecialCharacters(const QString& str);
	void setTextCursorPosition(int cursorPos);
	void selectFragment(int fragmentPos, int fragmentLen);
	
private:
	static const QSize IMPORTED_IMAGE_SIZE;
	
	bool m_bLeftClick;
	QPoint m_clickedPos;
	QString m_fileName;

	SelectedImageFormat m_selectedImgFmt;
};