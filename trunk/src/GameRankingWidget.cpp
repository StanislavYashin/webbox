#include "GameRankingWidget.h"
#include "NavControlWidget.h"

GameRankingWidget::GameRankingWidget(QWidget *parent)
{ 
	QString paths[] =
	{
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover0.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover1.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover2.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover3.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover3.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover3.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover3.jpg",
		Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover3.jpg"
	};

	QColor colors[] = 
	{
		QColor(255,0,0),
		QColor(0,255,0),
		QColor(0,0,255),
		QColor(100,100,100),
		QColor(255,0,255),
		QColor(0,255,255),
		QColor(0,100,230),
		QColor(255,100,0),
	};

	contentWidget = new RankingWidget();

	for (int i = 0; i < 8; ++i)
	{
		RankingLabel *label = new RankingLabel(700, 100, 250, paths[i], QString::fromWCharArray(L"The Witch 3"), QString::fromWCharArray(L"PC,PS4,XBOX ONE"), QString::fromWCharArray(L"Ãâ·Ñ"));
		//label->setColor(colors[i]);
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
	//mainLayout->setContentsMargins(10, 10, 10, 10);
	//mainLayout->setSpacing(10);
	//mainLayout->setMargin(10);
	mainLayout->addWidget(scrollArea);
	mainLayout->addLayout(bot_layout);

	setLayout(mainLayout);
}

GameRankingWidget::~GameRankingWidget()
{

}
