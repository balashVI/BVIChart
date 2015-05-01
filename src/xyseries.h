#ifndef XYSERIES_H
#define XYSERIES_H

#include "abstractseries.h"
#include "chartpoint.h"

class XYSeries : public AbstractSeries
{
    Q_OBJECT
public:
    explicit XYSeries(QObject *parent = 0);
    ~XYSeries();

    Q_PROPERTY(QQmlListProperty<ChartPoint> data READ data NOTIFY dataChanged)
    QQmlListProperty<ChartPoint> data();

    Q_PROPERTY(ChartPen* strokePen READ strokePen WRITE setStrokePen NOTIFY strokePenChanged)
    ChartPen* strokePen() const;
    void setStrokePen(ChartPen* value);

    Q_PROPERTY(bool drawPoints READ drawPoints WRITE setDrawPoints NOTIFY drawPointsChanged)
    void setDrawPoints(bool value);
    bool drawPoints() const;

    void getDataRange(double &xLoverValue, double &xUpperValue, double &yLoverValue, double &yUpperValue);
    const QList<ChartPoint*>* getDataList();

protected:
    static void appendPoint(QQmlListProperty<ChartPoint> *dataList, ChartPoint *point);
    static int dataListLength(QQmlListProperty<ChartPoint> *dataList);
    static ChartPoint *pointAt(QQmlListProperty<ChartPoint> *dataList, int index);
    QList<ChartPoint *> dataList;
    ChartPen *pStrokePen;
    bool pDrawPoints;
    double xUpperValue, xLoverValue, yUpperValue, yLoverValue;

signals:
    void strokePenChanged();
    void drawPointsChanged();
    void dataChanged();

private slots:
    virtual void calculateDataRange();
};

#endif // XYSERIES_H
