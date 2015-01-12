#include "AppStorePageWidget.h"
#include "GlowButton.h"
#include "SecondaryDetailWidget.h"
#include "GridContentWidget.h"
#include "NavControlWidget.h"
#include "AeroButton.h"

#define APP_CONTENT_ROW 4
#define APP_CONTENT_COL 3

TCHAR *app_category_arr[] = { L"网络", L"媒体", L"系统", L"实用工具", L"行业", L"编程", L"安全" };
AppletWidget *app_content_arr[APP_CONTENT_ROW][APP_CONTENT_COL];

GlowButton* AppStorePageWidget::createMenu(QSignalMapper *mapper,int id, QString iconPath, QString buttonText, bool extraMode)
{ 
	if (mapper == NULL)
		return NULL;

	GlowButton *button = new GlowButton(80, 50, extraMode, "", buttonText, QColor(255, 255, 255, 0), QColor(24, 116, 205, 255));
	 
	button->setTransition(false);
	button->setIsBackgroundTransparent(true);
	button->setMode(eGlowButtonMode::GBM_NOBACKGROUND);
	button->setGroupId(CFG_APPSTORE_SUBMENU_GUID);
	 
	button->setTextColor(QColor(255, 255, 255, 255));
	 
	QFont font = QFont("Microsoft Yahei");
	font.setPixelSize(15);
	font.setBold(false);
	button->setFont(font);
	connect(button, SIGNAL(glowButtonClicked(GlowButton*)), mapper, SLOT(map()));

	mapper->setMapping(button, id); 
	 
	return button; 
}

AppStorePageWidget::AppStorePageWidget(BoxDocument *doc,QWidget *parent)
	:QWidget(parent)
{
	_doc = doc;

	QPalette palette; 
	palette.setBrush(QPalette::Window, QBrush(Qt::transparent)); 
	this->setPalette(palette);
	this->setAutoFillBackground(true);
 
	m_image_dir = "C:/Users/shijie/Pictures";
 
	QString paths[] =
	{
		"dota2.png",
		"messages.png",
		"safari.png",
		"ibooks.png",
		"launchpad.png",
		"maps.png",
		"facetime.png",
		"gamecenter.png"
	};
 
	QList<GlowButton*> m_aerobtn_list;
 
	QSignalMapper *menu_mapper = new QSignalMapper(this);

	for (int i = 0; i <= 6; ++i)
	{
		m_aerobtn_list.append(createMenu(menu_mapper, i, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/Blue/MB_0014_iTunes.png", QString::fromWCharArray(app_category_arr[i])));
	}
	 
	connect(menu_mapper, SIGNAL(mapped(int)), this, SLOT(OnCategoryChanged(int)));

	QHBoxLayout *menu_layout = new QHBoxLayout();
	menu_layout->setContentsMargins(0, 0, 0, 0);
	menu_layout->setSpacing(0);
	menu_layout->setMargin(0);
 
	for (int i = 0; i < m_aerobtn_list.count(); ++i)
	{
		menu_layout->addWidget(m_aerobtn_list[i]);
	} 

	menu_layout->addStretch();
	 
	NavControlWidget *navWidget = new NavControlWidget();

	connect(navWidget, SIGNAL(OnBackClicked(NavControlWidget *)), SLOT(OnBackward()));
	connect(navWidget, SIGNAL(OnHomeClicked(NavControlWidget *)), SLOT(OnHome()));
	connect(navWidget, SIGNAL(OnForwardClicked(NavControlWidget *)), SLOT(OnForward()));

	QHBoxLayout *bot_layout = new QHBoxLayout();
	bot_layout->addStretch();
	bot_layout->addWidget(navWidget);
	bot_layout->addStretch();

	grid_widget = new GridContentWidget(APP_CONTENT_ROW, APP_CONTENT_COL);
  
	stacked_widget = new QStackedWidget();
	stacked_widget->setContentsMargins(10, 0, 0, 10);
	stacked_widget->setPalette(palette);
	stacked_widget->setAutoFillBackground(true);
	stacked_widget->addWidget(grid_widget);
  
	QVBoxLayout *right_layout = new QVBoxLayout();
	right_layout->addLayout(menu_layout); 
	right_layout->addWidget(stacked_widget);
	 
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

	m_aerobtn_list[0]->check();
}

void AppStorePageWidget::loadProperties(QList<Webbox::Data::CommonProperty*> propertyList)
{   
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (app_content_arr[i][j] != NULL)
			{
				grid_widget->removeItem(app_content_arr[i][j]);
				app_content_arr[i][j] = NULL;
			}
		}
	}
	stacked_widget->removeWidget(scrollArea);
	stacked_widget->removeWidget(grid_widget);
	delete grid_widget;
	grid_widget = NULL;
	grid_widget = new GridContentWidget(APP_CONTENT_ROW, APP_CONTENT_COL);
	
	int idx = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (propertyList.count()>idx)
			{ 
				AppletWidget *widget = new AppletWidget(209, 90, false, propertyList[idx++]);
				connect(widget, SIGNAL(labelPress()), this, SLOT(OnItemClicked())); 
				grid_widget->addItem(widget);
				app_content_arr[i][j] = widget;
			}
		}
	}

	stacked_widget->addWidget(grid_widget);

	update(); 
}

AppStorePageWidget::~AppStorePageWidget()
{
   
}  

void AppStorePageWidget::OnBackward()
{
	stacked_widget->setCurrentIndex(0);
}

void AppStorePageWidget::OnForward()
{
	if (stacked_widget->count()>1)
		stacked_widget->setCurrentIndex(1);
}

void AppStorePageWidget::OnHome()
{
	stacked_widget->setCurrentIndex(0);
}

void AppStorePageWidget::OnItemClicked()
{  
	DetailGameInfo info;

	info.title_zh = QString::fromWCharArray(L"巫师3:狂猎");
	info.platform = QString::fromWCharArray(L"PC,PS4,XBOXONE");
	info.publisher = QString::fromWCharArray(L"CD Projekt Red");
	info.rating = QString::fromWCharArray(L"RP");
	info.title_en = QString::fromWCharArray(L"The Witcher 3: Wild Hunt");
	info.type = QString::fromWCharArray(L"角色扮演(RPG)"); 
	info.date = QString::fromWCharArray(L"2014年10月1日");

	SecondaryDetailWidget *subWidget = new SecondaryDetailWidget(700, 512, true, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/game/Cover2.jpg", QString::fromWCharArray(L"巫师3"));
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

void AppStorePageWidget::OnCategoryChanged(int index)
{
	auto result = _doc->findCategory(QString::fromWCharArray(app_category_arr[index]));
	loadProperties(result); 
}