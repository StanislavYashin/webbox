#pragma once

#include <QPainter>
#include <QtWidgets>
#include "stdafx.h"
#include "BaseStyleWidget.h"

class ContentWidget : public QWidget
{
Q_OBJECT

public:

    ContentWidget(QWidget *parent = 0);

protected:
 
private:

    QSplitter *main_splitter;
};
