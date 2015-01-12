#include "AeroButton.h"
#include "Config.h"

QMap<int, QList<AeroButton*>> AeroButton::buttonList = QMap<int, QList<AeroButton*>>();

QMap<int, AeroButton*> AeroButton::activeGroup = QMap<int,AeroButton*>();

AeroButton::AeroButton(int groupid, const QColor &textColor, QWidget * parent, eIconPosition pos)
	: QPushButton(parent),
    m_hovered(false),
    m_pressed(false),
    m_color(Qt::gray),
    m_highlight(Qt::lightGray),
    m_shadow(Qt::black),
    m_opacity(1.0),
    m_roundness(0),
	m_icon_position(pos)
{
	if (!buttonList.contains(groupid)) 
		buttonList[groupid] = QList<AeroButton*>();  
	buttonList[groupid].append(this);
 
	setObjectName("AeroWidget");
	setStyleSheet("QPushButton#AeroWidget{background:transparent; border-color:transparent;}");

	m_title = new QLabel();
	m_icon  = new QLabel();

	setTextColor(textColor); 

	main_layout = new QGridLayout();

	main_layout->addWidget(m_title, 0, 1, Qt::AlignLeft);
	main_layout->addWidget(m_icon , 0, 0, Qt::AlignCenter);

	setLayout(main_layout);

	//this->setGraphicsEffect(Profile::generateGlowEffect(QColor(255, 255, 255), 5));
}

AeroButton::~AeroButton()
{
	
}

void AeroButton::paintEvent(QPaintEvent * pe)
{  
	//QPushButton::paintEvent(pe);

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
 
	qreal opacity = m_opacity;

    QColor button_color;
    if(this->isEnabled())
    {
        m_hovered ? button_color = m_highlight : button_color = m_color;

        if(m_pressed)
        {
            button_color = m_highlight.darker(50);
			opacity = 0.6; 
        }
		else if (m_hovered)
		{
			opacity = 0.5;
		}
    }
    else
    {
		button_color = QColor(50, 50, 50);
    } 

    QRect button_rect = this->geometry();

    //outline
    painter.setPen(QPen(QBrush(Qt::transparent), 0.0));
    QPainterPath outline;
    outline.addRoundedRect(0, 0, button_rect.width(), button_rect.height(), m_roundness, m_roundness);
	painter.setOpacity(opacity);
    painter.drawPath(outline); 

	QColor clr = QColor(m_shadow);

	if (!m_pressed && !m_hovered)
	{
		clr.setAlpha(50);
	}

    //gradient
    /*QLinearGradient gradient(0, 0, 0, button_rect.height());
	gradient.setSpread(QGradient::PadSpread); 
    gradient.setColorAt(0.0, button_color);  
	gradient.setColorAt(0.5, clr);  
    gradient.setColorAt(1.0, button_color);*/

	//QBrush brush(gradient);
	QBrush brush(clr);
    painter.setBrush(brush); 
	painter.setPen(Qt::NoPen);// QPen(QBrush(button_color), 0.0));

    //main button
    /*QPainterPath painter_path;
    painter_path.addRoundedRect(1, 1, button_rect.width() - 2, button_rect.height() - 2, m_roundness, m_roundness);
    painter.setClipPath(painter_path); 
    painter.setOpacity(m_opacity);
    painter.drawRoundedRect(1, 1, button_rect.width() - 2, button_rect.height() - 2, m_roundness, m_roundness);*/

	QPainterPath painter_path;
	painter_path.addRoundedRect(0, 0, button_rect.width(), button_rect.height(), m_roundness, m_roundness);
	painter.setClipPath(painter_path);
	painter.setOpacity(opacity);
	painter.drawRoundedRect(0, 0, button_rect.width(), button_rect.height(), m_roundness, m_roundness);

    //glass highlight
   /* painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(QBrush(Qt::white), 0.01));
    painter.setOpacity(0.30);
    painter.drawRect(1, 1, button_rect.width() - 2, (button_rect.height() / 2) - 2);*/

	const int OFFSET = 6;

    //text
    /*QString text = this->text();
    if(!text.isNull())
    {
		QFont font = this->font();
		painter.setFont(font);
		painter.setPen(Qt::white);
		painter.setOpacity(1.0);
	 
		if (this->icon().isNull())
		{
			painter.drawText(0, 0, button_rect.width(), button_rect.height(), Qt::AlignCenter, text);
		}
		else
		{
			painter.drawText(button_rect.height() + OFFSET , 0, button_rect.width() - button_rect.height() - OFFSET * 2, button_rect.height(), Qt::AlignLeft | Qt::AlignVCenter, text);
		}
    }*/

    //icon
  //  QIcon icon = this->icon();
  //  if(!icon.isNull())
  //  { 
		////QPixmap pixmap = icon.pixmap.scaled(this->height() - 6, this->height() - 6, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
		//
		//int length = this->height() > this->width() ? this->width() : this->height();

		//QSize icon_size = QSize(length - 2 * OFFSET, length - 2 * OFFSET);// this->iconSize();
		//QRect icon_position = this->calculateIconPosition(button_rect, icon_size);
		//painter.setOpacity(1.0);
		//painter.drawPixmap(icon_position, QPixmap(icon.pixmap(QSize(length - 6, length - 6))));// icon_size)));
  //  } 
}

