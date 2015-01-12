#pragma once

#include <QDialog.h>
#include <QPainter>
#include <QtWidgets>
#include "stdafx.h"
#include "DropShadowWindow.define.h"
#include "basestylewidget.h"

class DropShadowWindow : public BaseStyleWidget
{
	Q_OBJECT
/*method*/
public:

    explicit DropShadowWindow(QWidget *parent = 0);
	~DropShadowWindow(); 

	void showWindow();
	void initializeWindow();
	void changeTheme(); 
	void setBackground(eBKMode bkMode, QString bkImageURL);
 
protected:

	virtual void paintEvent(QPaintEvent *event); 
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
	
	void _drawWindowShadow(QPainter &painter);
 
private:

    void __setCursorStyle(const QPoint &cursorPoint);
    //void __setDrayMove(int nXGlobal,int nYGlobal,eDirection Dir);
	//void __setCursorStyle(eDirection Dir);
	//eDirection __pointValid(int nXRelative, int nYRelative);

    _declare(eBKMode,   BackgroundMode)
    _declare(QString,   BackgroundImageURL)

	_property(QPixmap*, BackgroundImage)
    _property(QImage*,  Img)
	_property(QColor,   BackgroundColor) 
	_property(bool,		DropShadowEnabled)
	_property(QLabel*,  Title)

	_private(QPoint,	MovePoint)
	_private(bool,		LeftMouseDown)
	_private(QPoint,	DragPosition)
	_private(eDirection,Dir) 
};
