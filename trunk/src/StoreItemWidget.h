#pragma once 

#include <QtWidgets>
#include "Config.h"
 
class StoreItemWidget : public QWidget {
	Q_OBJECT
public:
	explicit StoreItemWidget(int w, int h, QString photo_path, QString text, const QColor &glowColor, QWidget *parent=0);
	~StoreItemWidget();

	void setColor(const QColor &);
	void setFont(QFont &);
	void setTextColor(const QColor &color);
	void setPixmap(const QPixmap &pixmap);
	void setTitle(QString text);
	void setMouseEnterFlag(bool);
	void setMousePressFlag(bool);
	void setTransition(bool bEnabled);
	void setIsBackgroundTransparent(bool bIsTransparent);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

	void painterInfo(int r, int g, int b, int top_color, int middle_color, int bottom_color);

private:

	QLabel *m_title;
	QLabel *m_icon;

signals:

	void signalLabelPress(StoreItemWidget *);

private:

	QColor m_color;

	//void createFrame();

	void paintWidget(int transparency, QPainter *device, int roundRadius = 0);
	bool getMouseEnterFlag();
	bool getMousePressFlag();

	bool m_mouseEnterFlag;
	bool m_mousePressFlag;
	bool m_bIsBkgTransparent;
	bool m_bEnableTransition;
};