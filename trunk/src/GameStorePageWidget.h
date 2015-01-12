#pragma once

#include "Common.h"
#include "Config.h"
#include <QtWidgets> 
#include "AppletWidget.h"
#include "BannerButton.h"
#include "GeneralDocument.hpp"
#include "BoxDocument.hpp"
#include "GridContentWidget.h"
#include "GlowButton.h"

class GameStorePageWidget : public QWidget
{
	Q_OBJECT

public:

	explicit GameStorePageWidget(BoxDocument *doc,QWidget *parent = 0);
	~GameStorePageWidget();

	void loadProperties(QList<Webbox::Data::CommonProperty*> _properties);
	
	GlowButton* createToolButton(QSignalMapper *mapper, int id, QString iconPath, QString buttonText, bool extraMode = false);

signals:

public slots :

	void OnItemClicked();
	void OnCategoryChanged(int index);
	void OnBackward();
	void OnForward();
	void OnHome();

protected:

	GridContentWidget *grid_widget;
	QStackedWidget *stacked_widget;
	QScrollArea *scrollArea;
	BoxDocument *_doc;

	_private(QString, image_dir);
};