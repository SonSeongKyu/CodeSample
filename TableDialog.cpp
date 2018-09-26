#include "TableDialog.h"

#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qgroupbox.h>
#include <qcolordialog.h>

#include "StyleManager.h"

TableDialog::TableDialog(QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f), m_tableFormat(), m_defaultTable(), m_rowSpin(nullptr), m_colSpin(nullptr), m_borderColorBtn(nullptr)
{
	setFixedSize(250, 150);
	setStyleSheet(STYLE_MANAGER->mainFrame);
	setWindowTitle("Table Property");

	m_tableFormat.setCellSpacing(0);
	m_tableFormat.setCellPadding(nPadding);
	m_tableFormat.setBorderBrush(QBrush(nBorderColor));

	createUI();
}

TableDialog::~TableDialog()
{

}

void TableDialog::createUI()
{
	QVBoxLayout* vMainLayout = new QVBoxLayout;
	setLayout(vMainLayout);

	vMainLayout->addWidget(createTableProperty(), 1);
	vMainLayout->addWidget(createBtnGroup(), 0);
}

QWidget* TableDialog::createTableProperty()
{
	QGroupBox* group = new QGroupBox("Table Property", this);
	group->setStyleSheet(STYLE_MANAGER->groupBox);
	QVBoxLayout* vGroupLayout = new QVBoxLayout;
	group->setLayout(vGroupLayout);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setSpacing(5);

	QLabel* rowLabel = new QLabel("Row", group);
	hLayout->addWidget(rowLabel, 0);
	m_rowSpin = new QSpinBox(group);
	m_rowSpin->setStyleSheet(STYLE_MANAGER->spinBox);
	m_rowSpin->setValue(2);
	hLayout->addWidget(m_rowSpin, 1);

	QLabel* colLabel = new QLabel("Col", group);
	hLayout->addWidget(colLabel, 0);
	m_colSpin = new QSpinBox(group);
	m_colSpin->setStyleSheet(STYLE_MANAGER->spinBox);
	m_colSpin->setValue(2);
	hLayout->addWidget(m_colSpin, 1);
	vGroupLayout->addItem(hLayout);

	hLayout = new QHBoxLayout;
	hLayout->setSpacing(5);

	QLabel* paddingLabel = new QLabel("Padding", group);
	hLayout->addWidget(paddingLabel, 0);
	QSpinBox* paddingSpin = new QSpinBox(group);
	paddingSpin->setStyleSheet(STYLE_MANAGER->spinBox);
	paddingSpin->setValue(nPadding);
	hLayout->addWidget(paddingSpin, 1);

	connect(paddingSpin, SIGNAL(valueChanged(int)), this, SLOT(OnPaddingChange(int)));

	QPixmap pix(16, 16);
	pix.fill(nBorderColor);
	m_borderColorBtn = new QPushButton(QIcon(pix), "Border Color", group);
	m_borderColorBtn->setStyleSheet(STYLE_MANAGER->pushButton);
	hLayout->addWidget(m_borderColorBtn, 2);

	connect(m_borderColorBtn, &QPushButton::clicked, this, &TableDialog::OnColorChange);

	vGroupLayout->addItem(hLayout);
	
	return group;
}

QWidget* TableDialog::createMEDIPDefaultTableButton()
{
	QGroupBox* group = new QGroupBox("Default Table", this);
	group->setStyleSheet(STYLE_MANAGER->groupBox);
	QVBoxLayout* vGroupLayout = new QVBoxLayout;
	group->setLayout(vGroupLayout);

	QPushButton* btn = new QPushButton("Auto Patient Data", group);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	vGroupLayout->addWidget(btn);

	btn = new QPushButton("Texture Feature Table", group);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	vGroupLayout->addWidget(btn);

	return group;
}

QWidget* TableDialog::createBtnGroup()
{
	QWidget* btnArea = new QWidget(this);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setMargin(0);
	btnArea->setLayout(hLayout);

	QPushButton* btn = new QPushButton("OK", btnArea);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	hLayout->addWidget(btn);

	connect(btn, &QPushButton::clicked, this, &TableDialog::OnFinished);

	btn = new QPushButton("Cancel", btnArea);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	hLayout->addWidget(btn);

	connect(btn, &QPushButton::clicked, this, &TableDialog::OnCancel);

	return btnArea;
}

