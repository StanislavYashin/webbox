#pragma once

#include <QPainter>
#include <QToolButton>
#include <QMouseEvent>
#include "Config.h"
#include "Common.h"

#include "CommonProperty.hpp"

class AppletWidget : public QToolButton
{
	Q_OBJECT
public:
	explicit AppletWidget(int w, int h, bool isGlow, Webbox::Data::CommonProperty *itemProperty, QWidget *parent=0);

	virtual ~AppletWidget();

	void setMousePress(bool mouse_press);

	void setProperty(Webbox::Data::CommonProperty * prop);

	/*void setVisible(bool vis)
	{
		m_visible = vis;
		update();
	}*/

protected:

	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color);

signals:
	 
	void labelPress();

public slots:
	//void OnClicked();

private:

	//bool m_visible;

	QLabel *iconLabel;
	QLabel *lb_title; 
	_private(QPixmap, icon);

	_public(bool, MouseOver)
	_public(bool, MousePress)
};