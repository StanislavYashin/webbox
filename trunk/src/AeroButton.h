#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "AeroButton.define.h"
#include "Config.h"

class AeroButton : public QPushButton
{
	Q_OBJECT

public:

	static QMap<int,QList<AeroButton*>> buttonList;

	static QMap<int, AeroButton*> activeGroup;
	 
public:
	
	AeroButton(int groupid,const QColor &textColor, QWidget* parent = 0, eIconPosition pos = eIconPosition::IP_LEFT);
	//AeroButton(const QString & text, QWidget * parent = 0, eIconPosition pos = eIconPosition::IP_LEFT);
	//AeroButton(const QIcon & icon, const QString & text, QWidget * parent = 0, eIconPosition pos = eIconPosition::IP_LEFT);

	virtual ~AeroButton();

	void setColor(QColor color) { m_color = color;  }
	void setHighlight(QColor highlight) { m_highlight = highlight; }
	void setShadow(QColor shadow) { m_shadow = shadow; }

	//Range: 0.0 [invisible] - 1.0 [opaque]
	void setOpacity(qreal opacity) { m_opacity = opacity; }

	//Range: 0 [rectangle] - 99 [oval]
	void setRoundness(int roundness) { m_roundness = roundness; }

	void setIconPosition(eIconPosition eIconPosition) { m_icon_position = eIconPosition; }

	void setButtonIcon(QString icon)
	{ 
		int min_len = this->height() > this->width() ? this->width() : this->height();

		QPixmap pixmap = QPixmap(icon).scaled(min_len - 16, min_len - 16, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
		
		m_icon->setPixmap(pixmap); 
	}

	void setPressed(bool is_pressed){ m_pressed = is_pressed; this->repaint(); }

	int findGroup(AeroButton*) ;

	void setButtonText(QString text) {  m_text = text; m_title->setText(text); }

	void EnableGlow()
	{ 
		m_title->setGraphicsEffect(Profile::generateGlowEffect(QColor(255, 255, 255), 5)); 
	}

	void setTextColor(QColor color){
		m_textColor = color; 
		QPalette p; p.setBrush(QPalette::ButtonText, QBrush(color)); 
		m_title->setPalette(p); 
		this->setPalette(p);
	}

	void setTextFont(const QFont &font)
	{
		m_title->setFont(font);
	}

protected:

	void paintEvent(QPaintEvent * pe);

	void enterEvent(QEvent * e);
	
	void leaveEvent(QEvent * e);

	void mousePressEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);

private:

	QRect calculateIconPosition(QRect button_rect, QSize icon_size);

	QRect calculateTextPosition(QRect button_rect, int Offset);

private:

	bool m_hovered;
	bool m_pressed;

	QColor m_color;
	QColor m_highlight;
	QColor m_shadow;
	QColor m_normal;

	qreal m_opacity;

	int m_roundness;

	eIconPosition m_icon_position;

	QString m_text;

	QGridLayout *main_layout;
	QColor m_textColor;
	QLabel *m_title;
	QLabel *m_icon;
};
