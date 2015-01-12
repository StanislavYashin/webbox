#pragma once

#include <QtWidgets>

#include "Config.h"
#include "Common.h"
#include <QMouseEvent>
#include <QPainter>

class BannerButton : public QToolButton
{

public:

	explicit BannerButton(QString pic_name, int w, int h, int icon_w, int icon_h, QWidget *parent = 0);
	~BannerButton();
	void setMousePress(bool mouse_press);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);

public:

	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
}; 