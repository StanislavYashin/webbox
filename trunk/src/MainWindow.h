#include "DropShadowWindow.h" 

#include <QtNetwork\QLocalSocket>
#include <QtNetwork\QLocalServer>
#include "Config.h"
#include "TitleWidget.h"
#include "MainWindow.define.h"
#include "ContentWidget.h"
//#include "ui_DockWidget.h"

class MainWindow : public DropShadowWindow 
{
	Q_OBJECT

		/*METHODS*/
public:

	MainWindow(QWidget* parent = 0);
	~MainWindow();
	
	void InitializeFromConfig(Profile &cfg);

	bool isRunning();

protected:

	void paintEvent(QPaintEvent *event);

private slots:
	void __turnPage(int pageId);
	void __newLocalConnection();

private:
	void initLocalConnection();

	_private(int, current_page);

	/*DATA*/
	_private(TitleWidget*, title_widget)

	_private(QLocalServer*, Server)

	_private(bool, IsRunning)

	_private(ContentWidget*, content_widget)

	_private(QStackedWidget*, stacked_widget) 
};
