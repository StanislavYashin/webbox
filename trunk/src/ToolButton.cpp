#include "ToolButton.h"
#include "GlowEffect.h"
#include "QtWidgets"

ToolButton::ToolButton(int w,int h,QPixmap pic, QWidget *parent)
    :QToolButton(parent)
{
    //设置文本颜色
    //QPalette text_palette = palette();
    //text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
    //setPalette(text_palette);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true);
 

    //设置文本粗体
    QFont &text_font = const_cast<QFont &>(font());
    text_font.setWeight(QFont::Bold);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //setStyleSheet("QToolButton{border:0px;color:white;}");

	/*GlowEffect *effect = new GlowEffect(this);
	effect->setRadius(5);
	effect->setGlowColor(Qt::blue);*/
	//this->setGraphicsEffect(effect);

    //设置图标
    QPixmap pixmap(pic);
    pixmap = pixmap.scaled(w,h,Qt::AspectRatioMode::KeepAspectRatio,Qt::TransformationMode::SmoothTransformation);
    setIcon(pixmap);
    setAutoRaise(true);
    setIconSize(pixmap.size());
    resize(pixmap.size());// , TOOLWIDGET_H);
    //设置大小
    setFixedSize(w+35, h + 35);

    setFont(ProfileInstance().AppFont);

    setObjectName("transparentToolButton");

    m_MouseOver =  false;
    m_MousePress = false;  
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *)
{
    m_MouseOver = true;
}

void ToolButton::leaveEvent(QEvent *)
{
    m_MouseOver = false;
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
		m_MousePress = true;
        emit clicked();
    }
}

void ToolButton::setMousePress(bool mouse_press)
{
    this->m_MousePress = mouse_press;
    update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{ 
    if (m_MouseOver)
    {
        //绘制鼠标移到按钮上的按钮效果
		painterInfo(100, 100, 100);
    }
    else
    {
        if (m_MousePress)
        { 
            painterInfo(100, 150, 200);
        }
    }

    QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{ 
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(0, 230, 230, top_color));
	linear.setColorAt(0.5, QColor(0, 230, 230, middle_color));
	linear.setColorAt(1, QColor(0, 230, 230, bottom_color));
	painter.setBrush(linear);
	painter.drawRoundedRect(rect(), 5, 5);// .drawRect(rect());
}
