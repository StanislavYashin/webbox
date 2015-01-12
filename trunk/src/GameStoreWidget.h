#pragma once
 
#include <QtWidgets>
#include "GlowButton.h"
#include "Config.h"
#include "Common.h"
#include "GameStorePageWidget.h"
#include "GeneralDocument.hpp"

class GameStoreWidget : public QWidget
{
	Q_OBJECT
	
public:

	explicit GameStoreWidget(QWidget *parent = 0);
	
private:

	GlowButton* __createToolButton(QString iconPath, QString buttonText, bool extraMode=false);

signals:
	 
public slots :

	void switchPage(int);
	
public:

	QStackedWidget *stacked_widget;

	QList<GlowButton*> m_aerobtn_list;

	_private(QList<BannerButton*>, category_list); 
};