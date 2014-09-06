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

protected:
    void paint(QPainter *painter) override;
    void hoverMoveEvent(QHoverEvent * event) override;
    void sliceChanged() override;
    void paintAxis(QPainter *painter, QPointF &center, int maxRadius);
    ChartAxis *pAxis;

    double maxDataValue, minDataValue;
    int numberOfEnabledSlices;

signals:

private slots:

};

#endif // POLARAREACHARTCANVAS_H
