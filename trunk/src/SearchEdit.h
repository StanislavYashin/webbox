#ifndef SEARCHEDIT_H
#define SEARCHEDIT_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>

#include "clearlabel.h"

#define SE_RECT_RADIUS 15
#define SE_EDIT_HEIGHT 15
#define SE_HEIGHT 21
#define SE_PEN_WIDTH 3
#define SE_LEFT_SPACE 10
#define SE_WIDGET_SPACE 3
#define SE_TOP 3

#define SE_BG_BRUSH_COLOR Qt::white
#define SE_BG_PEN_COLOR QColor(0,139,209)


class SearchEdit : public QWidget
{
    Q_OBJECT
public:
    explicit SearchEdit(QWidget *parent = 0);

public:
    /*!
      public interfaces
    */
    void setText(const QString& str);

    void clear();

    QString text() const;
protected:
    void resizeEvent(QResizeEvent *);

    void paintEvent(QPaintEvent *);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    QSize sizeHint() const
    {
        return QSize(300,40);
    }

private:
    void drawBackground(QPainter* paitner);

private:
    void calcGeo();
    void initVariables();
    void initWidgets();

private:
    QLabel* m_searchLabel;
    ClearLabel* m_clearLabel;
    QLineEdit* m_searchEdit;

    bool m_bEnter;

private Q_SLOTS:
    void HandleTextChanged(const QString& str);
    void ClearText();

Q_SIGNALS:
    void textChanged(const QString& str);



};

#endif // SEARCHEDIT_H
