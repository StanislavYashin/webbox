#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include "Common.h"

class ImageLabel : QLabel
{
Q_OBJECT

public:

	explicit ImageLabel(QWidget *parent = 0);

	~ImageLabel();

protected:

	virtual void paintEvent(QPaintEvent *event);

	//virtual void mousePressEvent(QMouseEvent *event);
	/*virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseEnter(QMouseEvent *event);*/

};
