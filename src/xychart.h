#ifndef XYCHART_H
#define XYCHART_H

#include "barchart.h"
#include "xyseries.h"

class XYChart : public BarChart
{
    Q_OBJECT
public:
    explicit XYChart(QQuickPaintedItem *parent = 0);
    ~XYChart();

    Q_PROPERTY(QQmlListProperty<XYSeries> series READ series NOTIFY seriesChanged)
    QQmlListProperty<XYSeries> series();

protected:
    static void appendSeries(QQmlListProperty<XYSeries> *seriesList, XYSeries *series);
    static int seriesListLength(QQmlListProperty<XYSeries> *seriesList);
    static XYSeries *seriesAt(QQmlListProperty<XYSeries> *seriesList, int index);
    QList<XYSeries *> seriesList;

    StandartAxis pXAxis;

    void virtual paint(QPainter *painter) override;

private:
    double xUpperValue, xLoverValue, yUpperValue, yLoverValue;

signals:
    void seriesChanged();

protected slots:
    void calculateDataRange();
};

#endif // XYCHART_H
