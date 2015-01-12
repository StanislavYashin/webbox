#pragma once

#include <QtWidgets>

#include "Config.h"
#include "Common.h"
#include <QMouseEvent>
#include <QPainter>

class IconWidget : public QToolButton
{ 
	Q_OBJECT

public:

	explicit IconWidget(int w, int h, QString picPath, QColor normalColor, QColor downColor, QColor enterColor, QWidget *parent = 0);

	~IconWidget();

	void setMousePress(bool mouse_press);

	void setRoundCorner(int radius)
	{
		m_radius = radius;
		this->update();
	}

signals:

	void OnWidgetClicked(IconWidget *);

protected:

	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(QColor clr);
	
public:

	_public(bool, MouseOver);
	_public(bool, MousePress);

	int m_radius;

	QColor m_enterColor;
	QColor m_downColor;
	QColor m_normalColor;
};