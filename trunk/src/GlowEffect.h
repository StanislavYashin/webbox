 #pragma once

#include <QtWidgets>
#include <QtCore>

class GlowEffectPrivate;

/// @brief 发光效果的QGraphicsEffect
/// @par 示例:
/// @code
/// GlowEffect *effect = new GlowEffect(this);
/// effect->setRadius(5);
/// effect->setGlowColor(Qt::blue);
/// lbl->setGraphicsEffect(effect);
/// @endcode
/// @see setLogFile
class GlowEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    GlowEffect(QObject *parent = 0);
    virtual ~GlowEffect();

    void setRadius(int radius);

    void setGlowColor(const QColor &color);
    virtual QRectF boundingRectFor(const QRectF &sourceRect) const;
protected:
    virtual void draw(QPainter *painter);
    virtual void sourceChanged(ChangeFlags flags);

private:
    Q_DISABLE_COPY(GlowEffect)
    Q_DECLARE_PRIVATE(GlowEffect)
    GlowEffectPrivate* const d_ptr;
}; 