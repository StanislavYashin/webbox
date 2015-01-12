#include "BannerButton.h"

BannerButton::BannerButton(QString pic_name,int w,int h, int icon_w,int icon_h, QWidget *parent)
	:QToolButton(parent)
{
	//设置文本颜色
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	setPalette(text_palette);

	//设置文本粗体
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setWeight(QFont::Bold);
	text_font.setPointSize(10);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//设置图标
	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(QSize(icon_w,icon_h));

	setFixedSize(w, h);

	//设置大小
	//setFixedSize(pixmap.width() + 25, pixmap.height() + 25);
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
}

BannerButton::~BannerButton()
{

}

void BannerButton::enterEvent(QEvent *)
{
	mouse_over = true;
}

void BannerButton::leaveEvent(QEvent *)
{
	mouse_over = false; 
}

void BannerButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		setMousePress(true);
		emit clicked();
	}
}

void BannerButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void BannerButton::paintEvent(QPaintEvent *event)
{
	if (mouse_press)
	{
		painterInfo(0, 180, 255);
	}
	else if (mouse_over)
	{
		//绘制鼠标移到按钮上的按钮效果
		painterInfo(0, 100, 150);
	} 

	QToolButton::paintEvent(event);
}

void BannerButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	QColor color = QColor(255, 130, 71);
	/*linear.setColorAt(0, QColor(135, 206, 235, top_color));
	linear.setColorAt(0.5, QColor(135, 206, 235, middle_color));
	linear.setColorAt(1, QColor(135, 206, 235, bottom_color));*/
	linear.setColorAt(0, QColor(255, 255, 255, top_color));
	linear.setColorAt(0.5, QColor(255, 255, 255, middle_color));
	linear.setColorAt(1, QColor(255, 255, 255, bottom_color));
	painter.setBrush(linear);
	painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
	painter.drawRect(rect());
}