int TableDialog::getColumn()
{
	if (m_colSpin)
		return m_colSpin->value();
	return 0;
};

int TableDialog::getRow()
{
	if (m_rowSpin)
		return m_rowSpin->value();
	return 0;
};

void TableDialog::OnFinished()
{
	emit accept();
}

void TableDialog::OnCancel()
{
	this->close();
}

void TableDialog::OnPaddingChange(int val)
{
	m_tableFormat.setCellPadding(val);
}

void TableDialog::OnColorChange()
{
	QColorDialog dlg(this);
	dlg.setStyleSheet("color : white");
	if (dlg.exec() == QDialog::Accepted)
	{
		QColor color = dlg.selectedColor();
		m_tableFormat.setBorderBrush(QBrush(color));
		QPixmap pix(16, 16);
		pix.fill(color);
		m_borderColorBtn->setIcon(pix);
	}
}

//========================================================================

TableCellSplitDialog::TableCellSplitDialog(QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f), m_columEditBox(nullptr), m_rowEditBox(nullptr)
{
	setFixedSize(200, 150);
	setStyleSheet(STYLE_MANAGER->mainFrame);
	setWindowTitle("Split Cell");

	QWidget* widget = new QWidget(this);
	widget->setFixedSize(this->size());

	QVBoxLayout* vMainLayout = new QVBoxLayout;
	widget->setLayout(vMainLayout);

	QGroupBox* group = new QGroupBox("Number", this);
	//group->setStyleSheet(STYLE_MANAGER->imgDialogGroupBox);

	QVBoxLayout* vLayout = new QVBoxLayout;
	group->setLayout(vLayout);

	vLayout->addWidget(createRowNumberGroup(group));
	vLayout->addWidget(createColumNumberGroup(group));

	vMainLayout->addWidget(group, 1);
	vMainLayout->addWidget(createBtnGroup(), 0);
}


TableCellSplitDialog::~TableCellSplitDialog()
{
}

QWidget* TableCellSplitDialog::createRowNumberGroup(QWidget* parent)
{
	QWidget* group = new QWidget(parent);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setSpacing(0);
	hLayout->setMargin(0);
	group->setLayout(hLayout);

	QLabel* label = new QLabel("Column", group);
	hLayout->addWidget(label, 1);

	m_columEditBox = new QSpinBox(group);
	m_columEditBox->setFixedWidth(this->size().width() / 2);
	m_columEditBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_columEditBox->setMaximum(50);
	m_columEditBox->setValue(2);
	hLayout->addWidget(m_columEditBox, 1, Qt::AlignRight);

	return group;
}

QWidget* TableCellSplitDialog::createColumNumberGroup(QWidget* parent)
{
	QWidget* group = new QWidget(parent);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setSpacing(0);
	hLayout->setMargin(0);
	group->setLayout(hLayout);

	QLabel* label = new QLabel("Row", group);
	hLayout->addWidget(label, 1);

	m_rowEditBox = new QSpinBox(group);
	m_rowEditBox->setFixedWidth(this->size().width() / 2);
	m_rowEditBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_rowEditBox->setMaximum(50);
	m_rowEditBox->setValue(2);
	hLayout->addWidget(m_rowEditBox, 1, Qt::AlignRight);

	return group;
}

QWidget* TableCellSplitDialog::createBtnGroup()
{
	QWidget* btnArea = new QWidget(this);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setMargin(0);
	btnArea->setLayout(hLayout);

	QPushButton* btn = new QPushButton("OK", btnArea);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	hLayout->addWidget(btn);

	connect(btn, &QPushButton::clicked, this, &TableCellSplitDialog::OnFinished);

	btn = new QPushButton("Cancel", btnArea);
	btn->setStyleSheet(STYLE_MANAGER->pushButton);
	hLayout->addWidget(btn);

	connect(btn, &QPushButton::clicked, this, &TableCellSplitDialog::OnCancel);

	return btnArea;
}

std::pair<int, int> TableCellSplitDialog::getSplitNumber()
{
	std::pair<int, int> res(m_columEditBox->value(), m_rowEditBox->value());
	return res;
}

void TableCellSplitDialog::OnFinished()
{
	emit accept();
}

void TableCellSplitDialog::OnCancel()
{
	this->close();
}

