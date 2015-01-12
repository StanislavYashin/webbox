#include "IconWidget.h"
#include "Config.h"

IconWidget::IconWidget(int w, int h,QString path, QColor normalColor, QColor downColor,QColor enterColor,QWidget *parent)
	: QToolButton(parent)
{ 
	m_radius = 10;

	setToolButtonStyle(Qt::ToolButtonIconOnly);
	 
	setFixedSize(w, h);
	 
	setAutoRaise(true);
	setObjectName("transparentToolButton"); 

	QPixmap pixmap(path);
	setIcon(pixmap);

	m_normalColor = normalColor;
	m_enterColor = enterColor;
	m_downColor = downColor;

	m_MouseOver = false;
	m_MousePress = false;
}

IconWidget::~IconWidget()
{

}

void IconWidget::enterEvent(QEvent *)
{
	m_MouseOver = true;
}

void IconWidget::leaveEvent(QEvent *)
{
	m_MouseOver = false;
	setMousePress(false);
}

void IconWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = true;
		QPalette text_palette = palette();
		text_palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
		setPalette(text_palette);
		repaint(); 
		emit OnWidgetClicked(this);
	}
}

void IconWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = false;
		QPalette text_palette = palette();
		text_palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
		setPalette(text_palette);
		repaint();
	}
}

void IconWidget::setMousePress(bool mouse_press)
{
	this->m_MousePress = mouse_press;
	update();
}

void IconWidget::paintEvent(QPaintEvent *event)
{
	if (m_MousePress)
	{ 
		painterInfo(m_downColor);       // .red(), m_downColor.green(), m_downColor.blue(), 255, 255, 255);
	}
	else
	{
		if (m_MouseOver)
		{ 
			painterInfo(m_enterColor);  // .red(), m_enterColor.green(), m_enterColor.blue(), 255, 255, 255);
		}
		else
		{
			painterInfo(m_normalColor); // .red(), m_normalColor.green(), m_normalColor.blue(), 255, 255, 255);
		}
	}

	QToolButton::paintEvent(event);
}

void IconWidget::painterInfo(QColor clr) // int r, int g, int b, int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 0);
	painter.setPen(pen); 
	/*QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(r, g, b, top_color));
	linear.setColorAt(0.5, QColor(r, g, b, middle_color));
	linear.setColorAt(1, QColor(r, g, b, bottom_color));*/
	painter.setBrush(QBrush(clr));// linear);
	painter.setRenderHints(QPainter::HighQualityAntialiasing);// | QPainter::TextAntialiasing);
	painter.drawRoundedRect(rect(), m_radius, m_radius);
} 