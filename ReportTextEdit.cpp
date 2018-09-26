#include "ReportTextEdit.h"

#include <qtextdocumentwriter.h>
#include <qtextcodec.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qprintpreviewdialog.h>
#include <qprinterinfo.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qtextlist.h>
#include <qcolordialog.h>
#include <qmimedata.h>
#include <qimagereader.h>
#include <qpainter.h>
#include <qscrollbar.h>
#include <qtexttable.h>
#include <qabstracttextdocumentlayout.h>
#include <qtextdocumentfragment.h>

#include "define.h"
#include "TableDialog.h"
#include "StyleManager.h"
#include "StringManager.h"
#include "ReportTabDialog.h"

#ifdef DEV_VER
#include <iostream>
#include <qdebug.h>
#endif // !DEV_VER

const QSize SelectedImageFormat::RESIZING_POINTER_SIZE = QSize(8, 8);

SelectedImageFormat::SelectedImageFormat()
	: m_select(false), m_resizing(false), m_fragmentPos(0), m_fragmentLen(0), m_imageRect(), m_name()
{
	for (int i = 0; i < m_resizingPointer.size(); ++i)
		m_resizingPointer[i] = QRect();
}

SelectedImageFormat::~SelectedImageFormat()
{

}

void SelectedImageFormat::updateResizingPointer()
{
	QPoint imgPos = QPoint(m_imageRect.topLeft());
	QSize imgSize = QSize(m_imageRect.size());
	QRect rect(QPoint(imgPos.x() - RESIZING_POINTER_SIZE.width() / 2, imgPos.y() - RESIZING_POINTER_SIZE.height() / 2), RESIZING_POINTER_SIZE);

	m_resizingPointer[(int)ImageResizingPointer::TopLeft] = QRect(rect.topLeft(), RESIZING_POINTER_SIZE);
	m_resizingPointer[(int)ImageResizingPointer::TopMid] = QRect(QPoint(rect.x() + imgSize.width() / 2, rect.y()), RESIZING_POINTER_SIZE);
	m_resizingPointer[(int)ImageResizingPointer::TopRight] = QRect(QPoint(rect.x() + imgSize.width(), rect.y()), RESIZING_POINTER_SIZE);

	m_resizingPointer[(int)ImageResizingPointer::MidLeft] = QRect(QPoint(rect.x(), rect.y() + imgSize.height() / 2), RESIZING_POINTER_SIZE);
	m_resizingPointer[(int)ImageResizingPointer::MidRight] = QRect(QPoint(rect.x() + imgSize.width(), rect.y() + imgSize.height() / 2), RESIZING_POINTER_SIZE);

	m_resizingPointer[(int)ImageResizingPointer::BotLeft] = QRect(QPoint(rect.x(), rect.y() + imgSize.height()), RESIZING_POINTER_SIZE);
	m_resizingPointer[(int)ImageResizingPointer::BotMid] = QRect(QPoint(rect.x() + imgSize.width() / 2, rect.y() + imgSize.height()), RESIZING_POINTER_SIZE);
	m_resizingPointer[(int)ImageResizingPointer::BotRight] = QRect(QPoint(rect.x() + imgSize.width(), rect.y() + imgSize.height()), RESIZING_POINTER_SIZE);
}

void SelectedImageFormat::updateImage(const QTextCursor& cursor)
{
	QTextImageFormat imgFmt;
	imgFmt.setName(m_name);
	imgFmt.setWidth(m_imageRect.width());
	imgFmt.setHeight(m_imageRect.height());

	QTextCursor editCursor = cursor;

	editCursor.setPosition(m_fragmentPos);
	editCursor.setPosition(m_fragmentPos + m_fragmentLen, QTextCursor::KeepAnchor);
	editCursor.setCharFormat(imgFmt);
}

void SelectedImageFormat::drawResizeController(QPainter& painter)
{
	if (false == m_select) return;

	painter.drawRect(m_imageRect);

	painter.setBrush(Qt::white);
	for (int i = 0; i < m_resizingPointer.size(); ++i)
	{
		painter.drawEllipse(m_resizingPointer[i]);
	}
}

