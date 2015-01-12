#ifndef APPSTOREWIDGET_H
#define APPSTOREWIDGET_H

#include <QtWidgets>
#include "GlowButton.h"
#include "Common.h"
#include "Config.h"
#include <QBoxLayout>
#include "AppStorePageWidget.h"
#include "BoxDocument.hpp"
#include "CommonProperty.hpp"
#include "NavControlWidget.h"

class AppStoreWidget : public QWidget
{
    Q_OBJECT

public:

    explicit AppStoreWidget(QWidget *parent = 0);
	
	//void setNavigator(bool value);

private:
	 
	QList<GlowButton*> m_aerobtn_list;

	GlowButton* __createToolButton(QString iconPath, QString buttonText, bool extraMode = false);

signals:

public slots :

	void switchPage(int);

private:

	QStackedWidget *stackedWidget;

	BoxDocument *__doc;

	//NavControlWidget *navWidget;

	QHBoxLayout *mainLayout;
};

#endif 