//=======================================================================================

TableCellDialog::TableCellDialog(const QColor& cellColor, QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f), m_tableCellFormat()
{
	setFixedSize(250, 165);
	setStyleSheet(STYLE_MANAGER->mainFrame);
	setWindowTitle("Cell Property");

	m_tableCellFormat.setBackground(QBrush(cellColor));

	QVBoxLayout* vMainLayout = new QVBoxLayout;
	setLayout(vMainLayout);

	QGroupBox* group = new QGroupBox("Padding", this);
	group->setStyleSheet(STYLE_MANAGER->groupBox);
	vMainLayout->addWidget(group, 1);

	QGridLayout* gridLay = new QGridLayout;
	gridLay->setSpacing(5);
	group->setLayout(gridLay);

	QLabel* leftLabel = new QLabel("Left", group);
	gridLay->addWidget(leftLabel, 0, 0);

	m_leftSpinBox = new QSpinBox(group);
	m_leftSpinBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_leftSpinBox->setValue(TableDialog::getTablePadding());
	gridLay->addWidget(m_leftSpinBox, 0, 1);

	QLabel* rightLabel = new QLabel("Right", group);
	gridLay->addWidget(rightLabel, 0, 2);

	m_rightSpinBox = new QSpinBox(group);
	m_rightSpinBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_rightSpinBox->setValue(TableDialog::getTablePadding());
	gridLay->addWidget(m_rightSpinBox, 0, 3);

	QLabel* topLabel = new QLabel("Top", group);
	gridLay->addWidget(topLabel, 1, 0);

	m_topSpinBox = new QSpinBox(group);
	m_topSpinBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_topSpinBox->setValue(TableDialog::getTablePadding());
	gridLay->addWidget(m_topSpinBox, 1, 1);

	QLabel* botLabel = new QLabel("Bottom", group);
	gridLay->addWidget(botLabel, 1, 2);

	m_bottomSpinBox = new QSpinBox(group);
	m_bottomSpinBox->setStyleSheet(STYLE_MANAGER->spinBox);
	m_bottomSpinBox->setValue(TableDialog::getTablePadding());
	gridLay->addWidget(m_bottomSpinBox, 1, 3);

	QPixmap pix(16, 16);
	pix.fill(cellColor);
	m_colorBtn = new QPushButton(QIcon(pix), "Cell Color", this);
	m_colorBtn->setStyleSheet(STYLE_MANAGER->pushButton);
	vMainLayout->addWidget(m_colorBtn);

	connect(m_colorBtn, &QPushButton::clicked, this, &TableCellDialog::OnColorChange);

	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->setSpacing(5);

	QPushButton* btnOK = new QPushButton("OK", this);
	btnOK->setStyleSheet(STYLE_MANAGER->pushButton);
	btnLayout->addWidget(btnOK);

	connect(btnOK, &QPushButton::clicked, this, &TableCellDialog::OnFinished);

	QPushButton* btnCancel = new QPushButton("Cancel", this);
	btnCancel->setStyleSheet(STYLE_MANAGER->pushButton);
	btnLayout->addWidget(btnCancel);

	connect(btnCancel, &QPushButton::clicked, this, &TableCellDialog::OnCancel);

	vMainLayout->addItem(btnLayout);
}

TableCellDialog::~TableCellDialog()
{

}

const QTextTableCellFormat& TableCellDialog::getTableCellFormat()
{
	m_tableCellFormat.setLeftPadding(m_leftSpinBox->value());
	m_tableCellFormat.setRightPadding(m_rightSpinBox->value());
	m_tableCellFormat.setTopPadding(m_topSpinBox->value());
	m_tableCellFormat.setBottomPadding(m_bottomSpinBox->value());

	return m_tableCellFormat;
}

void TableCellDialog::OnFinished()
{
	emit accept();
}

void TableCellDialog::OnCancel()
{
	this->close();
}

void TableCellDialog::OnColorChange()
{
	QColorDialog dlg(this);
	if (dlg.exec() == QDialog::Accepted)
	{
		QColor color = dlg.selectedColor();
		m_tableCellFormat.setBackground(QBrush(color));
		QPixmap pix(16, 16);
		pix.fill(color);
		m_colorBtn->setIcon(QIcon(pix));
	}
}