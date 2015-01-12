#include "GridContentWidget.h"

GridContentWidget::GridContentWidget(int row_cnt,int col_cnt,QWidget *parent)
	:QWidget(parent)
{
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));  
	this->setPalette(palette);
	this->setAutoFillBackground(true);

	curRow = curCol = 0;

	nRow = row_cnt;
	nCol = col_cnt;
	
	main_layout = new QGridLayout();

	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setMargin(0);
	main_layout->setSpacing(12);
	
	for (int i = 0; i < nRow; ++i)
	{
		main_layout->setRowMinimumHeight(i,50);
		for (int j = 0; j < nCol; ++j)
		{
			main_layout->addWidget(new QWidget(), i, j);
		}
	}

	setLayout(main_layout);
}

GridContentWidget::~GridContentWidget()
{

}

void GridContentWidget::addItem(AppletWidget *widget)
{
	main_layout->addWidget(widget,curRow,curCol);

	if (curCol + 1 < nCol)
	{
		++curCol;
	}
	else
	{
		++curRow;
		curCol = 0;
	}
}

void GridContentWidget::removeItem(AppletWidget *widget)
{
	main_layout->removeWidget(widget);
	delete widget;
}