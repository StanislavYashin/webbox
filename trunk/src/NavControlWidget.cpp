#include "NavControlWidget.h"
#include "IconWidget.h"
#include "SearchWidget.h"

#define ICONSIZE 40

NavControlWidget::NavControlWidget(QWidget *parent)
	: QWidget(parent)
{
	IconWidget *backwardWidget = new IconWidget(ICONSIZE, ICONSIZE, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/icon/UI/backward2.png", QColor(24, 116, 205, 120), QColor(0, 0, 0), QColor(24, 116, 205));
	backwardWidget->setRoundCorner(ICONSIZE/2);
	IconWidget *forwardWidget = new IconWidget(ICONSIZE, ICONSIZE, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/icon/UI/forward2.png", QColor(24, 116, 205, 120), QColor(0, 0, 0), QColor(24, 116, 205));
	forwardWidget->setRoundCorner(ICONSIZE / 2);
	IconWidget *homeWidget = new IconWidget(ICONSIZE, ICONSIZE, Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/icon/UI/home.png", QColor(24, 116, 205, 120), QColor(0, 0, 0), QColor(24, 116, 205));
	homeWidget->setRoundCorner(ICONSIZE / 2);

	QSignalMapper *mapper = new QSignalMapper(this);
	mapper->setMapping(backwardWidget, 0); connect(backwardWidget, SIGNAL(OnWidgetClicked(IconWidget *)),mapper,SLOT(map()));
	mapper->setMapping(homeWidget, 1); connect(homeWidget, SIGNAL(OnWidgetClicked(IconWidget *)), mapper, SLOT(map()));
	mapper->setMapping(forwardWidget, 2); connect(forwardWidget, SIGNAL(OnWidgetClicked(IconWidget *)), mapper, SLOT(map()));
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(HandleEvent(int)));

	//SearchWidget *searchPage = new SearchWidget(); 
	//searchPage->setContentsMargins(0, 0, 0, 0);
	//searchPage->setFixedSize(240, 40);

	//QPalette palette;
	//palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 220)));// Qt::transparent));
	//this->setPalette(palette);
	//this->setAutoFillBackground(true);

	/*QLineEdit *line_edit = new QLineEdit();
	line_edit->setFont(QFont("Microsoft Yahei", 10));
	line_edit->setPlaceholderText(QString::fromWCharArray(L"搜索无限可能"));
	QPalette palette_line_edit;
	palette_line_edit.setBrush(QPalette::Text, QBrush(QColor(24, 116, 205, 220)));
	line_edit->setPalette(palette_line_edit);
	line_edit->setAlignment(Qt::AlignCenter);
	line_edit->setContentsMargins(0, 0, 0, 0);
	line_edit->setTextMargins(0, 5, 0, 5);
	line_edit->setFixedWidth(230);
	line_edit->setObjectName("SearchBox");
	line_edit->setStyleSheet("QWidget#SearchBox{background:transparent; border-radius: 3px;}");*/

	QHBoxLayout *main_layout = new QHBoxLayout();
	//main_layout->addWidget(line_edit);
	main_layout->addWidget(backwardWidget);
	main_layout->addWidget(homeWidget);
	main_layout->addWidget(forwardWidget);

	setLayout(main_layout);
}
 
void NavControlWidget::HandleEvent(int index)
{
	if (index == 0)
	{
		emit OnBackClicked(this);
	}
	else if (index == 1)
	{
		emit OnHomeClicked(this);
	}
	else if (index == 2)
	{
		emit OnForwardClicked(this);
	}
}

NavControlWidget::~NavControlWidget()
{
	
} 


