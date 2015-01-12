#ifndef CLABEL_H
#define CLABEL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

class CLabel : public QWidget {
	Q_OBJECT 
public:

	explicit CLabel(QWidget *parent = 0);
	~CLabel();

	void setTextColor(const QColor &color);
	void setColor(const QColor &);
	void setPixmap(const QPixmap &);
	void setText(const QString &);
	void setMouseEnterFlag(bool);
	void setMousePressFlag(bool);
	void setFont(QFont &);
	void setTransition(bool bEnabled);
	void setIsBackgroundTransparent(bool bIsTransparent);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

signals:

	void signalLabelPress(CLabel *);

private:

	void initVariable();
	void initSetupUi();
	void createFrame();
	void createWidget();
	void createLayout(); 
	void paintWidget(int transparency, QPainter *device, int roundRadius = 0);
	bool getMouseEnterFlag();
	bool getMousePressFlag();

	bool m_mouseEnterFlag;
	bool m_mousePressFlag;

	QHBoxLayout *m_pHLayout;
	QLabel *m_pLabelIcon;
	QLabel *m_pLabelText;

	QColor m_color;

	bool m_bIsBkgTransparent;
	bool m_bEnableTransition;
};

#endif  
