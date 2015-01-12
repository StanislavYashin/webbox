#pragma once

#include <QtWidgets>

#include "Common.h"
#include "Config.h"

#include "RankingWidget.h"

class GameRankingWidget : public QWidget
{
	Q_OBJECT
public:
	GameRankingWidget(QWidget *parent = 0);
	virtual ~GameRankingWidget(); 

	RankingWidget *contentWidget;
};