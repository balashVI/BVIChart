#ifndef POLARAREACHART_H
#define POLARAREACHART_H

#include "abstractchart.h"
#include "chartpen.h"
#include "polararea.h"
#include "polarraxis.h"

class PolarAreaChart : public AbstractChart
{
    Q_OBJECT
public:
    explicit PolarAreaChart(QQuickPaintedItem *parent = 0);

    Q_PROPERTY(QQmlListProperty<PolarArea> polarAreas READ polarAreas NOTIFY polarAreasChanged())
    QQmlListProperty<PolarArea> polarAreas();

    Q_PROPERTY(double angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)

    ///Містить налаштування лінії обведення
    Q_PROPERTY(ChartPen* strokePen READ strokePen WRITE setStrokePen NOTIFY strokePenChanged)

    ///Містить вісь R
    Q_PROPERTY(PolarRAxis* axis READ axis NOTIFY axisChanged)
    PolarRAxis* axis();

    ChartPen* strokePen() const;
    void setStrokePen(ChartPen* value);

    double angleOffset() const;
    void setAngleOffset(double value);

protected:
    static void appendPolarArea(QQmlListProperty<PolarArea> *polarAreasList, PolarArea *polarArea);
    static int polarAreasListLength(QQmlListProperty<PolarArea> *polarAreasList);
    static PolarArea *polarAreaAt(QQmlListProperty<PolarArea> *polarAreasList, int index);
    QList<PolarArea *> polarAreasList;
    void paint(QPainter *painter) override;

private:
    double pAngleOffset;
    double sumSliceValue;
    ChartPen *pStrokePen;
    double upperValue, loverValue;
    PolarRAxis pAxis;

signals:
    void polarAreasChanged();
    void angleOffsetChanged();
    void strokePenChanged();
    void axisChanged();

public slots:
    void calculateDataRange();
};

#endif // POLARAREACHART_H
