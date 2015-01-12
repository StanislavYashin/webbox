#pragma once

#include <QtWidgets>
#include "Common.h"
#include "Config.h"
#include "IconWidget.h" 

class RankingLabel : public QWidget
{
	Q_OBJECT
public:
	RankingLabel(int w, int h, int picLen, QString iconPath, QString title, QString type,QString price, QWidget *parent = 0);
	virtual ~RankingLabel();

	void setRating(int rating);

	void setColor(QColor clr){ m_color = clr; }

	QLabel *m_icon;
	QLabel *m_title;
	QLabel *m_type;
	QLabel *m_platform;
	QLabel *m_price; 

	QHBoxLayout *main_layout;

	void setMousePress(bool mouse_press);

	_public(bool, MouseOver);
	_public(bool, MousePress);

	QColor m_color;

signals:

	void clicked();

protected:

	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	virtual void painterInfo(int top_color, int middle_color, int bottom_color);
};