#include <QApplication>
#include <QDir>
//#define TEST
#if defined(TEST)
#include "httpwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	HttpWindow httpWin;

	httpWin.show();
	return app.exec();
}
#endif