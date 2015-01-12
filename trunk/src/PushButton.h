#pragma once

#include "Common.h"
#include <QtWidgets>
#include <qpainter.h>
#include "PushButton.define.h"

class PushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit PushButton(QWidget *parent = 0);
	virtual ~PushButton();

	void setPicName(QString pic_name);

protected:

	void paintEvent(QPaintEvent *pe);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	
	_private(eButtonState, state);
	QString pic_name;

	int btn_width; //按钮宽度
	int btn_height; //按钮高度
	bool mouse_press; //按钮左键是否按下
};