#include "basestylewidget.h"
#include <QStyleOption>
#include <QPainter>

BaseStyleWidget::BaseStyleWidget(QWidget *parent) 
	: QDialog(parent)
{
}

void BaseStyleWidget::paintEvent(QPaintEvent *pe)
{ 
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseStyleWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() != Qt::Key_Escape)
		QDialog::keyPressEvent(event);
}
