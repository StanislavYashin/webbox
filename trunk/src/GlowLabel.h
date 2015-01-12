#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include "stdafx.h"

class GlowLabel : public QLabel
{

Q_OBJECT

/*METHODS*/
public:

    GlowLabel(QWidget* parent = 0);
    ~GlowLabel();

protected:

	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

private:


/*FIELDS*/ 
public:


protected:


private:


};
