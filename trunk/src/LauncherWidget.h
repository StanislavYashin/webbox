#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QtWidgets>
#include "DockWidget.h"
#include "Common.h"
#include "BaseStyleWidget.h"
#include "ToolButton.h"
#include "LaunchProperty.hpp"

class LauncherWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = 0);
	virtual ~LauncherWidget();
	 
	ToolButton* addToolButton(int w, int h, Webbox::Data::LaunchProperty *_p);

signals:

public slots:
	void __onItemClicked(int icoIndex);

private:
	_private(DockWidget*, dockWidget)
};

#endif // LAUNCHERWIDGET_H
