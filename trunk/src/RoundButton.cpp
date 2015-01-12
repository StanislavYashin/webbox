#include "RoundButton.h"
#include "Config.h"

RoundButton::RoundButton(int w, int h, QWidget *parent)
	:QToolButton(parent)
{ 
	//设置文本颜色
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(255, 255,255));
	setPalette(text_palette);

	//设置文本粗体
	QFont font = QFont("SIMSUN");
	//QFont &text_font = const_cast<QFont &>(font());
	//text_font.setWeight(QFont::Bold);
	font.setPixelSize(12);
	setFont(font); 
	setToolButtonStyle(Qt::ToolButtonTextOnly);
	
	//设置图标
	/*QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(QSize(icon_w, icon_h));*/

	setFixedSize(w, h);
	//设置大小
	//setFixedSize(pixmap.width() + 25, pixmap.height() + 25);
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	m_MouseOver = false;
	m_MousePress = false;
}

RoundButton::~RoundButton()
{

}

void RoundButton::enterEvent(QEvent *)
{
	m_MouseOver = true;
}

void RoundButton::leaveEvent(QEvent *)
{
	m_MouseOver = false;
	setMousePress(false);
}

void RoundButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = true;
		QPalette text_palette = palette();
		text_palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
		setPalette(text_palette);
		repaint(); 
		emit clicked();
	}
}

void RoundButton::mouseReleaseEvent(QMouseEvent *event)
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

void RoundButton::setMousePress(bool mouse_press)
{
	this->m_MousePress = mouse_press;
	update();
}

void RoundButton::paintEvent(QPaintEvent *event)
{
	if (m_MousePress)
	{
		//painterInfo(255, 0, 0, 255, 255, 255);
		painterInfo(0, 100, 0, 150, 200, 255);
	}
	else
	{
		if (m_MouseOver)
		{
			//绘制鼠标移到按钮上的按钮效果
			painterInfo(255, 0, 0, 150, 200, 255);
			//painterInfo(0, 100, 0, 255, 255, 255);
		}
		else
		{
			painterInfo(24, 116, 205, 150, 200, 255); 
		}
	} 

	QToolButton::paintEvent(event); 
}

void RoundButton::painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(r, g, b, top_color));
	linear.setColorAt(0.5, QColor(r, g, b, middle_color));
	linear.setColorAt(1, QColor(r, g, b, bottom_color));
	painter.setBrush(linear);
	painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
	painter.drawRoundedRect(rect(),10,10); 
}
