#ifndef POLARAREACHARTCANVAS_H
#define POLARAREACHARTCANVAS_H

#include "piechartcanvas.h"
#include "chartaxis.h"

class PolarAreaChartCanvas : public PieChartCanvas
{
    Q_OBJECT
public:
    PolarAreaChartCanvas(QQuickItem *parent = 0);

    Q_PROPERTY(ChartAxis *axis READ axis)
    ChartAxis *axis() const;

private:
    void paint(QPainter *painter);
    ChartAxis *pAxis;

signals:

public slots:

};

#endif // POLARAREACHARTCANVAS_H
