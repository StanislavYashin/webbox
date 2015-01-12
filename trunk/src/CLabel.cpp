#include "clabel.h"
#include "Config.h"

CLabel::CLabel(QWidget *parent) :
QWidget(parent)
{
	initVariable();
	initSetupUi();
}

CLabel::~CLabel()
{
	delete m_pLabelIcon;
	delete m_pLabelText;
	delete m_pHLayout;
}

void CLabel::setColor(const QColor &color)
{
	m_color = color;
	this->update();
}

void CLabel::setFont(QFont &font)
{
	m_pLabelText->setFont(font);
}

void CLabel::setPixmap(const QPixmap &pixmap)
{
	m_pLabelIcon->setPixmap(pixmap.scaled(QSize(55, 55), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CLabel::setTextColor(const QColor &color)
{    
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::WindowText, color);
	m_pLabelText->setPalette(text_palette);

	this->update();
}

void CLabel::setText(const QString &text)
{
	m_pLabelText->setText(text);
}

void CLabel::setMouseEnterFlag(bool flag)
{
	m_mouseEnterFlag = flag;
	this->update();
}

void CLabel::setMousePressFlag(bool flag)
{
	m_mousePressFlag = flag;
	this->update();
}

void CLabel::setIsBackgroundTransparent(bool bIsTransparent)
{
	m_bIsBkgTransparent = bIsTransparent;
	this->update();
}

void CLabel::setTransition(bool bEnabled)
{
	m_bEnableTransition = bEnabled;
	this->update();
}

void CLabel::enterEvent(QEvent *)
{
	if (!getMousePressFlag())
		setMouseEnterFlag(true);
	this->setCursor(Qt::PointingHandCursor);
}

void CLabel::leaveEvent(QEvent *)
{
	setMouseEnterFlag(false);
}

void CLabel::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		setMousePressFlag(true);
		emit signalLabelPress(this);
	}
}

void CLabel::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	if (getMouseEnterFlag())
	{ 
		if (m_bEnableTransition)
		{
			paintWidget(100, &painter, 0);
		}
		else
		{
			paintWidget(100, &painter, 3);
		} 
	}
	else if (getMousePressFlag())
	{
		if (m_bEnableTransition)
		{
			paintWidget(150, &painter,0);
		}
		else
		{
			paintWidget(180, &painter,3);
		}
		
		//paintWidget(200, &painter);
	}
	else
	{
		if (!m_bIsBkgTransparent)
		{
			paintWidget(50, &painter,0);
		}
		//paintWidget(20, &painter);
	}
	QWidget::paintEvent(e);
}

void CLabel::initVariable()
{
	setMouseEnterFlag(false);
	setMousePressFlag(false);
	setTransition(true);
	setIsBackgroundTransparent(true);
	setColor(QColor(255, 255, 255));
}

void CLabel::initSetupUi()
{
	createFrame();
	createWidget();
	createLayout();
}

void CLabel::createFrame()
{
	this->setStyleSheet("QWidget {background:transparent;border:0px;color:blue;}");
}

void CLabel::createWidget()
{
	m_pLabelIcon = new QLabel(); 
	m_pLabelText = new QLabel(); 
}

void CLabel::createLayout()
{
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));
	this->setPalette(palette);

	m_pLabelText->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::white, 5));

	m_pHLayout = new QHBoxLayout;
	//m_pHLayout->setSpacing(10);
	m_pHLayout->setContentsMargins(QMargins(0, 0, 5, 0));
	m_pHLayout->addWidget(m_pLabelIcon); 
	m_pHLayout->addStretch();

	QGridLayout *main_layout = new QGridLayout();
	main_layout->addWidget(m_pLabelText, 0, 1, Qt::AlignLeft);
	main_layout->addWidget(m_pLabelIcon, 0, 0, Qt::AlignLeft);
	setLayout(main_layout);

	this->setLayout(m_pHLayout);
}

void CLabel::paintWidget(int transparency, QPainter *device, int roundRadius)
{
	QPen pen(Qt::NoBrush, 1);
	device->setPen(pen);

	//QLinearGradient linear(this->rect().topLeft(), this->rect().topRight()); 
	//linear.setColorAt(0, QColor(24, 116, 205, transparency));  
	//linear.setColorAt(1, QColor(24, 116, 205, transparency/20));
	//linear.setColorAt(0, QColor(38, 184, 222, transparency)); 
	//linear.setColorAt(1, QColor(38, 184, 222,  transparency / 20));
	//linear.setColorAt(0, QColor(100, 149, 237, transparency));
	//linear.setColorAt(1, QColor(100, 149, 237, transparency / 20));
	//linear.setColorAt(0, QColor(96, 123, 139, transparency));
	//linear.setColorAt(1, QColor(96, 123, 139, 0));// transparency / 20));

	if (m_bEnableTransition)
	{
		QLinearGradient linear(this->rect().topLeft(), this->rect().topRight());
		linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), transparency));
		linear.setColorAt(1, QColor(m_color.red(), m_color.green(), m_color.blue(), 0));
		QBrush brush(linear);
		device->setBrush(brush);
		device->drawRoundedRect(this->rect(),roundRadius,roundRadius);
	}
	else if (!m_bIsBkgTransparent)
	{
		QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
		
		if (roundRadius == 0)
		{
			linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), 10));
			linear.setColorAt(0.5, QColor(m_color.red(), m_color.green(), m_color.blue(), 20));
			linear.setColorAt(1, QColor(m_color.red(), m_color.green(), m_color.blue(), 10));
			QBrush brush(linear);
			device->setBrush(brush);
			device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
		}
		else
		{
			QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
			linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), transparency));
			QBrush brush(linear);
			device->setBrush(brush);
			device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
		}
	} 
	else
	{
		QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
		linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), transparency));
		QBrush brush(linear);
		device->setBrush(brush);
		device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
	}
}

inline bool CLabel::getMouseEnterFlag()
{
	return m_mouseEnterFlag;
}

inline bool CLabel::getMousePressFlag()
{
	return m_mousePressFlag;
}
