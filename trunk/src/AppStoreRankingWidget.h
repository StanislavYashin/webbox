#pragma once

#include <QtWidgets>
#include "Config.h"
#include "Common.h"
 
#include "RankingWidget.h"

class AppStoreRankingWidget : public QWidget
{
	Q_OBJECT

public:
	AppStoreRankingWidget(QWidget *parent = 0);
	virtual ~AppStoreRankingWidget();

	RankingWidget *contentWidget;
};