ImageResizingPointer SelectedImageFormat::hitTest(const QPoint& mousePos)
{
	for (int i = 0; i < m_resizingPointer.size(); ++i)
	{
		if (isHitResizingPointer(mousePos, m_resizingPointer[i]))
			return static_cast<ImageResizingPointer>(i);
	}
	return ImageResizingPointer::None;
}

bool SelectedImageFormat::isHitResizingPointer(const QPoint& pos, const QRect& area)
{
	int correction = 2;
	bool xRange = area.x() - correction <= pos.x() && pos.x() <= area.x() + area.width() + correction;
	bool yRange = area.y() - correction <= pos.y() && pos.y() <= area.y() + area.height() + correction;

	if (xRange && yRange)
		return true;

	return false;
}

void SelectedImageFormat::setSelectedFormat(const QRect& imgRect, const QString& name, int fragmentPos, int fragmentLen)
{
	m_select = true;
	m_fragmentPos = fragmentPos;
	m_fragmentLen = fragmentLen;
	m_imageRect = imgRect;
	m_name = name;

	updateResizingPointer();
}

void SelectedImageFormat::releaseSelection()
{
	m_select = false;
	m_resizing = false;
	m_fragmentPos = 0;
	m_fragmentLen = 0;
	m_imageRect = QRect();
	m_name.clear();
}

//======================================================================================

const QSize ReportTextEdit::IMPORTED_IMAGE_SIZE = QSize(200, 200);

ReportTextEdit::ReportTextEdit(QWidget* parent)
	: QTextEdit(parent), m_bLeftClick(false), m_clickedPos(), m_fileName(), m_selectedImgFmt()
{
	setStyleSheet(STYLE_MANAGER->reportTextEdit);

	setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	
	QSizeF size = QSizeF(595.0f, 842.0f); //A4 Pixel 사이즈
	
	setFixedSize(size.toSize());
	setLineWrapMode(QTextEdit::FixedPixelWidth);
	setLineWrapColumnOrWidth(static_cast<int>(size.width()));
	
	setFixedWidth(size.toSize().width());
	document()->setPageSize(size);

	viewport()->setMouseTracking(true);
	viewport()->installEventFilter(this);
	
	setContextMenuPolicy(Qt::CustomContextMenu);

	connect(document()->documentLayout(), &QAbstractTextDocumentLayout::documentSizeChanged, this, &ReportTextEdit::OnPageWidthLimit);
}


ReportTextEdit::~ReportTextEdit()
{

}

bool ReportTextEdit::canInsertFromMimeData(const QMimeData* source) const
{
	return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source);
}

void ReportTextEdit::insertFromMimeData(const QMimeData* source)
{
	if (source->hasImage())
	{
		static int i = 1;
		QUrl url(QString("dropped_image_%1").arg(i++));

		QImage image = qvariant_cast<QImage>(source->imageData());
		QSize size = image.size();
		size.scale(IMPORTED_IMAGE_SIZE, Qt::AspectRatioMode::KeepAspectRatio);
		dropImage(url, image.scaled(size, Qt::KeepAspectRatio));
	}
	else if (source->hasUrls())
	{
		foreach(QUrl url, source->urls())
		{
			QFileInfo info(url.toLocalFile());

			if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
			{
				QImage image(info.filePath());
				QSize size = image.size();
				size.scale(IMPORTED_IMAGE_SIZE, Qt::AspectRatioMode::KeepAspectRatio);
				dropImage(url, image);
			}
		}
	}
	else
	{
		QTextEdit::insertFromMimeData(source);
	}
}

void ReportTextEdit::paintEvent(QPaintEvent *ev)
{
	QTextEdit::paintEvent(ev);	
	
	QPainter painter(viewport());

	drawPageBoundaryLine(painter);

	m_selectedImgFmt.drawResizeController(painter);
}