void AeroButton::enterEvent(QEvent * e)
{
	m_hovered = true;
	this->repaint();

	QWidget::enterEvent(e);
}

void AeroButton::leaveEvent(QEvent * e)
{
	m_hovered = false;
	this->repaint();

	QWidget::leaveEvent(e);
}

int AeroButton::findGroup(AeroButton *button)
{
	QMap<int, QList<AeroButton*>>::iterator it;

	for (it = buttonList.begin(); it != buttonList.end(); ++it)
		if (it.value().contains(button))
			return it.key();

	return -1;
}

void AeroButton::mousePressEvent(QMouseEvent * e)
{
	int groupid = findGroup(this);

	if (!activeGroup.contains(groupid))
	{  
		activeGroup[groupid] = this;
		m_pressed = true;// !m_pressed;// true;
		this->repaint();
	} 
	else
	{ 
		if (activeGroup[groupid] != this)
		{  
			activeGroup[groupid]->setPressed(false);
			activeGroup[groupid] = this;
			m_pressed = true;// !m_pressed;// true;
			this->repaint();
		}
	}  

	QPushButton::mousePressEvent(e);
}

void AeroButton::mouseReleaseEvent(QMouseEvent * e)
{
	//m_pressed = false;
	this->repaint();

	QPushButton::mouseReleaseEvent(e);
}

QRect AeroButton::calculateTextPosition(QRect button_rect, int offset)
{
	switch (m_icon_position)
	{
	case IP_LEFT:
		break;
	case IP_CENTER:
		break;
	case IP_RIGHT:
		break;
	case IP_BOTTOM:
		break;
	}

	return QRect();
}

QRect AeroButton::calculateIconPosition(QRect button_rect, QSize icon_size)
{
	int x = 0;
	int y = 0;
	int height = 0;
	int width = 0;

	switch (m_icon_position)
	{
	case IP_LEFT:
	{
		double margin = (button_rect.height() - icon_size.height()) / 2.0;
		x =  margin;
		y =  margin;
	}
		break;
	case IP_RIGHT:
	{
		x = (button_rect.width() - icon_size.width());
		y = (button_rect.height() - icon_size.height());
	}
		break;
	case IP_TOP:
	{
		x = (button_rect.width() - icon_size.width()) / 2.0;
		y = (button_rect.height() - icon_size.height()) / 2.0;
	}
		break;
	case IP_BOTTOM:
	{
		x = (button_rect.width() - icon_size.width()) / 2.0;
		y = (button_rect.height() - icon_size.height());
	}
		break;
	case IP_CENTER:
	{
		x = (button_rect.width() - icon_size.width()) / 2;
		y = (button_rect.height() - icon_size.height()) / 2;
	}
		break;
	default:
		break;
	} 
	
	width = icon_size.width();
	height = icon_size.height();

	QRect icon_position;
	icon_position.setX(x);
	icon_position.setY(y);
	icon_position.setWidth(width);
	icon_position.setHeight(height);

	return icon_position;
} 
