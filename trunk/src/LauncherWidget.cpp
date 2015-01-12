#include "LauncherWidget.h"
#include "AeroButton.h"
#include "Config.h"
#include "ToolButton.h" 
#include "BoxDocument.hpp"
#include "DocumentManager.hpp"

LauncherWidget::LauncherWidget(QWidget *parent) :
BaseStyleWidget(parent)
{
	QLabel *m_Title = new QLabel();
	m_Title->setText("@launcher"); 

	this->setObjectName("launcher");

	//this->setStyleSheet("LauncherWidget { border-image:url('Webbox::Utility::PathUtil::GetCurrentExePath() + /Skin/img/abstract.jpg') 0 0 0 0 stretch stretch; border-radius: 0px;  margin:0px;}");

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 240)));// Qt::transparent));
	this->setPalette(palette);
	this->setAutoFillBackground(true);

	m_dockWidget = new DockWidget(this); 
	 
	//m_dockWidget.setupUi(this);
	setMouseTracking(true);

	connect(m_dockWidget, SIGNAL(IconClicked(int)), this, SLOT(__onItemClicked(int)));
 
	QString paths[] = { 
		"dota2.png" ,
		"messages.png",
		"safari.png",
		"ibooks.png",
		"launchpad.png",
		"maps.png",
		"facetime.png",
		"gamecenter.png"
	}; 

	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("dota2.png")), "Dota 2 CN");
	//m_dockWidget->AddIcon(QPixmap(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/vancl_round.png"), "VANCL");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("messages.png")), "iMessage");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("safari.png")), "Safari");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("ibooks.png")), "iBooks");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("launchpad.png")), "LaunchPad");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("maps.png")), "Maps");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("facetime.png")), "FaceTime");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("maps.png")), "Maps");
	m_dockWidget->AddIcon(QPixmap(Webbox::Config::AllCfg::getIconPath().append("gamecenter.png")), "Game Center");

	QGridLayout *grid_layout = new QGridLayout();
	grid_layout->setContentsMargins(0,0,0,0);
	grid_layout->setMargin(0); 
 
	//BoxDocument *doc = DocumentManager::get

	int idx = 0;

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			if (idx < 8)
			{
				Webbox::Data::LaunchProperty *_property = new Webbox::Data::LaunchProperty();
				_property->icon_name = paths[idx++];
				_property->name_cn = "Sample App";
				grid_layout->addWidget(addToolButton(80, 80, _property), row, col, Qt::AlignCenter);
			}
			else
			{
				grid_layout->addWidget(new QWidget(), row, col, Qt::AlignCenter);
			}
		}
	}
		

	//int idx = 0;

	//for (int row = 0; row < 3; ++row) 
	//	for (int col = 0; col < 5; ++col)
	//	{ 
	//		if (idx < 8)
	//		{
	//			/*Webbox::Data::LaunchProperty *_property = new Webbox::Data::LaunchProperty();
	//			QFile file(paths[idx++]);
	//			file.open(QIODevice::ReadOnly);
	//			QByteArray blob = file.readAll();
	//			_property->setIcon(blob);
	//			_property->setNameCN("Sample App");*/
	//			grid_layout->addWidget(addToolButton(80, 80, _property), row, col, Qt::AlignCenter);
	//		} 
	//		else
	//		{
	//			grid_layout->addWidget(new QWidget(), row, col, Qt::AlignCenter); 
	//		}
	//	} 	
	 
	QVBoxLayout *main_layout = new QVBoxLayout(); 
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addLayout(grid_layout);
	main_layout->addWidget(m_dockWidget);

	this->setLayout(main_layout);
}

ToolButton* LauncherWidget::addToolButton(int w, int h, Webbox::Data::LaunchProperty *_p) // QString iconPath, QString buttonText)
{
	QFont font = ProfileInstance().AppFont;
	font.setPointSize(11); 
	//QPixmap p;
	//p.loadFromData(_p->getIcon());
	ToolButton *btn = new ToolButton(w, h, QPixmap(Webbox::Config::AllCfg::getIconPath()+"/"+_p->icon_name));
	btn->setText(_p->name_cn);  
	btn->setFont(font);  
	 
	return btn;
}

LauncherWidget::~LauncherWidget()
{
}

void LauncherWidget::__onItemClicked(int iconIndex)
{
	/*QString title = "MacDock - you clicked icon %1";
	title = title.arg(iconIndex + 1);
	setWindowTitle(title);*/
}