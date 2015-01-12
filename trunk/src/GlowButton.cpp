#include "GlowButton.h"
#include "IconWidget.h"

QMap<int, QList<GlowButton*>> GlowButton::buttonList = QMap<int, QList<GlowButton*>>();

QMap<int, GlowButton*> GlowButton::activeGroup = QMap<int, GlowButton*>();

GlowButton::GlowButton(int w,int h, bool isExtraMode,
	QString photo_path,QString text,
	const QColor &bkcolor, const QColor &glowColor,QWidget *parent)
	:QWidget(parent)
{ 
	m_title = new QLabel();
	m_title->setText(text);

	m_bCheckMode = false;

	setBackColor(bkcolor);
	setGlowColor(glowColor);
	setMouseEnterFlag(false);
	setMousePressFlag(false);
	setTransition(true);
	setIsBackgroundTransparent(true); 
	setIsExtraEnabled(isExtraMode); 
	setMode(eGlowButtonMode::GBM_BACKGROUND);

	if (photo_path.size() > 0)
	{
		m_icon = new QLabel();
		QPixmap pixmap = QPixmap(photo_path);
		pixmap = pixmap.scaled(30, 30, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);

		m_icon->setPixmap(pixmap);
	}
	else
	{
		m_icon = NULL;
	} 
	
	this->setFixedSize(w, h);
	 
	QGridLayout *right_layout = new QGridLayout(); 
	right_layout->addWidget(m_title, 0, 0, Qt::AlignCenter);
	right_layout->addWidget(new QWidget(), 1, 0, Qt::AlignCenter);
 
	if (m_icon == NULL)
	{
		setLayout(right_layout);
	}
	else
	{
		QGridLayout *grid_layout = new QGridLayout();
		grid_layout->addLayout(right_layout, 0, 1, Qt::AlignLeft);
		grid_layout->addWidget(m_icon, 0, 0, Qt::AlignCenter);

		QHBoxLayout *main_layout = new QHBoxLayout();
		main_layout->addLayout(grid_layout);
		if (m_showExtraIcon)
			main_layout->addWidget(new IconWidget(16, 16, "", QColor(24, 116, 205), QColor(0, 0, 0), QColor(255, 0, 0)));
		else
			main_layout->addSpacing(20); 

		setLayout(main_layout);
	}
}

GlowButton::~GlowButton() 
{

} 

int GlowButton::findGroup(GlowButton *button)
{
	QMap<int, QList<GlowButton*>>::iterator it;

	for (it = buttonList.begin(); it != buttonList.end(); ++it)
		if (it.value().contains(button))
			return it.key();

	return -1;
}

void GlowButton::setGroupId(int id)
{
	if (m_bCheckMode == false)
		m_bCheckMode = true;

	if (!buttonList.contains(id))
		buttonList[id] = QList<GlowButton*>();
	buttonList[id].append(this);
}

void GlowButton::setMode(eGlowButtonMode mode)
{
	m_mode = mode;
}

void GlowButton::setIsExtraEnabled(bool enable)
{
	m_showExtraIcon = enable;
}

void GlowButton::setTitle(QString text)
{
	m_title->setText(text);
	this->update();
}  

void GlowButton::setPixmap(const QPixmap &pixmap)
{
	m_icon->setPixmap(pixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void GlowButton::setTextColor(const QColor &color)
{
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::WindowText,color);
	m_title->setPalette(text_palette);
	this->update();
}

void GlowButton::setGlowColor(const QColor &color)
{
	m_color = color;
	m_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(color, 5)); 
	this->update();
}

void GlowButton::setBackColor(const QColor &color)
{
	m_backColor = color;
	this->update();
}

void GlowButton::setFont(QFont &font)
{
	m_title->setFont(font);
}  

void GlowButton::setMouseEnterFlag(bool flag)
{
	m_mouseEnterFlag = flag;
	if (m_bCheckMode == false)
	{
		if(flag)
			m_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::red, 5));
		else 
			m_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(m_color, 5));
	}

	this->update();
}

void GlowButton::setMousePressFlag(bool flag)
{
	m_mousePressFlag = flag;
	
	if (flag)
		m_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::red, 5));
	else
		m_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(m_color, 5));
	 
	this->update();
}

void GlowButton::setIsBackgroundTransparent(bool bIsTransparent)
{
	m_bIsBkgTransparent = bIsTransparent;
	this->update();
}

void GlowButton::setTransition(bool bEnabled)
{
	m_bEnableTransition = bEnabled;
	this->update();
}

void GlowButton::enterEvent(QEvent *)
{
	if (!getMousePressFlag())
		setMouseEnterFlag(true);

	this->setCursor(Qt::PointingHandCursor);
}

void GlowButton::mouseReleaseEvent(QMouseEvent *)
{

}

void GlowButton::leaveEvent(QEvent *)
{
	setMouseEnterFlag(false);
}

void GlowButton::setPressed(bool is_pressed)
{ 
	setMousePressFlag(is_pressed); 
	this->update();
}

void GlowButton::check()
{ 
	int groupid = findGroup(this);

	if (!activeGroup.contains(groupid))
	{
		activeGroup[groupid] = this;
		setMousePressFlag(true);
		this->repaint();
		emit glowButtonClicked(this);
	}
	else
	{
		if (activeGroup[groupid] != this)
		{
			activeGroup[groupid]->setPressed(false);
			activeGroup[groupid] = this;
			setMousePressFlag(true);
			this->repaint();
			emit glowButtonClicked(this);
		}
	} 
}

void GlowButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_bCheckMode == true)
		{
			check();
		}
		else
		{
			setMousePressFlag(true);
			emit glowButtonClicked(this);
		}
	}
}

void GlowButton::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	if (m_mode == eGlowButtonMode::GBM_NOBACKGROUND)
	{
		return;
	}

	//»æÖÆ±³¾°
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
			paintWidget(255, &painter, 0);
		}
		else
		{
			paintWidget(180, &painter, 3);
		} 
	}
	else
	{
		if (!m_bIsBkgTransparent)
		{
			paintWidget(50, &painter, 0);
		} 
	}

	QWidget::paintEvent(e);
} 
void GlowButton::paintWidget(int transparency, QPainter *device, int roundRadius)
{
	QPen pen(Qt::NoPen); 
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
		linear.setColorAt(0, QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), transparency));
		linear.setColorAt(1, QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 0));
		QBrush brush(linear);
		device->setBrush(brush);
		device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
	}
	else if (!m_bIsBkgTransparent)
	{
		/*if (roundRadius == 0)
		{
			QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
			linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), 30));
			linear.setColorAt(0.5, QColor(m_color.red(), m_color.green(), m_color.blue(), 100));
			linear.setColorAt(1, QColor(m_color.red(), m_color.green(), m_color.blue(), 10));
			QBrush brush(linear);
			device->setBrush(brush);
			device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
		}
		else
		{*/
			QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
			linear.setColorAt(0, QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), transparency));
			QBrush brush(linear);
			device->setBrush(brush);
			device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
		//}
	}
	else
	{
		QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
		linear.setColorAt(0, QColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), transparency));
		QBrush brush(linear);
		device->setBrush(brush);
		device->drawRoundedRect(this->rect(), roundRadius, roundRadius);
	}
}

inline bool GlowButton::getMouseEnterFlag()
{
	return m_mouseEnterFlag;
}

inline bool GlowButton::getMousePressFlag()
{
	return m_mousePressFlag;
}
