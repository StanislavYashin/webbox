#include "SecondaryDetailWidget.h"

#include "AppletWidget.h"
#include "GlowEffect.h"
#include <QtWidgets>
#include "RoundButton.h"
#include "IconWidget.h"
#include "CarouselWidget.h"
#include <string>

SecondaryDetailWidget::SecondaryDetailWidget(int w, int h, bool isGlow, QString pic_name, QString title, QWidget *parent)
	:QWidget(parent)
{ 
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true);
	 
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setBold(true); 

	setObjectName("SndWidget");
	setStyleSheet("QWidget#SndWidget{background:transparent;}");
 
	QPixmap pixmap(pic_name);
	auto pic_w = pixmap.width();
	auto pic_h = pixmap.height();

	double ratio = pic_w * 1. / pic_h;

	double pic_transformed_w = 140  ;
	double pic_transformed_h = 140 / ratio;

	pixmap = pixmap.scaled(pic_transformed_w, pic_transformed_h, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
	 
	m_icon = pixmap;
	 
	setFont(ProfileInstance().AppFont);
	
	m_MouseOver = false;
	m_MousePress = false;

	QLabel *widget = new QLabel();
	widget->setPixmap(pixmap);

	QFont font = QFont("Microsoft Yahei");
	font.setPixelSize(20);
	//font.setBold(true);

	QLabel *lb_title = new QLabel();
	lb_title->setText(title);
	lb_title->setFont(font); 

	QLabel *lb_icon = new QLabel();
	lb_icon->setPixmap(m_icon);
	lb_icon->setFixedSize(pic_transformed_w, pic_transformed_h);

	if (isGlow)
		lb_title->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::white, 5));
	 
	//IconWidget *closeButton = new IconWidget(16, 16, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/icon/UI/close.png", QColor(24, 116, 205), QColor(0, 0, 0), QColor(255, 0, 0));
	
	RoundButton *installButton = new RoundButton(60, 20); 
	installButton->setText(QString::fromWCharArray(L"安装"));

	//图标
	QGridLayout *topLayout = new QGridLayout();
	topLayout->setContentsMargins(20, 20, 20, 20);
	topLayout->setSpacing(30);

	 
	__topMidLayout = new QVBoxLayout();
	__topMidLayout->setSpacing(5);
	__topMidLayout->setContentsMargins(0, 0, 0, 0);
	__topMidLayout->addWidget(lb_title);
	__topMidLayout->addSpacing(10);
	//__topMidLayout->addStretch();

	topLayout->addLayout(__topMidLayout, 0, 1);
	topLayout->addWidget(lb_icon, 0, 0); 
	
	QVBoxLayout *bottom_right_layout = new QVBoxLayout();
	bottom_right_layout->addStretch();
	bottom_right_layout->addWidget(installButton, 0, Qt::AlignRight);
  
	QVBoxLayout *top_right_layout = new QVBoxLayout();
	//top_right_layout->addWidget(closeButton);
	top_right_layout->addStretch();
	
	//topLayout->addStretch();
	topLayout->addLayout(bottom_right_layout,0,2);
	//topLayout->addLayout(,0,3);
 
	QHBoxLayout *grid_layout = new QHBoxLayout();
	
	grid_layout->addLayout(topLayout);
	grid_layout->addStretch();
	grid_layout->addLayout(top_right_layout);
	
	CarouselWidget *carousel_widget = new CarouselWidget(730, 400, 4, 4, 500); 

	QVBoxLayout *main_layout = new QVBoxLayout(); 
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setMargin(0);
	main_layout->setSpacing(0);
	main_layout->addLayout(grid_layout); 
	main_layout->addSpacing(30);
	main_layout->addWidget(carousel_widget);
	main_layout->addStretch();
	setLayout(main_layout);
}

SecondaryDetailWidget::~SecondaryDetailWidget()
{

}

void SecondaryDetailWidget::setGameInfo(const DetailGameInfo &info)
{
	__info = info;
	 
	QLabel* title_zh =  new QLabel(QString::fromWCharArray(L"中文：") + info.title_zh); title_zh->setFont(ProfileInstance().AppFont);
	QLabel* title_en = new QLabel(QString::fromWCharArray(L"英文：") + info.title_en); title_en->setFont(ProfileInstance().AppFont);
	QLabel* publisher = new QLabel(QString::fromWCharArray(L"发行：") + info.publisher); publisher->setFont(ProfileInstance().AppFont);
	QLabel* platform = new QLabel(QString::fromWCharArray(L"平台：") + info.platform); platform->setFont(ProfileInstance().AppFont);
	QLabel* rating = new QLabel(QString::fromWCharArray(L"分级：") + info.rating); rating->setFont(ProfileInstance().AppFont);
	QLabel* type = new QLabel(QString::fromWCharArray(L"类型：") + info.type); type->setFont(ProfileInstance().AppFont);
	QLabel* date = new QLabel(QString::fromWCharArray(L"日期：") + info.date); date->setFont(ProfileInstance().AppFont);
	 
	__topMidLayout->addWidget(title_zh);
	__topMidLayout->addWidget(title_en);
	__topMidLayout->addWidget(publisher);
	__topMidLayout->addWidget(platform);
	__topMidLayout->addWidget(rating);
	__topMidLayout->addWidget(type);
	__topMidLayout->addWidget(date);
	__topMidLayout->addStretch();
}

void SecondaryDetailWidget::enterEvent(QEvent *)
{
	m_MouseOver = true;
}

void SecondaryDetailWidget::leaveEvent(QEvent *)
{
	m_MouseOver = false;
	setMousePress(false);
}

void SecondaryDetailWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = true;
		repaint(); 
	}
}

void SecondaryDetailWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_MousePress = false;
		repaint();
	}
}

void SecondaryDetailWidget::setMousePress(bool mouse_press)
{
	this->m_MousePress = mouse_press;
	update();
}

void SecondaryDetailWidget::paintEvent(QPaintEvent *event)
{ 
	QWidget::paintEvent(event);
	painterInfo(24, 116, 205, 0, 20, 255);
}

void SecondaryDetailWidget::painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 0);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(r, g, b, top_color));
	linear.setColorAt(0.5, QColor(r, g, b, middle_color));
	linear.setColorAt(1, QColor(r, g, b, bottom_color));
	painter.setBrush(linear);
	painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
	painter.drawRoundedRect(rect(), 5, 5);   //.drawRect(rect());
}
