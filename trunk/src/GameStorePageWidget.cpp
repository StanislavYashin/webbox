#include "GameStorePageWidget.h"
#include "GlowButton.h"
#include "StoreItemWidget.h"
#include "GridContentWidget.h"
#include "SecondaryDetailWidget.h"
#include "NavControlWidget.h" 
#include "DocumentManager.hpp"

#define GAME_CONTENT_ROW 2
#define GAME_CONTENT_COL 2

TCHAR *game_category_arr[] = { 
	L"FPS",
	L"RPG",
	L"休闲",
	L"体育",
	L"动作",
	L"MMO",
	L"竞速",
	L"策略",
	L"模拟",
	L"冒险",
	L"独立" };

AppletWidget *game_content_arr[GAME_CONTENT_ROW][GAME_CONTENT_COL];

GameStorePageWidget::GameStorePageWidget(BoxDocument *doc,QWidget *parent)
	:QWidget(parent)
{
	_doc = doc;

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent)); // Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true);
	  
	//this->setFixedSize(ProfileInstance().WindowWidth, 150);

	m_image_dir = "C:/Users/shijie/Pictures";

	QString covers[] =
	{
		"Cover0.jpg",
		"Cover1.jpg",
		"Cover2.jpg",
		"Cover3.jpg",
		"Cover4.jpg",
		"Cover5.jpg",
		"Cover6.jpg" 
	};

	QList<GlowButton*> m_aerobtn_list;
	 
	/*
	QLineEdit *line_edit = new QLineEdit();
	line_edit->setFont(QFont("Microsoft Yahei", 10));
	line_edit->setPlaceholderText(QString::fromWCharArray(L"搜索商店"));
	QPalette palette_line_edit;
	palette_line_edit.setBrush(QPalette::Text, QBrush(QColor(24, 116, 205, 255)));
	line_edit->setPalette(palette_line_edit);
	line_edit->setAlignment(Qt::AlignCenter);
	line_edit->setContentsMargins(20, 10, 20, 10);
	line_edit->setTextMargins(0, 5, 0, 5);
	line_edit->setFixedWidth(150);
	line_edit->setObjectName("SearchBox");
	line_edit->setStyleSheet("QWidget#SearchBox{background:transparent;border-radius: 2px;}");
	*/
	 
	QList<GlowButton*> m_submenu_list;

	QSignalMapper *menu_mapper = new QSignalMapper(this); 

	for (int i = 0; i < 10; ++i)
	{
		m_submenu_list.append(createToolButton(menu_mapper, i, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(game_category_arr[i])));
	}

	connect(menu_mapper, SIGNAL(mapped(int)), this, SLOT(OnCategoryChanged(int)));

	QVBoxLayout *menu_layout = new QVBoxLayout();	
	menu_layout->setContentsMargins(0, 0, 0, 0);
	menu_layout->setSpacing(0);
	menu_layout->setMargin(0);
 
	QHBoxLayout *sub_menu_layout = NULL;

	for (int i = 0; i < m_submenu_list.count(); ++i)
	{
		if (i%10 ==0 )
		{ 
			sub_menu_layout = new QHBoxLayout();
			sub_menu_layout->setContentsMargins(0, 0, 0, 0);
			sub_menu_layout->setSpacing(0);
			sub_menu_layout->setMargin(0);

			menu_layout->addLayout(sub_menu_layout); 
		}  

		sub_menu_layout->addWidget(m_submenu_list[i]);

		if (i == m_submenu_list.count() - 1 && i% 10!= 0)
		{
			menu_layout->addStretch();
			//sub_menu_layout->addWidget(line_edit);
		}
	} 

	grid_widget = new GridContentWidget(GAME_CONTENT_ROW, GAME_CONTENT_COL);
	 
	stacked_widget = new QStackedWidget();
	stacked_widget->setContentsMargins(0, 0, 0, 0);
	stacked_widget->addWidget(grid_widget);
  
	NavControlWidget *navWidget = new NavControlWidget();

	connect(navWidget, SIGNAL(OnBackClicked(NavControlWidget *)), SLOT(OnBackward()));
	connect(navWidget, SIGNAL(OnHomeClicked(NavControlWidget *)), SLOT(OnHome()));
	connect(navWidget, SIGNAL(OnForwardClicked(NavControlWidget *)), SLOT(OnForward()));

	QHBoxLayout *bot_layout = new QHBoxLayout();
	bot_layout->addStretch();
	bot_layout->addWidget(navWidget);
	bot_layout->addStretch();

	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->addLayout(menu_layout);
	right_layout->addWidget(stacked_widget);
 
	//right_layout->addSpacing(10);
	//right_layout->addLayout(bot_layout);
	 
	QHBoxLayout *upper_layout = new QHBoxLayout();
	upper_layout->setContentsMargins(0, 0, 0, 0);
	upper_layout->setSpacing(0);

	upper_layout->addLayout(menu_layout);
	upper_layout->addLayout(right_layout);
	upper_layout->addStretch();

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->setMargin(0);
	main_layout->addLayout(upper_layout);
	main_layout->addStretch();
	main_layout->addLayout(bot_layout);

	this->setLayout(main_layout);

	m_submenu_list[0]->check();
}

