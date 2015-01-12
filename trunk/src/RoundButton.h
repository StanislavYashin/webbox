#pragma once

#include <QtWidgets>

#include "Config.h"
#include "Common.h"
#include <QMouseEvent>
#include <QPainter>

class RoundButton : public QToolButton
{ 
public: 

	explicit RoundButton(int w, int h, QWidget *parent = 0);
	~RoundButton();
	void setMousePress(bool mouse_press);

protected: 

	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color);
	 
public:

	_public(bool, MouseOver)
	_public(bool, MousePress)
};