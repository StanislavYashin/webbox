#include "MusicWidget.h"
#include "GlowEffect.h"
#include "Config.h"

MusicWidget::MusicWidget(QWidget *parent) :
	QWidget(parent)
{
	QLabel *m_Title = new QLabel();
	m_Title->setText("@music");

	//m_Title->setObjectName("whiteLabel");
	//m_Title->setMaximumWidth(200);
	//m_Title->setMaximumHeight(60);
	//m_Title->setMargin(10);

	/*GlowEffect *effect = new GlowEffect();
	effect->setRadius(2);
	effect->setGlowColor(Qt::blue);
	*/

	m_Title->setGraphicsEffect(ProfileInstance().generateGlowEffect(Qt::blue,5));

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 220)));// Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true);

	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->addWidget(m_Title);
	this->setLayout(main_layout);
}
