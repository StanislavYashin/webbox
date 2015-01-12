#pragma once

#include <QtWidgets>

#include "Common.h"
#include "Config.h"

/*
 * Ç°½øºóÍË
 */

class NavControlWidget : public QWidget
{
	Q_OBJECT

public:

	explicit NavControlWidget(QWidget *parent = 0);
	virtual ~NavControlWidget();

public slots:
	void HandleEvent(int index);


signals:

	void OnHomeClicked(NavControlWidget *);
	void OnBackClicked(NavControlWidget *);
	void OnForwardClicked(NavControlWidget *);

public slots:

};