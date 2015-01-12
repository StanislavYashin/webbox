#pragma once
 
#include "Config.h"
#include "Common.h"

#include "CLabel.h"
#include "GlowButton.h"
#include "AppletWidget.h" 
#include "CommonProperty.hpp"
#include "BoxDocument.hpp"
#include "GridContentWidget.h"

class AppStorePageWidget : public QWidget
{
	Q_OBJECT 

public :

	explicit AppStorePageWidget(BoxDocument *doc,QWidget *parent = 0);
	GlowButton* createMenu(QSignalMapper *mapper, int id, QString iconPath, QString buttonText, bool extraMode = false);
	void loadProperties(QList<Webbox::Data::CommonProperty*> _properties);

	~AppStorePageWidget();

signals: 

public slots :

	void OnItemClicked();
	void OnCategoryChanged(int index);
	void OnBackward();
	void OnForward();
	void OnHome();

private:

	GlowButton *createToolButton(QString iconPath, QString buttonText); 

protected:
	
	GridContentWidget *grid_widget;
	QScrollArea *scrollArea;
	BoxDocument *_doc;

	QStackedWidget *stacked_widget;
	
	_private(QString, image_dir);

};