#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QWidget>

class SlideShowPrivate;

class SlideShow : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(int slideInterval READ slideInterval WRITE setSlideInterval)

public:
	SlideShow(QWidget* parent = 0);
	~SlideShow();
	void addImage(QString filename);
	void addImageDir(QString dirName);
	void clearImages();
	void startShow();
	void stopShow();


	int slideInterval();
	void setSlideInterval(int val);

signals:
	void inputReceived();

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void timerEvent(QTimerEvent* event);
	void showEvent(QShowEvent * event);


private:
	SlideShowPrivate* d;
};

#endif