 
#ifndef QXTFLOWVIEW_P_H_INCLUDED
#define QXTFLOWVIEW_P_H_INCLUDED


#include "FlowView.h"

#define PICTUREFLOW_QT4

#include <QtWidgets/QApplication>
#include <QCache>
#include <QHash>
#include <QImage>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QtWidgets/QWidget>
#include <QAbstractItemModel>
#include <QPersistentModelIndex>
#include <QList>

// for fixed-point arithmetic, we need minimum 32-bit long
// long long (64-bit) might be useful for multiplication and division
typedef long PFreal;
#define PFREAL_SHIFT 10
#define PFREAL_ONE (1 << PFREAL_SHIFT)

#define IANGLE_MAX 1024
#define IANGLE_MASK 1023

#define BILINEAR_STRETCH_HOR 4
#define BILINEAR_STRETCH_VER 4

inline PFreal fmul(PFreal a, PFreal b)
{
	return ((long long)(a))*((long long)(b)) >> PFREAL_SHIFT;
}

inline PFreal fdiv(PFreal num, PFreal den)
{
	long long p = (long long)(num) << (PFREAL_SHIFT * 2);
	long long q = p / (long long)den;
	long long r = q >> PFREAL_SHIFT;

	return r;
}

inline PFreal fsin(int iangle)
{
	// warning: regenerate the table if IANGLE_MAX and PFREAL_SHIFT are changed!
	static const PFreal tab[] =
	{
		3, 103, 202, 300, 394, 485, 571, 652,
		726, 793, 853, 904, 947, 980, 1004, 1019,
		1023, 1018, 1003, 978, 944, 901, 849, 789,
		721, 647, 566, 479, 388, 294, 196, 97,
		-4, -104, -203, -301, -395, -486, -572, -653,
		-727, -794, -854, -905, -948, -981, -1005, -1020,
		-1024, -1019, -1004, -979, -945, -902, -850, -790,
		-722, -648, -567, -480, -389, -295, -197, -98,
		3
	};

	while (iangle < 0)
		iangle += IANGLE_MAX;
	iangle &= IANGLE_MASK;

	int i = (iangle >> 4);
	PFreal p = tab[i];
	PFreal q = tab[(i + 1)];
	PFreal g = (q - p);
	return p + g * (iangle - i * 16) / 16;
}

inline PFreal fcos(int iangle)
{
	return fsin(iangle + (IANGLE_MAX >> 2));
}

/* ----------------------------------------------------------

QxtFlowViewState stores the state of all slides, i.e. all the necessary
information to be able to render them.

QxtFlowViewAnimator is responsible to move the slides during the
transition between slides, to achieve the effect similar to Cover Flow,
by changing the state.

QxtFlowViewSoftwareRenderer (or QxtFlowViewOpenGLRenderer) is
the actual 3-d renderer. It should render all slides given the state
(an instance of QxtFlowViewState).

Instances of all the above three classes are stored in
QxtFlowViewPrivate.

------------------------------------------------------- */

struct SlideInfo
{
	int slideIndex;
	int angle;
	PFreal cx;
	PFreal cy;
	int blend;
};

class QxtFlowViewState
{
public:
	QxtFlowViewState();
	~QxtFlowViewState();

	void reposition();
	void reset(); 
	 
	QRgb backgroundColor;
	int slideWidth;
	int slideHeight;
	QxtFlowView::ReflectionEffect reflectionEffect;
	QVector<QImage*> slideImages;

	int angle;
	int spacing;
	PFreal offsetX;
	PFreal offsetY;

	SlideInfo centerSlide;
	QVector<SlideInfo> leftSlides;
	QVector<SlideInfo> rightSlides;
	int centerIndex;
};

class QxtFlowViewAnimator
{
public:
	QxtFlowViewAnimator();
	QxtFlowViewState* state;

	void start(int slide);
	void stop(int slide);
	void update();

	int target;
	int step;
	int frame;
	QTimer animateTimer;
};

class QxtFlowViewAbstractRenderer
{
public:
	QxtFlowViewAbstractRenderer() : state(0), dirty(false), widget(0) {}
	virtual ~QxtFlowViewAbstractRenderer() {}

	QxtFlowViewState* state;
	bool dirty;
	QWidget* widget;

	virtual void init() = 0;
	virtual void paint() = 0;
};

class QxtFlowViewSoftwareRenderer : public QxtFlowViewAbstractRenderer
{
public:
	QxtFlowViewSoftwareRenderer();
	~QxtFlowViewSoftwareRenderer();

	virtual void init();
	virtual void paint();

private:
	QSize size;
	QRgb bgcolor;
	int effect;
	QImage buffer;
	QVector<PFreal> rays;
	QImage* blankSurface;
#ifdef PICTUREFLOW_QT4
	QCache<int, QImage> surfaceCache;
	QHash<int, QImage*> imageHash;
#endif
#ifdef PICTUREFLOW_QT3
	QCache<QImage> surfaceCache;
	QMap<int, QImage*> imageHash;
#endif
#ifdef PICTUREFLOW_QT2
	QCache<QImage> surfaceCache;
	QIntDict<QImage> imageHash;
#endif

	void render();
	void renderSlides();
	QRect renderSlide(const SlideInfo &slide, int col1 = -1, int col2 = -1);
	QImage* surface(int slideIndex);
};



// -----------------------------------------

class QxtFlowViewPrivate : public QObject
{
	Q_OBJECT
public:
	QxtFlowViewState* state;
	QxtFlowViewAnimator* animator;
	QxtFlowViewAbstractRenderer* renderer;
	QTimer triggerTimer;
	QAbstractItemModel * model;
	void setModel(QAbstractItemModel * model);
	void clear();
	void triggerRender();
	void insertSlide(int index, const QImage& image);
	void replaceSlide(int index, const QImage& image);
	void removeSlide(int index);
	void setCurrentIndex(QModelIndex index);
	void showSlide(int index);

	int picrole;
	int textrole;
	int piccolumn;
	int textcolumn;

	void reset();

	QList<QPersistentModelIndex> modelmap;
	QPersistentModelIndex currentcenter;

	QPoint lastgrabpos;
	QModelIndex rootindex;

	public Q_SLOTS:
	void columnsAboutToBeInserted(const QModelIndex & parent, int start, int end);
	void columnsAboutToBeRemoved(const QModelIndex & parent, int start, int end);
	void columnsInserted(const QModelIndex & parent, int start, int end);
	void columnsRemoved(const QModelIndex & parent, int start, int end);
	void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
	void headerDataChanged(Qt::Orientation orientation, int first, int last);
	void layoutAboutToBeChanged();
	void layoutChanged();
	void modelAboutToBeReset();
	void modelReset();
	void rowsAboutToBeInserted(const QModelIndex & parent, int start, int end);
	void rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end);
	void rowsInserted(const QModelIndex & parent, int start, int end);
	void rowsRemoved(const QModelIndex & parent, int start, int end);
};


#endif // QXTFLOWVIEW_P_H_INCLUDED
