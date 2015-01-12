#pragma once

#include <QPainter>
#include <QToolButton>
#include <QMouseEvent>
#include "Config.h"
#include "Common.h"

class ToolButton : public QToolButton
{
public:
	explicit ToolButton(int w, int h, QPixmap pic, QWidget *parent = 0);

    virtual ~ToolButton();

    void setMousePress(bool mouse_press);

protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void painterInfo(int top_color, int middle_color, int bottom_color);

private:

    _public(bool, MouseOver)
    _public(bool, MousePress)
};
