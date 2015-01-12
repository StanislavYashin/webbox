#include "ImageLabel.h"
#include <QtWidgets>

void ImageLabel::paintEvent(QPaintEvent *pe)
{
	QPainter painter(this);

	QStyleOption sopt;
	/*sopt.initFrom(this);
	if (sopt.state & QStyle::State_MouseOver)
	{
		painter.fillRect(this->rect(), m_colorHover);
	}
	else
	{
		painter.fillRect(this->rect(), m_colorNotHover);
	}*/
}