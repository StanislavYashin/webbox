#include "AppletWidget.h"
#include "GlowEffect.h"
#include <QtWidgets>
#include "RoundButton.h"

AppletWidget::AppletWidget(int w, int h, bool isGlow, Webbox::Data::CommonProperty *itemProperty, QWidget *parent)
	:QToolButton(parent)
{
	//m_visible = true;

	//设置文本颜色
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));
	this->setPalette(palette);
 
	//设置文本粗体
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setWeight(QFont::Bold);

	//setText(title);

	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	 
	setObjectName("AppletWidget");
	setStyleSheet("QToolButton#AppletWidget{background:transparent;}");
	 
	int picWidth = h * 5 / 7;
	int picHeight = h;

	//设置图标
	QPixmap pixmap;
	pixmap.loadFromData(itemProperty->getIcon());

	pixmap = pixmap.scaled(picWidth, picHeight, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
	//setIcon(pixmap);
	setAutoRaise(true);
	setIconSize(pixmap.size());
	resize(pixmap.size());
	//设置大小

	m_icon = pixmap;

	setFixedSize(w + 30, h + 25);

	setFont(ProfileInstance().AppFont);

	//setObjectName("transparentToolButton");
	
	m_MouseOver = false;
	m_MousePress = false;
	
	iconLabel = new QLabel(); 
	iconLabel->setPixmap(pixmap);


	lb_title = new QLabel(); 
	lb_title->setText(itemProperty->getNameCN());
	lb_title->setFont(text_font); 
	 
	if(isGlow)
		lb_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::blue, 5));
	
	QLabel *lb_title2 = new QLabel();
	lb_title2->setText(itemProperty->getNameEn());
	lb_title2->setFont(text_font);

	RoundButton *installButton = new RoundButton(60,20);
	installButton->setText("安装");
	  
	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->addWidget(lb_title);
	right_layout->addStretch();

	QHBoxLayout *right_bottom_layout = new QHBoxLayout();
	right_bottom_layout->addStretch();
	right_bottom_layout->addWidget(installButton, 0, Qt::AlignRight);

	right_layout->addLayout(right_bottom_layout);

	QGridLayout *main_layout = new QGridLayout(); 
	main_layout->addLayout(right_layout,0,1,Qt::AlignCenter); 
	main_layout->addWidget(iconLabel, 0, 0, Qt::AlignLeft);
	setLayout(main_layout); 

	//connect(this,SIGNAL(clicked),this,SLOT(OnClicked()));
}

AppletWidget::~AppletWidget()
{

}

void AppletWidget::setProperty(Webbox::Data::CommonProperty * itemProperty)
{
	int picWidth = this->height() * 5 / 7;
	int picHeight = this->height();

	QPixmap pixmap;
	pixmap.loadFromData(itemProperty->getIcon()); 
	pixmap = pixmap.scaled(picWidth, picHeight, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
	
	iconLabel->setPixmap(pixmap);

	lb_title->setText(itemProperty->getNameCN()); 

	this->update();
}

void AppletWidget::enterEvent(QEvent *)
{
	m_MouseOver = true;
}

void AppletWidget::leaveEvent(QEvent *)
{
	m_MouseOver = false;
	setMousePress(false);
}

void AppletWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = true;
		repaint();
		emit labelPress();
	}
}

void AppletWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = false;
		repaint(); 
	}
}

void AppletWidget::setMousePress(bool mouse_press)
{
	this->m_MousePress = mouse_press;
	update();
}

void AppletWidget::paintEvent(QPaintEvent *event)
{
	QToolButton::paintEvent(event);

	if (m_MousePress)
	{
		//painterInfo(255, 130, 71, 100, 150, 200);
		painterInfo(0,230,230,100, 150, 200);
	}
	else
	{
		if (m_MouseOver)
		{
			//绘制鼠标移到按钮上的按钮效果
			//painterInfo(0, 230, 230, 100, 100, 100);
			//painterInfo(255, 130, 71, 255, 255, 255);  
			painterInfo(255, 255, 255, 255, 255, 255);
		}
		else
		{
			//painterInfo(224, 224, 224, 255, 255, 255);
			//painterInfo(255, 130, 71, 255, 255, 255);
			painterInfo(255, 255, 255, 140, 140, 140);
		}
	}  

	//QPainter painter(this);
	//painter.drawPixmap(this->rect(),m_icon);

	//QStyleOption opt;
	//opt.init(this);
	//QPainter p(this);
	//style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this); 
}

void AppletWidget::painterInfo(int r,int g,int b,int top_color, int middle_color, int bottom_color)
{ 
	/*if (m_visible == false)
		return;*/

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