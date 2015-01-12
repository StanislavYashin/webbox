#include "GlowLabel.h"

GlowLabel::GlowLabel(QWidget* parent)
{

}

GlowLabel::~GlowLabel()
{
    
}

void GlowLabel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this); 
}

void GlowLabel::mousePressEvent(QMouseEvent *event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		 
		break;
	case Qt::RightButton:
		
		break;
	default:
		QLabel::mousePressEvent(event);
	}
}

void GlowLabel::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) 
	{
		 
	}

	QLabel::mouseReleaseEvent(event);
}

void GlowLabel::mouseMoveEvent(QMouseEvent *event)
{
	QLabel::mouseMoveEvent(event);
}

