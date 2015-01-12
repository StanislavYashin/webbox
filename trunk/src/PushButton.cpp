#include "PushButton.h"

PushButton::PushButton(QWidget *parent)
	: QPushButton(parent)
{
	m_state = eButtonState::BTN_NORMAL; 
	mouse_press = false;
}

PushButton::~PushButton()
{

}
 
void PushButton::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	setFixedSize(QPixmap(pic_name).size());
}

void PushButton::enterEvent(QEvent *)
{
	m_state = eButtonState::BTN_HOVER;
	update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		m_state = eButtonState::BTN_PRESS;
		update();
	}
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if (mouse_press  && this->rect().contains(event->pos()))
	{
		mouse_press = false;
		m_state = eButtonState::BTN_HOVER;
		update();
		emit clicked();
	}
}

void PushButton::leaveEvent(QEvent *)
{
	m_state = BTN_NORMAL;
	update();
}

void PushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pixmap;
	switch (m_state)
	{
	case BTN_NORMAL:
	{
		pixmap.load(pic_name);
		break;
	}
	case BTN_HOVER:
	{
		pixmap.load(pic_name + QString("_hover"));
		break;
	}
	case BTN_PRESS:
	{
		pixmap.load(pic_name + QString("_pressed"));
		break;
	}
	case BTN_NONE:
	{
		pixmap.load(pic_name);
		break;
	}
	default:
		pixmap.load(pic_name);
	}

	painter.drawPixmap(rect(), pixmap);
}
