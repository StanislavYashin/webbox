#pragma once

#include "OverlayWidget.h"

#ifndef Q_DECL_OVERRIDE
#define Q_DECL_OVERRIDE override
#endif
 
class LoadingOverlay : public OverlayWidget
{
public:
	LoadingOverlay(QWidget * parent = 0) : OverlayWidget(parent) 
	{
		setAttribute(Qt::WA_TranslucentBackground);
	}
protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE
	{
		QPainter p(this);
		p.fillRect(rect(), QColor(100, 100, 100, 128));
		p.setPen(QColor(200, 200, 255, 255));
		p.setFont(QFont("arial,helvetica", 48));
		p.drawText(rect(), "Loading...", Qt::AlignHCenter | Qt::AlignTop);
	}
};