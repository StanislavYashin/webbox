#pragma once

#include <QtWidgets>
#include "Config.h"
#include "Common.h"
#include "AppletWidget.h"

class GridContentWidget : public QWidget
{
public:
	explicit GridContentWidget(int,int,QWidget *parent = 0);
	virtual ~GridContentWidget();

	void addItem(AppletWidget *widget);
	void removeItem(AppletWidget *widget);

protected:

	QGridLayout *main_layout;
	int nRow, nCol;
	int curRow, curCol;
}; 