#include "AppStoreWidget.h" 
#include "NavControlWidget.h"
#include "AppStoreRankingWidget.h"
#include "SearchWidget.h"
#include "DocumentManager.hpp"

AppStoreWidget::AppStoreWidget(QWidget *parent) :
QWidget(parent)
{ 
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 200)));
	this->setPalette(palette);
	this->setAutoFillBackground(true); 

	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"商业")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"开源")));
	m_aerobtn_list.append(__createToolButton(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(L"插件")));
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
	 
	__doc = DocumentManager::getAppStoreDocument();

	AppStorePageWidget *storePage = new AppStorePageWidget(__doc,this);
	AppStoreRankingWidget *rankPage = new AppStoreRankingWidget();
	SearchWidget *searchPage = new SearchWidget();

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(storePage);
	stackedWidget->addWidget(rankPage);
	stackedWidget->addWidget(searchPage);
	stackedWidget->setCurrentIndex(0);  

	//navWidget = new NavControlWidget(); 
	//navWidget->setObjectName("navictl");

	QHBoxLayout *bot_layout = new QHBoxLayout();
	bot_layout->addStretch();
	//bot_layout->addWidget(navWidget);
	bot_layout->addStretch();

	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->setSpacing(0);
	right_layout->setContentsMargins(0, 0, 0, 0);
	right_layout->addWidget(stackedWidget);
	right_layout->addLayout(bot_layout);

	mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	mainLayout->addLayout(menu_layout);
	mainLayout->addLayout(right_layout);
	mainLayout->addStretch();

	this->setLayout(mainLayout);

	m_aerobtn_list[0]->check();
}  

GlowButton* AppStoreWidget::__createToolButton(QString iconPath, QString buttonText, bool extraMode)
{
	GlowButton *button = new GlowButton(128, 50, extraMode, iconPath, buttonText, QColor(255, 255, 255, 255), QColor(255, 255, 255, 255));  // , QColor(24, 116, 205, 255));
	 
	button->setTransition(true);
	button->setTextColor(QColor(24, 116, 205, 255));      // QColor(24, 116, 205, 255));
	button->setGroupId(CFG_APPSTORE_GUID);
	QFont font = QFont("Microsoft Yahei");
	font.setPixelSize(16);
	button->setFont(font);
	button->setFixedSize(120, 50);
	button->setMouseTracking(true);

	return button;
}

void AppStoreWidget::switchPage(int page)
{ 
	if (page == 3)
		stackedWidget->setCurrentIndex(1);
	if (page == 0)
		stackedWidget->setCurrentIndex(0);
	if (page == 5)
		stackedWidget->setCurrentIndex(2);
}