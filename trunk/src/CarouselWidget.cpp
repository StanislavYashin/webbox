#include "CarouselWidget.h"
#include "Config.h"

CarouselWidget::CarouselWidget(int w,int h,int page_cnt,int btn_cnt,int page_move,QWidget *parent)
	:QWidget(parent)
{
	label_array = new CLabel*[page_cnt+1];
 
	mouse_press = false;
	mouse_move = false;
	current_index = 0;
	current_pos_x = 0;

	m_page_move = page_move; 
	m_width = w;
	m_height = h;
	m_page_cnt = page_cnt;
	m_btn_cnt = btn_cnt;

	this->setFixedSize(w, h);
	setWindowFlags(Qt::FramelessWindowHint);

	background_label = new QLabel(this);
	background_label->setPixmap(QPixmap(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover0.jpg"));
	background_label->setGeometry(QRect(0, 0, this->width(), this->height()));

	//将4张图片合成一张
	QPixmap pixmap(QSize(this->width()*page_cnt, h));
	QPainter painter(&pixmap);
	for (int i = 0; i < page_cnt; i++)
	{
		painter.drawImage(QRect(w*i, 0, w, h),
			QImage(QString(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover%1.jpg").arg(i)));
	}

	total_label = new QLabel(this);
	total_label->resize(pixmap.size());
	total_label->setPixmap(pixmap);
	total_label->move(0, 0);

	close_button = new PushButton(this);

	for (int i = 0; i < btn_cnt; i++)
	{
		CLabel *label = new CLabel(this);
		//label = new CLabel(this);
		label->resize(QSize(155, 50));
		label->setTextColor(QColor(255, 255, 255, 255));
		label->setFont(ProfileInstance().AppFont);
		label->setPixmap(QPixmap(QString(Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/cover/Cover%1.jpg").arg(i)));
		label->move(8 + i * 170, 340);
		connect(label, SIGNAL(signalLabelPress(CLabel*)), this, SLOT(changeCurrentPage(CLabel*)));
		label_array[i] = label;
		
	}

	label_array[0]->setMousePressFlag(true);

	close_button->setPicName(":/sysButton/close");
	close_button->move(this->width() - close_button->width() - 5, 0);

	connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));

	this->translateLanguage();
}

CarouselWidget::~CarouselWidget()
{
	for (int i = 0; i < m_page_cnt; i++)
	{
		delete label_array[i];
	}
	delete total_label;

	delete close_button;
	delete background_label;
}

void CarouselWidget::translateLanguage()
{
	label_array[0]->setText(QString::fromUtf8("1"));
	label_array[1]->setText(QString::fromUtf8("2"));  
	label_array[2]->setText(QString::fromUtf8("3"));  
	label_array[3]->setText(QString::fromUtf8("4"));  

	close_button->setToolTip(tr("close"));
}

void CarouselWidget::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_mouseSrcPos = e->pos();
		if (m_mouseSrcPos.y() <= 40)
		{
			mouse_move = true;
		}
		else
		{
			current_pos_x = total_label->x();
			mouse_press = true;
		}
	}
	else if (e->button() == Qt::RightButton)
	{
		if (label_move)
		{
			if (current_index > 0)
			{
				current_index--;
				moveCurrentPage(false); //右移
			}
		}
	}
}

void CarouselWidget::mouseReleaseEvent(QMouseEvent *e)
{
	int xpos = 0;

	if (mouse_press)
	{
		if (label_move)
		{
			m_mouseDstPos = e->pos();

			xpos = m_mouseDstPos.x() - m_mouseSrcPos.x();

			if (xpos > 0)//右移
			{
				if (xpos >= m_width/m_page_cnt)
				{
					if (current_index > 0)
					{
						current_index--;
						moveCurrentPage(false); //右移
					}
					else
					{
						moveCurrentPage(true); //左移
					}
				}
				else
				{
					moveCurrentPage(true); //左移
				}
			}
			else //左移
			{
				if (xpos <= -m_width / m_page_cnt)
				{
					if (current_index < m_page_cnt - 1)
					{
						current_index++;
						moveCurrentPage(true); //左移
					}
					else
					{
						moveCurrentPage(false); //右移
					}
				}
				else
				{
					moveCurrentPage(false); //右移
				}
			}

			mouse_press = false;
		}
	}
	else if (mouse_move)
	{
		mouse_move = false;
	}
}

void CarouselWidget::mouseMoveEvent(QMouseEvent *e)
{
	int x = 0;
	if (mouse_press)
	{
		if (label_move)
		{
			m_mouseDstPos = e->pos();
			x = m_mouseDstPos.x() - m_mouseSrcPos.x();

			setLabelMove(false);
			total_label->move(current_pos_x + x, 0);
			setLabelMove(true);
		}
	}
	else if (mouse_move)
	{
		m_mouseDstPos = e->pos();
		this->move(this->pos() + m_mouseDstPos - m_mouseSrcPos);
	}
}

void CarouselWidget::keyPressEvent(QKeyEvent *e)
{
	if (label_move)
	{
		switch (e->key())
		{
		case Qt::Key_Left:
		case Qt::Key_Up:
			if (current_index > 0)
			{
				current_index--;
				moveCurrentPage(false); //右移
			}
			break;

		case Qt::Key_Right:
		case Qt::Key_Down:
			if (current_index < m_page_cnt - 1)
			{
				current_index++;
				moveCurrentPage(true); //左移
			}
			break;

		default:
			break;
		}
	}
}

void CarouselWidget::changeCurrentPage(CLabel *label)
{
	for (int i = 0; i<m_btn_cnt; i++)
	{
		if (label != label_array[i])
		{
			label_array[i]->setMousePressFlag(false);
		}
	}

	//获取点击的图标下标
	int index = 0;
	for (int i = 0; i<m_page_cnt; i++)
	{
		if (label == label_array[i])
		{
			index = i;
			break;
		}
	}

	//若下标小于当前下标右移，否则左移
	if (index < current_index)
	{
		while (index != current_index)
		{
			current_index--;
			moveCurrentPage(false);
		}
	}
	else if (index > current_index)
	{
		while (index != current_index)
		{
			current_index++;
			moveCurrentPage(true);
		}
	}
}

void CarouselWidget::changeCurrentButton()
{
	for (int i = 0; i<m_btn_cnt; i++)
	{
		if (i != current_index)
		{
			label_array[i]->setMousePressFlag(false);
		}
		else
		{
			label_array[i]->setMousePressFlag(true);
		}
	}
}

inline void CarouselWidget::setLabelMove(bool enable)
{
	label_move = enable;
}

void CarouselWidget::moveCurrentPage(bool direction)
{
	//改变当前页面对应的按钮
	changeCurrentButton();

	//图片的几个分割点
	//0-680, 680-1360, 1360-2040, 2040-2720
	//真:向左移;  假:向右移

	//左移的几种可能性,对于x坐标
	//index=0, 将label移动到-680*0
	//index=1, 将label移动到-680*1
	//index=2, 将label移动到-680*2
	//index=3, 将label移动到-680*3
	setLabelMove(false);
	int current_pos_x = total_label->x(); //当前label坐标
	int dest_pos_x = -m_width * current_index; //目标X坐标
	if (direction)
	{
		while (current_pos_x > dest_pos_x)
		{
			total_label->move(current_pos_x - m_page_move, 0);
			current_pos_x = total_label->x();
			qApp->processEvents(QEventLoop::AllEvents);
		}
	}
	else
	{
		while (current_pos_x < dest_pos_x)
		{
			total_label->move(current_pos_x + m_page_move, 0);
			current_pos_x = total_label->x();
			qApp->processEvents(QEventLoop::AllEvents);
		}
	}

	total_label->move(dest_pos_x, 0);
	setLabelMove(true);
}