void ReportTextEdit::keyPressEvent(QKeyEvent *ev)
{
	if (ev->matches(QKeySequence::Copy) && m_selectedImgFmt.selectionFlag())
	{
		int pos = m_selectedImgFmt.getFragmentPos();
		int len = m_selectedImgFmt.getFragmentLen();
		selectFragment(pos, len);
	}
	else if (ev->matches(QKeySequence::Cut) && m_selectedImgFmt.selectionFlag())
	{
		int pos = m_selectedImgFmt.getFragmentPos();
		int len = m_selectedImgFmt.getFragmentLen();
		selectFragment(pos, len);
	}
	else if (ev->key() != Qt::Key_Control)
		m_selectedImgFmt.releaseSelection();

	QTextEdit::keyPressEvent(ev);
}

void ReportTextEdit::mousePressEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		m_bLeftClick = true;
		m_clickedPos = ev->pos();
	}

	QTextEdit::mousePressEvent(ev);
}

void ReportTextEdit::mouseMoveEvent(QMouseEvent * ev)
{
	int cursorPos = 0;
	static ImageResizingPointer pointer = ImageResizingPointer::None;

	if (isImageFormat(ev->pos(), cursorPos))
	{
		viewport()->setCursor(Qt::SizeAllCursor);
		if (false == m_selectedImgFmt.resizingFlag() && true == m_selectedImgFmt.selectionFlag())
		{
			pointer = m_selectedImgFmt.hitTest(ev->pos());

			if (ImageResizingPointer::TopMid == pointer || ImageResizingPointer::BotMid == pointer)
				viewport()->setCursor(Qt::SizeVerCursor);
			else if (ImageResizingPointer::MidLeft == pointer || ImageResizingPointer::MidRight == pointer)
				viewport()->setCursor(Qt::SizeHorCursor);
			else if (ImageResizingPointer::MidLeft == pointer || ImageResizingPointer::MidRight == pointer)
				viewport()->setCursor(Qt::SizeHorCursor);
			else if (ImageResizingPointer::TopRight == pointer || ImageResizingPointer::BotLeft == pointer)
				viewport()->setCursor(Qt::SizeBDiagCursor);
			else if (ImageResizingPointer::TopLeft == pointer || ImageResizingPointer::BotRight == pointer)
				viewport()->setCursor(Qt::SizeFDiagCursor);				

			if (m_bLeftClick)
				m_selectedImgFmt.setResizeFlag(true);
		}
	}
	else
		viewport()->setCursor(Qt::IBeamCursor);

	if (true == m_selectedImgFmt.resizingFlag())
	{
		resizingImageFormat(ev->pos(), pointer);
		update();
		return;
	}

	QTextEdit::mouseMoveEvent(ev);
}

void ReportTextEdit::mouseReleaseEvent(QMouseEvent* ev)
{
	int cursorPos = 0;

	if (true == m_selectedImgFmt.resizingFlag())
		m_selectedImgFmt.updateImage(textCursor());

	if (isImageFormat(ev->pos(), cursorPos) && false == m_selectedImgFmt.resizingFlag())
	{
		int imageStartPos = cursorPos - 1;
		setSeletedIamgeFormat(imageStartPos);
		setTextCursorPosition(imageStartPos);
		update();
	}
	else
	{
		m_selectedImgFmt.releaseSelection();
		update();
	}

	m_bLeftClick = false;
	m_selectedImgFmt.setResizeFlag(false);

	QTextEdit::mouseReleaseEvent(ev);
}

void ReportTextEdit::scrollContentsBy(int dx, int dy)
{
	m_selectedImgFmt.releaseSelection();
	QTextEdit::scrollContentsBy(dx, dy);
}

