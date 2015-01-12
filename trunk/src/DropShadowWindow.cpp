#include "DropShadowWindow.h" 
#include "ImageUtil.h"
#include "gloweffect.h"

DropShadowWindow::DropShadowWindow(QWidget *parent)
	: BaseStyleWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setAttribute(Qt::WA_TranslucentBackground); 
	initializeWindow();
}

DropShadowWindow::~DropShadowWindow()
{

}
  
void DropShadowWindow::showWindow()
{
	this->showNormal();
	this->raise();
	this->activateWindow();
}

void DropShadowWindow::initializeWindow()
{ 
	this->m_Dir = NONE; 
	this->setMouseTracking(true); 
	m_LeftMouseDown = false;

	m_Title = new QLabel(); 
}

void DropShadowWindow::changeTheme()
{
	if (m_BackgroundImageURL == NULL)
		return;

	switch (m_BackgroundMode)
	{
	case eBKMode::BKNOTILESTRETCH:
	{
		this->setStyleSheet(QString(css_bk_notilestretch).arg(m_BackgroundImageURL));

	} break;
	case eBKMode::BKSTRETCH:
	{
		this->setStyleSheet(QString(css_bk_stretch_round).arg(m_BackgroundImageURL));

	} break;
	case eBKMode::BKTILE:
	{
		this->setStyleSheet(QString(css_bk_tile).arg(m_BackgroundImageURL));

	} break;
	case eBKMode::CUSTOMSTRETCH:
	{ 
	} break;
	case eBKMode::CUSTOMTILE:
	{  
		QPalette *palette = new QPalette();
		palette->setBrush(QPalette::Background, QBrush(*m_BackgroundImage));
		setPalette(*palette);
	} break;
	default:
		break;
	}

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
	effect->setBlurRadius(SHADOW_WIDTH);
	effect->setOffset(0);
	effect->setColor(QColor(0, 0, 0));
	this->setGraphicsEffect(effect);
}

void DropShadowWindow::setBackground(eBKMode bkMode, QString bkImageURL)
{
	m_BackgroundMode = bkMode;
	m_BackgroundImageURL = bkImageURL;
	m_BackgroundImage = new QPixmap(bkImageURL);

	QImage *img = new QImage(bkImageURL);
	//QImage img = QImage(bkImageURL);
	//m_Img = get_blurred_image(*img, img->rect(), 2, false);
	m_Img = get_blurred_image(*img, img->rect(), 2, false);
	//qt_blurImage(*img, 50, true,false);
 
	changeTheme();
}

void DropShadowWindow::setBackgroundMode(eBKMode mode)
{
	m_BackgroundMode = mode; 
	changeTheme(); 
}

void DropShadowWindow::setBackgroundImageURL(QString url)
{
	m_BackgroundImageURL = url;
	m_BackgroundImage = new QPixmap(url);
	m_Img = new QImage(url);

	changeTheme();
}

void DropShadowWindow::_drawWindowShadow(QPainter &painter)
{ 
	QList<QPixmap> pixmaps;
	pixmaps.append(QPixmap(":/image/shadow/shadow_left"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_right"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_top"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_bottom"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_left_top"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_right_top"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_left_bottom"));
	pixmaps.append(QPixmap(":/image/shadow/shadow_right_bottom"));

	painter.drawPixmap(0, 0, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[4]);
	painter.drawPixmap(this->width() - SHADOW_WIDTH, 0, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[5]);
	painter.drawPixmap(0, this->height() - SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[6]);
	painter.drawPixmap(this->width() - SHADOW_WIDTH, this->height() - SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[7]);
	painter.drawPixmap(0, SHADOW_WIDTH, SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH, pixmaps[0].scaled(SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
	painter.drawPixmap(this->width() - SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH, pixmaps[1].scaled(SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
	painter.drawPixmap(SHADOW_WIDTH, 0, this->width() - 2 * SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[2].scaled(this->width() - 2 * SHADOW_WIDTH, SHADOW_WIDTH));
	painter.drawPixmap(SHADOW_WIDTH, this->height() - SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[3].scaled(this->width() - 2 * SHADOW_WIDTH, SHADOW_WIDTH));
}

void DropShadowWindow::paintEvent(QPaintEvent *event)
{ 
	BaseStyleWidget::paintEvent(event); 

    switch(m_BackgroundMode)
    {
	case eBKMode::PURECOLOR:
	{
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::black);
		painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
	}break;
	case eBKMode::CUSTOMSTRETCH:
	{ 
		if (m_BackgroundImage != NULL)
		{
			QPainter painter(this);
			painter.setPen(Qt::NoPen);
			painter.setBrush(Qt::white);
  
			painter.drawImage(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), *m_Img); 
			//this->_drawWindowShadow(painter);
		}
		else
		{
			QBitmap bitmap(this->size());
			QPainter painter(this);
			painter.setPen(Qt::NoPen);
			painter.setBrush(Qt::white);
			painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
		}
		
	} break;
	case eBKMode::CUSTOMTILE:
	{
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::white); 
		painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
		painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), *m_BackgroundImage);
		
	} break;
	case eBKMode::BKSTRETCH: 
	case eBKMode::BKTILE:  
	case eBKMode::BKNOTILESTRETCH:   
	{   
		//QPainter painter(this);
		//this->_drawWindowShadow(painter);  
	} break;
	case eBKMode::BKNONE:
	{
		QBitmap bitmap(this->size());
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::white);
		painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));

	} break;
    }
}

void DropShadowWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
   /* if (event->button() == Qt::LeftButton)
    {
        if(!m_bMaxWin)
        {
            m_rectRestoreWindow = geometry();
            setGeometry(qApp->desktop()->availableGeometry());
        }
        else
        {
            setGeometry(m_rectRestoreWindow);
        }
        m_bMaxWin = !m_bMaxWin;
    }*/
}

void DropShadowWindow::mousePressEvent(QMouseEvent *event)
{  
	switch (event->button()) 
	{
	case Qt::LeftButton:
		m_LeftMouseDown = true;
		if (m_Dir != NONE)
		{
			this->mouseGrabber();
		}
		else 
		{
			m_DragPosition = event->globalPos() - this->frameGeometry().topLeft();
		}
		break;
	case Qt::RightButton:
		this->close();
		break;
	default:
		BaseStyleWidget::mousePressEvent(event);
	} 
}

void DropShadowWindow::mouseReleaseEvent(QMouseEvent *event)
{  
	if (event->button() == Qt::LeftButton) 
	{
		m_LeftMouseDown = false;

		if (m_Dir != NONE)
		{
			m_Dir = eDirection::NONE;
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
}

//void DropShadowWindow::SetCursorStyle(Direction direction)
//{
//	Dir = direction;
//	//设置上下左右以及右上、右下、左上、坐下的鼠标形状
//	switch (direction)
//	{
//	case UP: 
//	case DOWN:
//		setCursor(Qt::SizeVerCursor);
//		break;
//	case RIGHT:
//	case LEFT:
//		setCursor(Qt::SizeHorCursor);
//		break;
//	case RIGHTTOP:
//	case LEFTBOTTOM:
//		setCursor(Qt::SizeBDiagCursor);
//		break;
//	case RIGHTBOTTOM:
//	case LEFTTOP:
//		setCursor(Qt::SizeFDiagCursor);
//		break;
//	default:
//		setCursor(Qt::ArrowCursor);
//		break;
//	}
//}

 
////确定点的位置方向
//Direction DropShadowWindow::PointValid(int nXRelative, int nYRelative)
//{
//	int nTop = qAbs(nYRelative)<PADDING ? UP : NONE;
//	int nRight = qAbs(nXRelative - rect().right())<PADDING ? RIGHT : NONE;
//	int nBottom = qAbs(nYRelative - rect().bottom())<PADDING ? DOWN : NONE;
//	int nLeft = qAbs(nXRelative)<PADDING ? LEFT : NONE;
//	return Direction(nTop + nRight + nBottom + nLeft);
//}

void DropShadowWindow::mouseMoveEvent(QMouseEvent *event)
{
	BaseStyleWidget::mouseMoveEvent(event);

	/*if (!LeftMouseDown)
	{
		Dir = PointValid(event->x(), event->y());
		SetCursorStyle(Dir);
	}
	else
	{
		int nXGlobal = event->globalX();
		int nYGlobal = event->globalY(); 
		SetDrayMove(nXGlobal, nYGlobal, Dir); 
		DragPosition = QPoint(nXGlobal, nYGlobal);
	}*/

	//移动窗口
	/*if (LeftMouseDown)
	{
		QPoint move_pos = event->globalPos(); 
		move(move_pos - MovePoint);
	}
	*/

	QPoint gloPoint = event->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (!m_LeftMouseDown)
	{
        this->__setCursorStyle(gloPoint);
	}
	else 
	{
		if (m_Dir != NONE) 
		{
			QRect rMove(tl, rb);

			switch (m_Dir) {
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:

				break;
			}
			this->setGeometry(rMove); 
		}
		else {
			move(event->globalPos() - m_DragPosition);
			event->accept();

			QPoint diff = event->pos() - m_DragPosition;
			QPoint newpos = this->pos() + diff; 
		}
	}
}

void DropShadowWindow::__setCursorStyle(const QPoint &cursorGlobalPoint)
{
	return;

	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());
	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
		// 左上角
		m_Dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		// 右下角
		m_Dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		//左下角
		m_Dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
		// 右上角
		m_Dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x()) {
		// 左边
		m_Dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING) {
		// 右边
		m_Dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING){
		// 上边
		m_Dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING) {
		// 下边
		m_Dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// 默认
		m_Dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

//void DropShadowWindow::SetDrayMove(int nXGlobal,int nYGlobal,Direction direction)
//{
//    //计算偏差
//	int ndX = nXGlobal - DragPosition.x();
//	int ndY = nYGlobal - DragPosition.y();
//    //获得主窗口位置信息
//    QRect rectWindow = geometry();
//    //判别方向
//    if(direction & Direction::UP)
//    {
//        rectWindow.setTop(rectWindow.top()+ndY);
//    }
//	if (direction & Direction::RIGHT)
//    {
//        rectWindow.setRight(rectWindow.right()+ndX);
//    }
//	if (direction & Direction::DOWN)
//    {
//        rectWindow.setBottom(rectWindow.bottom()+ndY);
//    }
//    if(direction & Direction::LEFT)
//    {
//        rectWindow.setLeft(rectWindow.left()+ndX);
//    }
//	if (rectWindow.width()< minimumWidth() || rectWindow.height()<minimumHeight())
//    {
//        return;
//    }
//    //重新设置窗口位置为新位置信息
//    setGeometry(rectWindow);
//} 