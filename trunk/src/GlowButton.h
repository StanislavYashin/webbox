#pragma once

#include <QtWidgets>
#include "Config.h"
#include "GlowButton.define.h"

class GlowButton : public QWidget 
{
	Q_OBJECT

public:

	explicit GlowButton(int w, int h, bool isExtraMode, QString photo_path, QString text, const QColor &bkColor,const QColor &glowColor, QWidget *parent = 0);
	~GlowButton();

	void setGlowColor(const QColor &);
	void setBackColor(const QColor &);
	void setFont(QFont &); 
	void setTextColor(const QColor &color);
	void setPixmap(const QPixmap &pixmap);
	void setTitle(QString text);
	void setMouseEnterFlag(bool);
	void setMousePressFlag(bool); 
	void setTransition(bool bEnabled);
	void setIsBackgroundTransparent(bool bIsTransparent);
	void setIsExtraEnabled(bool enable);
	void setMode(eGlowButtonMode mode);
	void setGroupId(int id);
	void setPressed(bool is_pressed);
	void check();
	int findGroup(GlowButton *button);

signals:

	void glowButtonClicked(GlowButton *);

protected:

	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *); 
	virtual void paintEvent(QPaintEvent *);
	 
private:

	QLabel *m_title;
	QLabel *m_icon; 

private: 

	static QMap<int, QList<GlowButton*>> buttonList;
	static QMap<int, GlowButton*> activeGroup;

	QColor m_color; 
	QColor m_backColor;
	//void createFrame();
	  
	void paintWidget(int transparency, QPainter *device, int roundRadius = 0);
	bool getMouseEnterFlag();
	bool getMousePressFlag();

	bool m_showExtraIcon; 
	bool m_mouseEnterFlag;
	bool m_mousePressFlag;
	bool m_bIsBkgTransparent;
	bool m_bEnableTransition;
	bool m_bCheckMode;

	eGlowButtonMode m_mode;
};