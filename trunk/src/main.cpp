#define WIN32_LEAN_AND_MEAN
//#define TEST
#if !defined(TEST) 

#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QSharedMemory> 
#include <QtPlugin> 
#include <stdio.h>
#include "AtomReader.hpp"
#include "MainWindow.h"
#include "Console.hpp"
#include <qdebug.h>

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

#ifdef _DEBUG
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"Qt5Cored.lib")
#pragma comment(lib,"Qt5Guid.lib")
#pragma comment(lib,"Qt5OpenGLd.lib")
#pragma comment(lib,"libEGLd.lib")
#pragma comment(lib,"Qt5Widgetsd.lib")
#pragma comment(lib,"libGLESv2d.lib")
#pragma comment(lib,"translatord.lib")
#pragma comment(lib,"preprocessord.lib")
#pragma comment(lib,"qwindowsd.lib")
#pragma comment(lib,"Qt5Sqld.lib")
#pragma comment(lib,"Qt5Networkd.lib")
#pragma comment(lib,"Qt5PlatformSupportd.lib")
#else
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"qt5sql.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"Qt5Core.lib")
#pragma comment(lib,"Qt5Gui.lib")
#pragma comment(lib,"Qt5OpenGL.lib")
#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"libGLESv2.lib")
#pragma comment(lib,"translator.lib")
#pragma comment(lib,"preprocessor.lib")
#pragma comment(lib,"qwindows.lib")
#pragma comment(lib,"Qt5Network.lib")
#pragma comment(lib,"Qt5PlatformSupport.lib")
#endif  

#include "avhttp.hpp" 
#include <iostream>

int main(int argc, char **argv)
{
	QApplication app(argc, argv); 
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec); 
 
	QFile css(":/css/Style");
	css.open(QFile::ReadOnly); 
	qApp->setStyleSheet(css.readAll());
	css.close();

	Console::instance().log(L"entering main",LOG_LEVEL::LL_VERBOSE);

	//AtomReader::test();

	/*QSharedMemory shared_memory;
	shared_memory.setKey(QString("main_window"));

	if (shared_memory.attach())
	{
		return 0;
	}

	if (shared_memory.create(1))
	{ */
#define TEST_BUILD
	try
	{
		boost::asio::io_service io;
		avhttp::http_stream h(io); 
		boost::system::error_code err_c;

		h.open("http://www.boost.org/LICENSE_1_0.txt",err_c);
		if (err_c)
		{
			std::cout << "error:" << err_c.message() << std::endl;
			return EXIT_FAILURE;
		}

		boost::array<char, 1024> buffer;
		for (;!err_c;)
		{
			std::size_t bytes_transferred = h.read_some(boost::asio::buffer(buffer), err_c);
			std::cout.write(buffer.data(), bytes_transferred);
		}

		std::cout.flush();
		h.close();
		io.run();

		//std::cout << &h;// << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "error:" << e.what() << std::endl;
	} 

#ifndef TEST_BUILD
		MainWindow main_window;   
		main_window.showWindow();
#endif 
		return app.exec();
	//}

	return EXIT_FAILURE;
}


#endif