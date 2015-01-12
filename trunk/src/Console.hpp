/*******************************************************
* Written by Shijie                                   *
* This file is part of O3 project                     *
* O3Afx is a cross-platform 3D Graphic accelerated    *
* application framework which emerges application     *
* and game develepment into a single framework        *
* You may distribute this file without modification.  *
* dreamware@outlook.com                               *
* (c)2013 Dreamware(R) Corporation                    *
*******************************************************/

#ifndef __O_CONSOLE_H
#define __O_CONSOLE_H

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <windows.h> 

enum LOG_LEVEL
{
	LL_NONE,
	LL_TRACE,
	LL_VERBOSE,
}; 

class Console
{

public:

	static Console &instance()
	{
		static Console console;
		return console;
	}

	inline Console()
		: b_existed(false)
	{
		if (b_existed)
			return;

		AllocConsole();
		Attach(800, 600);

		b_existed = TRUE;
	}
	inline Console(SHORT x, SHORT y)
	{
		if (b_existed)
			return;

		AllocConsole();
		Attach(x, y);

		b_existed = true;
	}
	inline Console(LPCTSTR lpszTitle, SHORT ConsoleHeight = 300, SHORT ConsoleWidth = 80)
	{
		if (b_existed)
			return;

		AllocConsole();
		SetConsoleTitle(lpszTitle);
		Attach(ConsoleHeight, ConsoleWidth);

		b_existed = TRUE;
	}
	virtual inline ~Console()
	{
		if (b_existed)
		{
			FreeConsole();
			b_existed = FALSE;
		}
	}

public:

	void log(TCHAR *s = NULL, LOG_LEVEL level = LL_NONE)
	{
		if (s == NULL)
		{
			level = LL_TRACE;
		}

		switch (level)
		{
		case LL_NONE:
		{
			wprintf(L"[none] %s\n", s);
		}
			break;
		case LL_VERBOSE:
		{
			TCHAR str[1024];
			wsprintf(str, L"[verbose] %s [file: %s @LINE:%d]", s, __FILEW__, __LINE__);
			wprintf(L"%s\n", str);
		}

			break;
		case LL_TRACE:
		{
			TCHAR str[1024];
			wsprintf(str, L"[trace] %s@%s  @LINE:%d ", s, __FUNCTIONW__, __LINE__);
			wprintf(L"%s\n", str);
		}break;
		}
	}

private:
	void Attach(SHORT ConsoleHeight, SHORT ConsoleWidth)
	{
		HANDLE  hStd;
		int     fd;
		FILE    *file;

		// 重定向标准输入流句柄到新的控制台窗口

		hStd = GetStdHandle(STD_INPUT_HANDLE);
		fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT);
		file = _fdopen(fd, "r");
		setvbuf(file, NULL, _IONBF, 0);
		*stdin = *file;

		// 重定向标准输出流句柄到新的控制台窗口

		hStd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size;
		size.X = ConsoleWidth;
		size.Y = ConsoleHeight;
		SetConsoleScreenBufferSize(hStd, size);
		fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT);
		file = _fdopen(fd, "w");
		setvbuf(file, NULL, _IONBF, 0);
		*stdout = *file;

		// 重定向标准错误流句柄到新的控制台窗口

		hStd = GetStdHandle(STD_ERROR_HANDLE);
		fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT);
		file = _fdopen(fd, "w");
		setvbuf(file, NULL, _IONBF, 0);
		*stderr = *file;
	}

	BOOL b_existed;
}; 
 
#endif