#pragma once 

#include <QtWidgets>

#include "Common.h"
#include "Config.h"

class StarRatingWidget : public QWidget
{
	Q_OBJECT

public:
	StarRatingWidget(QWidget *parent = 0);
	virtual ~StarRatingWidget();


};