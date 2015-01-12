#pragma once

#include <QtWidgets>
#include "Config.h"
#include "Common.h"

class NewsWidget : public QWidget
{
	Q_OBJECT
public:

	NewsWidget(QWidget *parent = 0);
	virtual~NewsWidget();
};