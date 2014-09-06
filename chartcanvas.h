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
    Q_PROPERTY(bool pausePainting READ pausePainting WRITE setPausePainting NOTIFY pausePaintingChanged)
    Q_PROPERTY(bool hoverEventsEnabled READ hoverEventsEnabled WRITE setHoverEventsEnabled NOTIFY hoverEventsEnabledChanged)
    Q_PROPERTY(ChartPopup *popup READ popup)

    int padding() const;
    void setPadding(int value);
    bool pausePainting() const;
    void setPausePainting(bool value);
    bool hoverEventsEnabled() const;
    void setHoverEventsEnabled(bool value);
    ChartPopup* popup() const;

protected:
    ChartPopup *pPopup;
    double pi;
    int pPadding;
    bool pPausePainting;
    bool pHoverEventsEnabled;


signals:
    void paddingChanged();
    void pausePaintingChanged();
    void hoverEventsEnabledChanged();

public slots:

};

#endif // CHARTCANVAS_H
