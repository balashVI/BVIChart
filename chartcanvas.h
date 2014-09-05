#ifndef CHARTCANVAS_H
#define CHARTCANVAS_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QtMath>
#include "chartpopup.h"

class ChartCanvas : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ChartCanvas(QQuickItem *parent = 0);

    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY paddingChanged)
    int padding() const;
    void setPadding(int value);

    Q_PROPERTY(bool pausePainting READ pausePainting WRITE setPausePainting NOTIFY pausePaintingChanged)
    bool pausePainting() const;
    void setPausePainting(bool value);

    Q_PROPERTY(bool hoverEventsEnabled READ hoverEventsEnabled WRITE setHoverEventsEnabled NOTIFY hoverEventsEnabledChanged)
    bool hoverEventsEnabled() const;
    void setHoverEventsEnabled(bool value);

    Q_PROPERTY(ChartPopup *popup READ popup)
    ChartPopup* popup() const;

protected:
    void paint(QPainter *painter);
    double pi;

    int pPadding;
    bool pPausePainting;
    bool pHoverEventsEnabled;
    ChartPopup *pPopup;

signals:
    void paddingChanged();
    void pausePaintingChanged();
    void hoverEventsEnabledChanged();

public slots:

};

#endif // CHARTCANVAS_H
