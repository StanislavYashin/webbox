#include "AppStoreRankingWidget.h"
#include "NavControlWidget.h"

AppStoreRankingWidget::AppStoreRankingWidget(QWidget *parent)
{
	QString paths[] =
	{
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/dota2.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/messages.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/safari.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/ibooks.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/launchpad.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/maps.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/facetime.png",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/gamecenter.png"
	};


	QColor colors[] =
	{
		QColor(255, 0, 0),
		QColor(0, 255, 0),
		QColor(0, 0, 255),
		QColor(100, 100, 100),
		QColor(255, 0, 255),
		QColor(0, 255, 255),
		QColor(0, 100, 230),
		QColor(255, 100, 0, 100),
	};

	contentWidget = new RankingWidget();

	for (int i = 0; i < 8; ++i)
	{
		RankingLabel *label = new RankingLabel(700, 100, 102, paths[i], QString::fromWCharArray(L"Office 2015"), QString::fromWCharArray(L"Windows 7+"), QString::fromWCharArray(L"ÆÆ½â"));
		label->setColor(colors[7]);
		contentWidget->addItem(label);
	}

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setGeometry(contentWidget->geometry());
	scrollArea->setWidget(contentWidget); // MainWidget is the container widget i.e. the window itself
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	/*scrollArea->viewport()->setAutoFillBackground(true);
	scrollArea->setStyleSheet("background-color:transparent;");*/

	scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
 
	NavControlWidget *navWidget = new NavControlWidget();
 
	QHBoxLayout *bot_layout = new QHBoxLayout();
	bot_layout->addStretch(); 
	bot_layout->addWidget(navWidget);
	bot_layout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout(); 
	mainLayout->addWidget(scrollArea);
	mainLayout->addLayout(bot_layout);

	setLayout(mainLayout);
}

AppStoreRankingWidget::~AppStoreRankingWidget()
{

}