bool ReportTextEdit::newFormat(bool wantClear)
{
	QString fileName;
	ReportDirNamingDialog dlg(this, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	int success = false;

	while (false == success)
	{
		int result = dlg.exec();

		if (result == QDialog::Accepted)
			fileName = dlg.getDirName();
		else if (result == QDialog::Rejected)
			return false;

		success = !QFileInfo(fileName).baseName().isEmpty();
		if (false == success)
		{
			QMessageBox::warning(nullptr, "Failed", "It is an empty string.");
			continue;
		}

		success = checkSpecialCharacters(QFileInfo(fileName).baseName());
		if(false == success)
		{
			QMessageBox::warning(nullptr, "Failed", "The name is not in English or contains special characters.");
			continue;
		}

		QDir dir(STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(fileName).baseName());
		success = !dir.exists();
		if (false == success)
		{
			QMessageBox::warning(nullptr, "Failed", "The name of the file already saved.");
		}
	}
	QString str = STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(fileName).baseName();
	setCurrentFileName(STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(fileName).baseName() + "/" + fileName);
	if(true == wantClear) clear();

	return fileSave();
}

bool ReportTextEdit::fileSave()
{
	if (m_fileName.size() <= 0)
		newFormat();

	setCurrentFileName(STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(m_fileName).baseName() + "/" + QFileInfo(m_fileName).fileName());

	QDir dir(STRING_MANAGER->report_format_dir_path);
	bool success = dir.mkdir(QFileInfo(m_fileName).baseName());

	if (false == success)
	{
		dir.cd(QFileInfo(m_fileName).baseName());
		success = dir.remove(QFileInfo(m_fileName).baseName() + ".html");
	}

	QString htmlString = toHtml();
	std::vector<QString> path_list;
	imageResourcePath(htmlString, path_list);
	success = copyImageToReportDirectory(htmlString, path_list);
	resourceCopyToReportDirectory();

	if (false == success) return false;
	
	QTextDocumentWriter writer(m_fileName);
	success = writer.write(document());
	if (success) {
		document()->setModified(false);
	}
	else {
		QMessageBox::warning(nullptr, "Save Failed", tr("Could not save \"%1\"").arg(QDir::toNativeSeparators(m_fileName)));
	}
	return success;
}

bool ReportTextEdit::fileSaveAs()
{
	bool result = newFormat(false);
	if (false == result) return false;
	return fileSave();
}


bool ReportTextEdit::deleteFormat()
{
	const QMessageBox::StandardButton ret = QMessageBox::warning(nullptr, "Warning",
		"Are you sure you want to delete the form?",
		QMessageBox::Ok | QMessageBox::Cancel
	);
	if (ret == QMessageBox::Ok)
	{
		return QDir(STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(m_fileName).baseName()).removeRecursively();
	}
	else if (ret == QMessageBox::Cancel)
		return false;
	return false;
}

bool ReportTextEdit::openReportFormatDir(const QString& path, QFileInfoList& fileList)
{
	QDir reportDir(path);
	
	reportDir.setFilter((QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot));

	fileList = reportDir.entryInfoList();
	if (fileList.size() <= 0) return false;

	fileList.erase(std::remove_if(fileList.begin(), fileList.end(), [](const QFileInfo& info) {
		QDir dir(info.filePath());
		return dir.isEmpty();
	}), fileList.end()); //이름이 공백인 디렉토리 검사

	fileList.erase(std::remove_if(fileList.begin(), fileList.end(), [](const QFileInfo& info) {
		QDir dir(info.filePath());
		return dir.dirName().contains(".");
	}), fileList.end()); // ( . )이 들어간 디렉토리 검사

	if (fileList.size() <= 0) return false;

	return loadFromDirName(fileList[0].fileName());
}

void ReportTextEdit::textBold()
{
	QTextCharFormat fmt;
	QTextCursor cursor = textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	bool isBold = cursor.charFormat().fontWeight() == QFont::Bold;
	fmt.setFontWeight(isBold ? QFont::Normal : QFont::Bold);
	mergeFormatOnWordOrSelection(fmt);
}

void ReportTextEdit::textUnderline()
{
	QTextCharFormat fmt;
	QTextCursor cursor = textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	bool bUnder = cursor.charFormat().fontUnderline();
	fmt.setFontUnderline(!bUnder);
	mergeFormatOnWordOrSelection(fmt);
}

void ReportTextEdit::textItalic()
{
	QTextCharFormat fmt;
	QTextCursor cursor = textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	bool bItalic = cursor.charFormat().fontItalic();
	fmt.setFontItalic(!bItalic);
	mergeFormatOnWordOrSelection(fmt);
}

void ReportTextEdit::textFontFamily(const QString &fontFamily)
{
	QTextCharFormat fmt;
	fmt.setFontFamily(fontFamily);
	mergeFormatOnWordOrSelection(fmt);
}

void ReportTextEdit::textSize(const QString &size)
{
	qreal pointSize = size.toFloat();
	if (size.toFloat() > 0) {
		QTextCharFormat fmt;
		fmt.setFontPointSize(pointSize);
		mergeFormatOnWordOrSelection(fmt);
	}
}

QColor ReportTextEdit::textColorChange()
{
	QColorDialog dlg(textColor());
	dlg.setStyleSheet("background-color : rgba(48,48,48,255); color : white");

	if (dlg.exec() == QDialog::Accepted)
	{
		QColor color = dlg.selectedColor();

		if (!color.isValid())
			return color;
		QTextCharFormat fmt;
		fmt.setForeground(color);
		mergeFormatOnWordOrSelection(fmt);
		return color;
	}

	return textColor();
}

void ReportTextEdit::textLeftAlign()
{
	setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
}

void ReportTextEdit::textCenterAlign()
{
	setAlignment(Qt::AlignHCenter);
}

void ReportTextEdit::textRightAlign()
{
	setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

void ReportTextEdit::textJustifyAlign()
{
	setAlignment(Qt::AlignJustify);
}

void ReportTextEdit::insertTable()
{
	TableDialog dlg(this, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	if (dlg.exec() == QDialog::Accepted)
	{
		QTextTable* table = textCursor().insertTable(dlg.getRow(), dlg.getColumn(), dlg.getTableFormat());
	}
}

void ReportTextEdit::mergeCell()
{
	QTextTable* table = textCursor().currentTable();
	if (table)
	{
		int firstRow = 0, numRow = 0, firstCol = 0, numCol = 0;
		textCursor().selectedTableCells(&firstRow, &numRow, &firstCol, &numCol);
		table->mergeCells(firstRow, firstCol, numRow, numCol);
	}
}

void ReportTextEdit::splitCell()
{
	QTextTable* table = textCursor().currentTable();

	int fr, nr, fc, nc;
	textCursor().selectedTableCells(&fr, &nr, &fc, &nc);

	if (fr >= 0 || fc >= 0) return;
	if (nullptr == table) return;

	QTextTableCell cell = table->cellAt(textCursor());

	int selectedRow = cell.row();
	int selectedColumn = cell.column();

	if (selectedRow < 0 || selectedColumn < 0)
		return;

	int spanRow = cell.rowSpan();
	int spanColumn = cell.columnSpan();

	if (spanRow <= 1 && spanColumn <= 1)
	{
		QMessageBox::warning(nullptr, "Failed", "It is only possible to split cells that span multiple rows or columns,\n"
			"such as rows that have been merged using merge cells.");
	}

	spanRow = std::max(1, spanRow - 1);
	spanColumn = std::max(1, spanColumn - 1);
	table->splitCell(selectedRow, selectedColumn, spanRow, spanColumn);
}

void ReportTextEdit::fileImport()
{
	const QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

	QImage image(fileName);
	QSize size = image.size();
	size.scale(IMPORTED_IMAGE_SIZE, Qt::AspectRatioMode::KeepAspectRatio);
	dropImage(fileName, image);
}

bool ReportTextEdit::fileExport()
{
	const QFileDialog::Options options = QFlag(QFileDialog::ShowDirsOnly);
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
		"Export file", QDir::homePath(), tr("PDF (*.pdf)"),
		&selectedFilter, options);

	QString type = QFileInfo(fileName).suffix();

	if ("pdf" == type)
	{
		QPrinterInfo info = QPrinterInfo::defaultPrinter();
		if (info.state() == QPrinter::Error)
		{
			QMessageBox::warning(nullptr, "Failed", "Can not save to PDF.");
		}
		QPrinter printer(info, QPrinter::HighResolution);
		printer.setOutputFormat(QPrinter::PdfFormat);
		printer.setPaperSize(QPrinter::A4);
		printer.setOutputFileName(fileName);
		printer.setPageMargins(QMarginsF(15, 15, 15, 15));

		document()->print(&printer);
	}

	return true;
}

void ReportTextEdit::printPreview()
{
	QPrinterInfo info = QPrinterInfo::defaultPrinter();
	if (info.state() == QPrinter::Error)
	{
		QMessageBox::warning(nullptr, "Failed", "Can not print.");
	}
	QPrinter printer(info, QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	connect(&preview, &QPrintPreviewDialog::paintRequested, this, &ReportTextEdit::OnPrintPreview);
	preview.exec();
}

void ReportTextEdit::openCellProperty()
{
	int firstRow = 0, numRow = 0, firstCol = 0, numCol = 0;
	textCursor().selectedTableCells(&firstRow, &numRow, &firstCol, &numCol);

	if (firstRow < 0 && firstCol < 0)
	{
		QTextTable* table = textCursor().currentTable();
		if (table)
		{
			QTextTableCell cell = table->cellAt(textCursor());
			QColor cellColor = cell.format().background().color();

			TableCellDialog dlg(cellColor, this, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
			if (dlg.exec() == QDialog::Accepted)
			{
				cell.setFormat(dlg.getTableCellFormat());
			}
		}
	}
	else
	{
		QTextTable* table = textCursor().currentTable();

		if (nullptr == table) return;

		TableCellDialog dlg(Qt::white, this, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

		if (dlg.exec() == QDialog::Accepted)
		{
			textCursor().beginEditBlock();
			for (int r = firstRow; r < firstRow + numRow; ++r)
			{
				for (int c = firstCol; c < firstCol + numCol; ++c)
				{
					QTextTableCell cell = table->cellAt(r, c);
					cell.setFormat(dlg.getTableCellFormat());
					QTextCharFormat fmt;
					fmt.setBackground(cell.format().background());
					mergeFormatOnWordOrSelection(fmt);
				}
			}
			textCursor().endEditBlock();
		}
	}
}
bool ReportTextEdit::loadFromDirName(const QString& dirName)
{
	QDir dir(STRING_MANAGER->report_format_dir_path + "/" + dirName);
	dir.setFilter((QDir::Files | QDir::NoSymLinks));

	QStringList nameFilters;
	nameFilters << "*.html";
	dir.setNameFilters(nameFilters);

	if (dir.isEmpty()) return false;

	QFileInfoList htmlList = dir.entryInfoList();
	if (htmlList.size() <= 0) return false;

	return load(dir.path() + "/" + htmlList.at(0).fileName());
}

void ReportTextEdit::OnPrintPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
	Q_UNUSED(printer);
#else
	print(printer);
#endif
}

void ReportTextEdit::OnPageWidthLimit()
{
	int widget_width = this->size().width();
	int document_width = static_cast<int>(document()->documentLayout()->documentSize().width());
	if (widget_width < document_width) undo();
}

bool ReportTextEdit::load(const QString &fileName)
{
	if (!QFile::exists(fileName))
		return false;
	
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return false;
	
	QByteArray data = file.readAll();
	QTextCodec *codec = Qt::codecForHtml(data);
	QString str = codec->toUnicode(data);

	if (Qt::mightBeRichText(str)) {
		setHtml(str);
	}
	else {
		str = QString::fromLocal8Bit(data);
		setPlainText(str);
	}

	setCurrentFileName(fileName);

	return true;
}

void ReportTextEdit::setCurrentFileName(const QString &fileName)
{
	m_fileName = fileName;
	document()->setModified(false);

	QString shownName;
	if (fileName.isEmpty())
		shownName = "untitled.txt";
	else
		shownName = QFileInfo(fileName).fileName();

	setWindowModified(false);
}

void ReportTextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	mergeCurrentCharFormat(format);
}

void ReportTextEdit::dropImage(const QUrl& url, const QImage& image)
{
	if (image.isNull()) return;

	document()->addResource(QTextDocument::ImageResource, url, image);

	QTextImageFormat imgFmt;
	imgFmt.setName(url.url());
	imgFmt.setWidth(image.size().width());
	imgFmt.setHeight(image.size().height());
	
	textCursor().beginEditBlock();
	{
		textCursor().insertImage(imgFmt);
		textCursor().insertText(" ");
	}
	textCursor().endEditBlock();
}

void ReportTextEdit::drawPageBoundaryLine(QPainter& painter)
{
	const int nMargin = 10;

	int vScrollBarVal = verticalScrollBar()->value() % static_cast<int>(document()->pageSize().height());
	int boundaryLineY = document()->pageSize().height() - nMargin - vScrollBarVal;

	QPoint emptyPos = QPoint(0, boundaryLineY);
	QSize emptySize = document()->pageSize().toSize();
	emptySize.rheight() = nMargin;
	painter.fillRect(QRect(emptyPos, emptySize), QColor(48, 48, 48, 255));

	emptyPos = QPoint(0, boundaryLineY + static_cast<int>(document()->pageSize().height()));
	painter.fillRect(QRect(emptyPos, emptySize), QColor(48, 48, 48, 255));
}

bool ReportTextEdit::isImageFormat(const QPoint& mousePos, int& cursorPos)
{
	QPoint layoutPos = mousePos;
	layoutPos.ry() += verticalScrollBar()->value();
	cursorPos = document()->documentLayout()->hitTest(layoutPos, Qt::ExactHit);

	if (cursorPos < 0) return false;

	QTextCursor cursor(document());
	cursor.setPosition(cursorPos);
	if (cursor.atEnd()) return false;

	cursorPos += 1;
	cursor.setPosition(cursorPos);
	QTextFormat format = cursor.charFormat();
	if (!format.isImageFormat()) return false;

	return true;
}

bool ReportTextEdit::findImageFormat(QTextBlock& block, QTextImageFormat& imgFmt, int imgCursorPos, int& fragmentPos, int& fragmentLen)
{
	QTextBlock::iterator it;

	for (it = block.begin(); !(it.atEnd()); ++it)
	{
		QTextFragment fragment = it.fragment();

		if (fragment.isValid())
		{
			if (fragment.charFormat().isImageFormat() && imgCursorPos == fragment.position())
			{
				fragmentPos = fragment.position();
				fragmentLen = fragment.length();
				imgFmt = fragment.charFormat().toImageFormat();
				return true;
			}
		}
	}
	return false;
}

void ReportTextEdit::setSeletedIamgeFormat(int imgCursorPos)
{
	QTextCursor cursor = textCursor();
	cursor.setPosition(imgCursorPos);

	int fragmentPos = 0;
	int fragmentLen = 0;
	QTextImageFormat imgfmt;
	bool res = findImageFormat(cursor.block(), imgfmt, imgCursorPos - 1, fragmentPos, fragmentLen);
	if (false == res) return;

	QRect rect = cursorRect(cursor);
	QPoint imgPos(viewport()->mapToParent(rect.topLeft()));
	QSize imgSize(imgfmt.width(), imgfmt.height());

	m_selectedImgFmt.setSelectedFormat(QRect(imgPos, imgSize), imgfmt.name(), fragmentPos, fragmentLen);
}

void ReportTextEdit::resizingImageFormat(const QPoint& pos, ImageResizingPointer pointer)
{
	if (false == m_selectedImgFmt.resizingFlag()) return;

	QSize newSize(m_selectedImgFmt.size());
	QSize prevSize(m_selectedImgFmt.size());

	int dx = pos.x() - m_clickedPos.x();
	int dy = pos.y() - m_clickedPos.y();

	int sign = 1;
	sign = safe_div(dy, std::abs(dy));
	int resizeRate = (std::abs(dx) > std::abs(dy)) ? (sign * std::abs(dx)) : (sign * std::abs(dy));

	switch (pointer)
	{
	case ImageResizingPointer::TopLeft:
	case ImageResizingPointer::TopRight:
		newSize = newSize.scaled(QSize(prevSize.width() - resizeRate, prevSize.height() - resizeRate), Qt::KeepAspectRatio);
		break;
	case ImageResizingPointer::BotRight:
	case ImageResizingPointer::BotLeft:
		newSize = newSize.scaled(QSize(prevSize.width() + resizeRate, prevSize.height() + resizeRate), Qt::KeepAspectRatio);
		break;
	case ImageResizingPointer::TopMid:
		newSize.rheight() -= dy;
		break;
	case ImageResizingPointer::BotMid:
		newSize.rheight() += dy;
		break;
	case ImageResizingPointer::MidLeft:
		newSize.rwidth() -= dx;
		break;
	case ImageResizingPointer::MidRight:
		newSize.rwidth() += dx;
		break;
	default:
		break;
	}

	m_clickedPos = pos;

	QSize pageSize = document()->pageSize().toSize();
	const QSize imageMinSize(30, 30);
	int margin = (int)document()->documentMargin();

	newSize.rwidth() = clamp(newSize.width(), imageMinSize.width(), pageSize.width() - margin * 2);
	newSize.rheight() = clamp(newSize.height(), imageMinSize.height(), pageSize.height() - margin * 2);

	updateResizingPointer(newSize);
}

void ReportTextEdit::updateResizingPointer(const QSize& newSize)
{
	QTextCursor cursor = textCursor();
	cursor.setPosition(m_selectedImgFmt.getFragmentPos());

	QRect rect = cursorRect(cursor);
	QPoint imgPos(viewport()->mapToParent(rect.topLeft()));

	QRect imgFmtRect(imgPos, newSize);
	m_selectedImgFmt.setImageRect(imgFmtRect);
	m_selectedImgFmt.updateResizingPointer();
}

bool ReportTextEdit::copyImageToReportDirectory(QString& htmlString, const std::vector<QString>& path_list)
{
	for (int i = 0; i < path_list.size(); ++i)
	{
		QFileInfo fi(path_list.at(i));
		QString newPath = STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(m_fileName).baseName() + "/" + fi.fileName();

		QImage img(path_list[i]);
		QFile::remove(newPath);
		img.save(newPath);
		htmlString.replace(path_list.at(i), newPath);
	}
	setHtml(htmlString);
	return true;
}

void ReportTextEdit::imageResourcePath(const QString& htmlString, std::vector<QString>& path_list)
{
	QString imgPathKey = "<img src=\"file:///";

	int index = 0;
	while (index >= 0)
	{
		index = htmlString.indexOf(imgPathKey, index);
		if (index == -1)
		{
			break;
		}
		else
		{
			QChar c = 0;
			QString path;
			index += imgPathKey.size();
			while ((c = htmlString.at(index++)) != '\"')
			{
				path.push_back(c);
			}
			path_list.push_back(path);
		}
	}
}

void ReportTextEdit::resourceCopyToReportDirectory()
{
	QString imgUrl = "<img src=\"";
	QString htmlString = toHtml();
	std::vector<QString> resource_list;
	int index = 0;
	while (index >= 0)
	{
		index = 
		index = htmlString.indexOf(imgUrl, index);
		if (index == -1)
		{
			break;
		}
		else
		{
			QChar c = 0;
			QString path;
			index += imgUrl.size();
			while ((c = htmlString.at(index++)) != '\"')
			{
				path.push_back(c);
			}
			if (path.contains("file:///")) continue;
			resource_list.push_back(path);
		}
	}

	for (auto resource_name : resource_list)
	{
		QVariant v = document()->resource(QTextDocument::ImageResource, resource_name);
		QImage img = qvariant_cast<QImage>(v);
		QString savePath = STRING_MANAGER->report_format_dir_path + "/" + QFileInfo(m_fileName).baseName() + "/" + resource_name + ".png";
		QSize s = img.size();
		QFile::remove(savePath);
		bool r = img.save(savePath);
		savePath = "file:///" + savePath;
		htmlString.replace(resource_name, savePath);
	}
	setHtml(htmlString);
}

bool ReportTextEdit::checkSpecialCharacters(const QString& str)
{
	QRegExp reg1("^[a-zA-Z0-9_ ]*$");
	return str.contains(reg1);
}

void ReportTextEdit::setTextCursorPosition(int cursorPos)
{
	if (cursorPos < 0) return;
	QTextCursor cursor = textCursor();
	cursor.setPosition(cursorPos);
	setTextCursor(cursor);
}

void ReportTextEdit::selectFragment(int fragmentPos, int fragmentLen)
{
	QTextCursor cursor = textCursor();
	cursor.setPosition(fragmentPos);
	cursor.setPosition(fragmentPos + fragmentLen, QTextCursor::KeepAnchor);
	setTextCursor(cursor);
}