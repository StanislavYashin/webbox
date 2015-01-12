#pragma once

#include "Config.h"
#include "Common.h"

#include <QtWidgets>

#include "RankingLabel.h"

class RankingWidget : public QWidget
{
	Q_OBJECT
public:

	RankingWidget(QWidget *parent = 0);
	virtual ~RankingWidget();

	void addItem(RankingLabel *label);

	QVBoxLayout *main_layout;

};