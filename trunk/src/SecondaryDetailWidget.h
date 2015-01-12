#pragma once

#include <QtWidgets>

#include "Common.h"
#include "Config.h" 
#include <QPainter>
#include <QToolButton>
#include <QMouseEvent> 
#include "SecondaryDetailWidget.define.h"

class SecondaryDetailWidget : public QWidget
{
public:

	explicit SecondaryDetailWidget(int w, int h, bool isGlow, QString pic_name, QString title, QWidget *parent = 0);

	virtual ~SecondaryDetailWidget();

	void setMousePress(bool mouse_press);

	void setGameInfo(const DetailGameInfo &info);

protected:

	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color);

private:

	QVBoxLayout *__topMidLayout;

	DetailGameInfo __info;

	_private(QPixmap, icon); 
	_public(bool, MouseOver);
	_public(bool, MousePress);
};