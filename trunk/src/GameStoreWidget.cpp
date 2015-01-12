#include "GameStoreWidget.h"  
#include "NavControlWidget.h"
#include "GameRankingWidget.h"
#include "SearchWidget.h"
#include "GeneralDocument.hpp"
#include "DocumentManager.hpp"

GlowButton* GameStoreWidget::__createToolButton(QString iconPath, QString buttonText, bool extraMode)
{
	GlowButton *button = new GlowButton(128, 50, extraMode, iconPath, buttonText, QColor(255, 255, 255, 255), QColor(255, 255, 255, 255));// QColor(255, 255, 255, 255), QColor(0, 0, 0, 255)); // , QColor(24, 116, 205, 255));

	button->setTransition(true);
	button->setTextColor(QColor(24, 116, 205, 255));
	button->setGroupId(CFG_GAMESTORE_GUID);
	QFont font = QFont("Microsoft Yahei");
	font.setPixelSize(16);
	button->setFont(font);
	button->setFixedSize(120, 50);
	button->setMouseTracking(true);

	return button;
}

GameStoreWidget::GameStoreWidget(QWidget *parent) :
	QWidget(parent)
{
	QLabel *m_Title = new QLabel();
	m_Title->setText("@gamestore");
	 
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 200))); //Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true); 

	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"单机")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"网络")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"Web")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"排行"))); 
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"资讯")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"下载")));
	
	QVBoxLayout *menu_layout = new QVBoxLayout();
	menu_layout->setContentsMargins(0, 0, 0, 0);
	menu_layout->setSpacing(0);
	menu_layout->setMargin(0);
	menu_layout->setAlignment(Qt::AlignLeft);

	QSignalMapper *signal_mapper = new QSignalMapper(this);

	for (int i = 0; i < m_aerobtn_list.count(); ++i)
	{
		connect(m_aerobtn_list[i], SIGNAL(glowButtonClicked(GlowButton*)), signal_mapper, SLOT(map()));
		signal_mapper->setMapping(m_aerobtn_list[i], i);  
		menu_layout->addWidget(m_aerobtn_list[i]); 
	}
	
	connect(signal_mapper, SIGNAL(mapped(int)), this, SLOT(switchPage(int)));
	
	menu_layout->addStretch();

	GameStorePageWidget *storePageWidget = new GameStorePageWidget(DocumentManager::getGameStoreDocument());
	//storePageWidget->dataSource = &Ge::ContentProviderInstance();
	GameRankingWidget *gameRankingWidget = new GameRankingWidget();
	SearchWidget *searchPage = new SearchWidget();
	 
	stacked_widget = new QStackedWidget();
	  
	stacked_widget->addWidget(storePageWidget);
	stacked_widget->addWidget(gameRankingWidget);
	stacked_widget->addWidget(searchPage);

	stacked_widget->setCurrentIndex(0);
  
	//NavControlWidget *navWidget = new NavControlWidget();
	QHBoxLayout *bot_layout = new QHBoxLayout();
	bot_layout->addStretch();
	//bot_layout->addWidget(navWidget);
	bot_layout->addStretch();

	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->setContentsMargins(0, 0, 0, 0);
	right_layout->setSpacing(0);
	right_layout->setMargin(0);
	right_layout->addWidget(stacked_widget); 
	right_layout->addStretch();
	//right_layout->addLayout(bot_layout);
 
	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addLayout(menu_layout);
	main_layout->addLayout(right_layout);
	main_layout->addStretch(); 

	this->setLayout(main_layout);

	m_aerobtn_list[0]->check();
}

void GameStoreWidget::switchPage(int page)
{ 
	if (page == 3)
		stacked_widget->setCurrentIndex(1);
	if (page == 0)
		stacked_widget->setCurrentIndex(0);
	if (page == 5)
		stacked_widget->setCurrentIndex(2);
}
