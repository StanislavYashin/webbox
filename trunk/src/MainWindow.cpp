#include "MainWindow.h"
#include <QLabel>
#include "GlowEffect.h"

#include "LauncherWidget.h"
#include "AppStoreWidget.h"
#include "GameStoreWidget.h"
#include "MusicWidget.h"
#include "VideoWidget.h"
#include "ExploreWidget.h"
#include "Console.hpp"

MainWindow::MainWindow(QWidget* parent)
	: DropShadowWindow(parent)
{
    //initLocalConnection();

	Console::instance().log(L"MainWindow constructor entering", LOG_LEVEL::LL_VERBOSE);

    InitializeFromConfig(Profile::GetProfile());
	setWindowIcon(QIcon(":/webbox"));
	 
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE); 
	this->setFont(Profile::GetProfile().AppFont);
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE);
	this->m_Title = new QLabel();
	m_Title->setText("@dreamxstudio");
	m_Title->setObjectName("whiteLabel");
	m_Title->setMaximumSize(100, 50);
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE);
	m_stacked_widget = new QStackedWidget();

    m_title_widget = new TitleWidget();
 
	m_stacked_widget->setContentsMargins(0, 0, 0, 0);
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE);
	QList<QWidget*>  pages; 
	pages.append(new LauncherWidget());
	pages.append(new AppStoreWidget());
	pages.append(new GameStoreWidget());
	pages.append(new MusicWidget());
	//pages.append(new VideoWidget());
	pages.append(new ExploreWidget());
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE);
	for (int i = 0; i < pages.count(); ++i)
	{
		m_stacked_widget->addWidget(pages.at(i));
	}
	Console::instance().log(L"", LOG_LEVEL::LL_VERBOSE);
	QVBoxLayout *center_layout = new QVBoxLayout();
	center_layout->addWidget(m_stacked_widget); 
	center_layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *top_layout = new QVBoxLayout();
	top_layout->setContentsMargins(0, 0, 0, 0);
	top_layout->addWidget(m_title_widget); 

	QVBoxLayout *main_layout = new QVBoxLayout();
	 
	main_layout->addLayout(top_layout);  
	main_layout->addLayout(center_layout); 
	main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);
	
	setLayout(main_layout);

	m_current_page = 0;
	 
	connect(m_title_widget, SIGNAL(__turnPage(int)), this, SLOT(__turnPage(int)));

    m_title_widget->TurnPage(0);  

	Console::instance().log(L"MainWindow constructor finished", LOG_LEVEL::LL_VERBOSE);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::InitializeFromConfig(Profile &cfg)
{ 
	setBackground(cfg.g_bkmode,cfg.g_bkimageurl); 
	setMinimumSize(cfg.WindowWidth, cfg.WindowHeight);
}

void MainWindow::__turnPage(int pageIndex)
{
	if (pageIndex < m_stacked_widget->count())
	{
		m_stacked_widget->setCurrentIndex(pageIndex);
	}
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	DropShadowWindow::paintEvent(event);
}

void MainWindow::initLocalConnection()
{  
	m_IsRunning = false;
	QCoreApplication::setApplicationName("Webbox");
	QString serverName = QCoreApplication::applicationName();

	QLocalSocket socket;
	socket.connectToServer(serverName);

	if (socket.waitForConnected(500))
	{
		m_IsRunning = true; 
		return;
	}

	//连接不上服务器，就创建一个
	m_Server = new QLocalServer(this);
	connect(m_Server, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
	if (m_Server->listen(serverName))
	{
		//防止程序崩溃时,残留进程服务,移除之  
		if (m_Server->serverError() == QAbstractSocket::AddressInUseError && QFile::exists(m_Server->serverName()))
		{
			QFile::remove(m_Server->serverName());
			m_Server->listen(serverName);
		}
    }
}

void MainWindow::__newLocalConnection()
{ 
	QLocalSocket *socket = m_Server->nextPendingConnection();
	if (!socket)
		return;

	socket->waitForReadyRead(1000);

	delete socket; 
}


bool MainWindow::isRunning()
{
	return m_IsRunning;
}
