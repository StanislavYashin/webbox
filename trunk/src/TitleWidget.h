#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include "AeroButton.h"
#include <QWidget>
#include <QLabel>
#include <QtWidgets>
#include "BaseStyleWidget.h"
#include "Common.h"
#include "ToolButton.h"

class TitleWidget : public BaseStyleWidget
{
Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);

    void setTitle(QString title);
 
	AeroButton* createToolButton(QString iconPath, QString buttonText);

signals:

	void __turnPage(int current_page); 

public slots:

	void TurnPage(int current_page);

private:

	_private(QList<AeroButton*>,aerobtn_list)

    //_public(QList<ToolButton*>,ToolButtonList)

/*DATA*/
    _private(QLabel*,Title)
};

#endif // TITLEWIDGET_H
