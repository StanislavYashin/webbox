#include "ExploreWidget.h"
#include "GlowEffect.h"

ExploreWidget::ExploreWidget(QWidget *parent) :
	QWidget(parent)
{
	QLabel *m_Title = new QLabel();
	m_Title->setText("@explore");
	//m_Title->setObjectName("whiteLabel");
	//m_Title->setMaximumWidth(200);
	//m_Title->setMaximumHeight(60);
	//m_Title->setMargin(10);

	/*GlowEffect *effect = new GlowEffect();
	effect->setRadius(2);
	effect->setGlowColor(Qt::blue);
	m_Title->setGraphicsEffect(effect);*/

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 220)));// Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true); 

	QLineEdit *line_edit = new QLineEdit();
	line_edit->setFont(QFont("Microsoft Yahei", 10));
	line_edit->setPlaceholderText("搜索商店");
	QPalette palette_line_edit;
	palette_line_edit.setBrush(QPalette::Text, QBrush(QColor(24, 116, 205, 220)));
	line_edit->setPalette(palette_line_edit);
	line_edit->setAlignment(Qt::AlignCenter);
	line_edit->setContentsMargins(20, 20, 0, 20);
	line_edit->setTextMargins(0, 5, 0, 5);
	line_edit->setFixedWidth(230);
	line_edit->setObjectName("SearchBox");
	line_edit->setStyleSheet("QWidget#SearchBox{background:transparent; border-radius: 3px;}");

	//line_edit->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::blue, 8)); 
	 

	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->addStretch();
	main_layout->addWidget(line_edit);
	main_layout->addStretch();
	this->setLayout(main_layout);
}
