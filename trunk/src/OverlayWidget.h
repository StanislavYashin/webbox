#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QGraphicsBlurEffect>

#ifndef Q_DECL_OVERRIDE
#define Q_DECL_OVERRIDE override
#endif

class OverlayWidget : public QWidget
{
	void newParent() 
	{
		if (!parent()) return;
		parent()->installEventFilter(this);
		raise();
	}
public:
	explicit OverlayWidget(QWidget * parent = 0) : QWidget(parent) 
	{
		setAttribute(Qt::WA_NoSystemBackground);
		newParent();
	}
protected:
	//! Catches resize and child events from the parent widget
	bool eventFilter(QObject * obj, QEvent * ev) Q_DECL_OVERRIDE
	{
		if (obj == parent()) 
		{
			if (ev->type() == QEvent::Resize) 
			{
				QResizeEvent * rev = static_cast<QResizeEvent*>(ev);
				this->resize(rev->size());
			}
			else if (ev->type() == QEvent::ChildAdded) 
			{
				raise();
			}
		}
		return QWidget::eventFilter(obj, ev);
	}
		//! Tracks parent widget changes
		bool event(QEvent* ev) Q_DECL_OVERRIDE{
		if (ev->type() == QEvent::ParentAboutToChange) 
		{
			if (parent()) parent()->removeEventFilter(this);
		}
		else if (ev->type() == QEvent::ParentChange) 
		{
			newParent();
		}
		return QWidget::event(ev);
	}
};