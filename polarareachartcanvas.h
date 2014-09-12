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
    Q_PROPERTY(bool axisAboveChart READ axisAboveChart WRITE setAxisAboveChart NOTIFY axisAboveChartChanged)

    bool axisAboveChart() const;
    void setAxisAboveChart(bool value);
    ChartAxis *axis() const;

protected:
    void paint(QPainter *painter) override;
    void hoverMoveEvent(QHoverEvent * event) override;
    void sliceChanged() override;
    void drawAxis(QPainter *painter, QPointF &center);

    ChartAxis *pAxis;
    bool pAxisAboveChart;

    double maxDataValue, minDataValue;
    int numberOfEnabledSlices;

signals:
    void axisAboveChartChanged();

private slots:

};

#endif // POLARAREACHARTCANVAS_H
