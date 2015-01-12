#include "StoreItemWidget.h"
#include "RoundButton.h"

StoreItemWidget::StoreItemWidget(int w, int h, QString photo_path,QString text, const QColor &glowColor, QWidget *parent)
	:QWidget(parent)
{
	setMouseEnterFlag(false);
	setMousePressFlag(false);
	setTransition(true);
	setIsBackgroundTransparent(true);
	setColor(QColor(255, 255, 255));

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));
	this->setPalette(palette);
	//this->setAutoFillBackground(true);

	m_icon = new QLabel(); 
	m_title = new QLabel();
	m_title->setText(text);
	m_title->setGraphicsEffect(ConfigInstance().generateGlowEffect(glowColor, 8));
	 
	//m_title->setFixedSize(this->size());

	QPixmap pixmap(photo_path);
	pixmap = pixmap.scaled(h*3/4, h, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
	resize(pixmap.size());
	
	m_icon->setPixmap(pixmap);

	this->setFixedSize(w+20, h+20);

	RoundButton *activateButton = new RoundButton(60, 20);
	activateButton->setText("安装");

	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->addWidget(m_title);
	right_layout->addStretch();
	QHBoxLayout *right_bottom_layout = new QHBoxLayout();
	right_bottom_layout->addStretch();
	right_bottom_layout->addWidget(activateButton, 0, Qt::AlignRight);

	right_layout->addLayout(right_bottom_layout);

	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->addWidget(m_icon);
	main_layout->addSpacing(10);
	//main_layout->addLayout(right_layout);
	setLayout(main_layout);
}

StoreItemWidget::~StoreItemWidget()
{

}


void StoreItemWidget::setTitle(QString text)
{
	m_title->setText(text);
	this->update();
}


void StoreItemWidget::setPixmap(const QPixmap &pixmap)
{
	m_icon->setPixmap(pixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void StoreItemWidget::setTextColor(const QColor &color)
{
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::WindowText, color);
	m_title->setPalette(text_palette);
	//m_title->setStyleSheet(QString("QLabel{color:white;border-radius}"));// rgb(% 1, % 2, % 3); ").arg(color.red(), color.green(), color.blue()).toStdString().c_str());
	this->update();
}

void StoreItemWidget::setColor(const QColor &color)
{
	m_color = color;
	this->update();
}

void StoreItemWidget::setFont(QFont &font)
{
	m_title->setFont(font);
}

void StoreItemWidget::setMouseEnterFlag(bool flag)
{
	m_mouseEnterFlag = flag;
	this->update();
}

void StoreItemWidget::setMousePressFlag(bool flag)
{
	m_mousePressFlag = flag;
	this->update();
}

void StoreItemWidget::setIsBackgroundTransparent(bool bIsTransparent)
{
	m_bIsBkgTransparent = bIsTransparent;
	this->update();
}

void StoreItemWidget::setTransition(bool bEnabled)
{
	m_bEnableTransition = bEnabled;
	this->update();
}

void StoreItemWidget::enterEvent(QEvent *)
{
	if (!getMousePressFlag())
		setMouseEnterFlag(true);
	this->setCursor(Qt::PointingHandCursor);
}

void StoreItemWidget::leaveEvent(QEvent *)
{
	setMouseEnterFlag(false);
}

void StoreItemWidget::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		setMousePressFlag(true);
		emit signalLabelPress(this);
	}
}

void StoreItemWidget::paintEvent(QPaintEvent *e)
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
			paintWidget(150, &painter, 0);
		}
		else
		{
			paintWidget(180, &painter, 3);
		}

		//paintWidget(200, &painter);
	}
	else
	{
		if (!m_bIsBkgTransparent)
		{
			paintWidget(50, &painter, 0);
		}
		//paintWidget(20, &painter);
	}
	QWidget::paintEvent(e);
}

//void StoreItemWidget::createFrame()
//{
//	this->setStyleSheet("QWidget {background:transparent;border:0px;color:black;}");
//}  

void StoreItemWidget::paintWidget(int transparency, QPainter *device, int roundRadius)
{
	QPen pen(Qt::NoBrush, 1);
	device->setPen(pen);
	device->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);

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
		device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
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

inline bool StoreItemWidget::getMouseEnterFlag()
{
	return m_mouseEnterFlag;
}

inline bool StoreItemWidget::getMousePressFlag()
{
	return m_mousePressFlag;
}


void StoreItemWidget::painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color)
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
	painter.drawRoundedRect(rect(), 5, 5);// .drawRect(rect());
}
