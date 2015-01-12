#include "TitleWidget.h"

TitleWidget::TitleWidget(QWidget *parent)
	: BaseStyleWidget(parent)
{ 
	setObjectName("TitleWidget");
	 
	QLabel *logo = new QLabel();  
	 
	QPixmap pixmap(Webbox::Utility::PathUtil::GetCurrentExePath() + "/Skin/img/logo_normal.png");
	QString cssText = QString("QLabel:!hover:!pressed{border-image:url(%1/Skin/img/logo_normal.png);} QLabel:hover{border-image:url(%2/Skin/img/logo_glow.png);}").arg(
		Webbox::Utility::PathUtil::GetCurrentExePath(), Webbox::Utility::PathUtil::GetCurrentExePath());

	logo->setStyleSheet(cssText);
	logo->setContentsMargins(0, 0, 0, 0);

	int pix_w = pixmap.width();
	int pix_h = pixmap.height(); 

	const double desire_height = 60;

	logo->setMinimumSize(desire_height*pix_w / pix_h, desire_height);

	QVBoxLayout *header = new QVBoxLayout();

	header->addSpacing(5);

	QGridLayout *grid_layout = new QGridLayout();
	grid_layout->setContentsMargins(0, 0, 0, 0);
	grid_layout->setSpacing(0); 
	grid_layout->setAlignment(Qt::AlignLeft);

	grid_layout->addWidget(logo, 0,0, Qt::AlignVCenter | Qt::AlignLeft);
 
	QSignalMapper *signal_mapper = new QSignalMapper(this);
 
	m_aerobtn_list.append(createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/Icon/UI/MB_0014_iTunes.png", QString::fromWCharArray(L"启动")));
	m_aerobtn_list.append(createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"软件")));
	m_aerobtn_list.append(createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/Icon/UI/game.png", QString::fromWCharArray(L"游戏")));
	m_aerobtn_list.append(createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"探索")));
	m_aerobtn_list.append(createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"帐户")));

	for (int i = 0; i < m_aerobtn_list.count(); ++i)
	{
		connect(m_aerobtn_list[i], SIGNAL(clicked()), signal_mapper, SLOT(map()));
		signal_mapper->setMapping(m_aerobtn_list[i], i);  
		grid_layout->addWidget(m_aerobtn_list[i],0,1+i, Qt::AlignCenter);
	}
	
	connect(signal_mapper, SIGNAL(mapped(int)), this, SLOT(TurnPage(int)));

	header->addLayout(grid_layout);

	QVBoxLayout *main_layout = new QVBoxLayout();

	main_layout->addLayout(header);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);  

	setLayout(main_layout); 
    setFixedHeight(70);
}

AeroButton* TitleWidget::createToolButton(QString iconPath, QString buttonText)
{
	AeroButton *button = new AeroButton(0,QColor(255,255,255));
	button->setButtonText(buttonText);
	button->setTextColor(Qt::white);
	button->setColor(QColor(Qt::transparent));
	button->setShadow(QColor(Qt::black));
	button->setHighlight(QColor(Qt::black));
	button->setRoundness(0); 
	button->setOpacity(1);
	QFont font = ProfileInstance().AppFont;
	font.setPointSize(11); 
	button->setTextFont(font);
	button->setFixedSize(120, 50); 
	button->setButtonIcon(iconPath); 
	 
	return button;
}

void TitleWidget::setTitle(QString title)
{
    m_Title->setText(title);
}

void TitleWidget::TurnPage(int current_page)
{
	bool ok;
	int current_index = current_page; 
	int nCnt = m_aerobtn_list.count();

	for (int i = 0; i < m_aerobtn_list.count(); i++)
	{
		AeroButton *tool_button = m_aerobtn_list.at(i);
		if (current_index == i)
		{
			tool_button->setPressed(true);  
		}
		else
		{
			tool_button->setPressed(false);
        }
	}

	emit __turnPage(current_index);
}