GameStorePageWidget::~GameStorePageWidget()
{

}

GlowButton* GameStorePageWidget::createToolButton(QSignalMapper *mapper, int id, QString iconPath, QString buttonText, bool extraMode)
{
	GlowButton *button = new GlowButton(70, 50, extraMode, "", buttonText, QColor(255, 255, 255, 0), QColor(24, 116, 205, 255));

	button->setTransition(false);
	button->setIsBackgroundTransparent(true);
	button->setMode(eGlowButtonMode::GBM_NOBACKGROUND);
	button->setTextColor(QColor(255, 255, 255, 255));
	button->setGroupId(CFG_GAMESTORE_SUBMENU_GUID);

	QFont font = QFont("Microsoft Yahei");
	font.setPixelSize(15);
	font.setBold(false);
	button->setFont(font);
	connect(button, SIGNAL(glowButtonClicked(GlowButton*)), mapper, SLOT(map())); 
	mapper->setMapping(button, id);
	return button;
}

void GameStorePageWidget::OnItemClicked()
{ 
	DetailGameInfo info;

	info.title_zh = QString::fromWCharArray(L"巫师3:狂猎");
	info.platform = QString::fromWCharArray(L"PC,PS4,XBOXONE");
	info.publisher = QString::fromWCharArray(L"CD Projekt Red");
	info.rating = QString::fromWCharArray(L"RP");
	info.title_en = QString::fromWCharArray(L"The Witcher 3: Wild Hunt");
	info.type = QString::fromWCharArray(L"角色扮演(RPG)");
	info.date = QString::fromWCharArray(L"2014年10月1日");

	SecondaryDetailWidget *subWidget = new SecondaryDetailWidget(620, 512, true, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/game/Cover2.jpg", QString::fromWCharArray(L"巫师3"));
	subWidget->setGameInfo(info);

	scrollArea = new QScrollArea;
	scrollArea->setGeometry(subWidget->geometry());
	scrollArea->setWidget(subWidget); // MainWidget is the container widget i.e. the window itself
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	scrollArea->viewport()->setAutoFillBackground(true);
	scrollArea->setStyleSheet("background-color:transparent;");

	scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	/*scrollArea->viewport()->setObjectName("scrollAreaViewPort");
	scrollArea->viewport()->setStyleSheet("scrollAreaViewPort{background-color:transparent;}");*/

	stacked_widget->addWidget(scrollArea);
	stacked_widget->setCurrentWidget(scrollArea);
}

void GameStorePageWidget::OnBackward()
{
	stacked_widget->setCurrentIndex(0);
}

void GameStorePageWidget::OnForward()
{
	if (stacked_widget->count()>1)
		stacked_widget->setCurrentIndex(1);
}

void GameStorePageWidget::OnHome()
{
	stacked_widget->setCurrentIndex(0);
}

void GameStorePageWidget::OnCategoryChanged(int index)
{
	auto result = _doc->findCategory(QString::fromWCharArray(game_category_arr[index]));
	loadProperties(result);
}

void GameStorePageWidget::loadProperties(QList<Webbox::Data::CommonProperty*> propertyList)
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (game_content_arr[i][j] != NULL)
			{
				grid_widget->removeItem(game_content_arr[i][j]);
				game_content_arr[i][j] = NULL;
			}
		}
	}

	stacked_widget->removeWidget(scrollArea);
	scrollArea = NULL;
	stacked_widget->removeWidget(grid_widget);
	delete grid_widget;
	grid_widget = NULL;
	grid_widget = new GridContentWidget(GAME_CONTENT_ROW, GAME_CONTENT_COL);

	int idx = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (propertyList.count()>idx)
			{
				AppletWidget *widget = new AppletWidget(338, 225, false, propertyList[idx++]);
				connect(widget, SIGNAL(labelPress()), this, SLOT(OnItemClicked()));
				grid_widget->addItem(widget);
				game_content_arr[i][j] = widget;
			}
		}
	}

	stacked_widget->addWidget(grid_widget);

	update();
}