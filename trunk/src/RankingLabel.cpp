#include "RankingLabel.h"

RankingLabel::RankingLabel(int w,int h,int picLen,QString iconPath, QString title, QString type, QString price, QWidget *parent)
{
	main_layout = new QHBoxLayout();
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setMargin(0);

	QPalette palette;
	palette.setBrush(QPalette::WindowText, QBrush(Qt::white));
	//this->setPalette(palette);
	//this->setAutoFillBackground(true);

	m_icon = new QLabel();
	m_title = new QLabel();
	m_type = new QLabel();
	m_price = new QLabel();

	int min_len = w > h ? h : w;

	this->setMinimumSize(w, h);

	QPixmap pixmap(iconPath);
	QPixmap transformed_pxmap = pixmap.scaled(picLen, h , Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	m_icon->setPixmap(transformed_pxmap);

	auto font = ProfileInstance().AppFont;
	font.setPixelSize(20);

	setColor(QColor(24, 116, 205));

	m_title->setText(title);
	m_title->setFont(font);
	m_title->setPalette(palette);

	//m_title->setGraphicsEffect(Profile::generateGlowEffect(QColor(255,255,255), 5));

	m_type->setText(type);
	m_type->setFont(ProfileInstance().AppFont);
	m_type->setPalette(palette);

	m_price->setText(price);
	m_price->setFont(ProfileInstance().AppFont);
	m_price->setPalette(palette);

	main_layout->addWidget(m_icon);

	QVBoxLayout *mid_layout = new QVBoxLayout();
	mid_layout->addWidget(m_title);
	mid_layout->addWidget(m_type);  

	main_layout->addLayout(mid_layout);
	main_layout->addStretch();
	main_layout->addWidget(m_price,0,Qt::AlignCenter);
	main_layout->addStretch();
	setLayout(main_layout);

	m_MouseOver = false;
	m_MousePress = false;

	this->update(); 
}

RankingLabel::~RankingLabel()
{
	delete main_layout;
}

void RankingLabel::setRating(int rating)
{
	
}


void RankingLabel::enterEvent(QEvent *)
{
	m_MouseOver = true;
	this->update();
}

void RankingLabel::leaveEvent(QEvent *)
{
	m_MouseOver =false;
	setMousePress(false);
}

void RankingLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		setMousePress(true); 
		emit clicked();
	}
}

void RankingLabel::mouseReleaseEvent(QMouseEvent *)
{
	setMousePress(false);
}

void RankingLabel::setMousePress(bool mouse_press)
{
	this->m_MousePress = mouse_press;
	update();
}

void RankingLabel::paintEvent(QPaintEvent *event)
{ 
	if (m_MousePress)
		painterInfo(180, 180, 180);
	else if (m_MouseOver)
		painterInfo(200, 190, 200);
	else 
		painterInfo(200, 190, 200);

	//QWidget::paintEvent(event);
}

void RankingLabel::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	 
	if (m_MousePress)
		painter.setPen(QPen(Qt::red, 0.1));
	else if (m_MouseOver)
		painter.setPen(QPen(Qt::darkBlue, 0.1));
	else
		painter.setPen(Qt::NoPen);

	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(m_color.red(), m_color.green(), m_color.blue(), top_color));
	linear.setColorAt(0.5, QColor(m_color.red(), m_color.green(), m_color.blue(), middle_color));
	linear.setColorAt(1, QColor(m_color.red(), m_color.green(), m_color.blue(), bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect()); //drawRoundedRect(rect(), 5, 5);// 
}
