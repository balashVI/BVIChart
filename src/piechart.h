#ifndef PIECHART_H
#define PIECHART_H

#include "abstractchart.h"
#include "pieslice.h"

///
/// \brief Кругова діаграма
///
/// Малює кругову діаграму. Приклад використання:
/// \code
/// ...
/// PieChart{
///     anchors.fill: parent
///     series: [
///         PieSeries{
///         },
///         PieSeries{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class PieChart : public AbstractChart
{
    Q_OBJECT
public:
    explicit PieChart(QQuickPaintedItem *parent = 0);

    Q_PROPERTY(QQmlListProperty<PieSlice> slices READ slices NOTIFY slicesChanged())
    QQmlListProperty<PieSlice> slices();

    Q_PROPERTY(double angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)

    ///Містить налаштування лінії обведення
    Q_PROPERTY(ChartPen* strokePen READ strokePen WRITE setStrokePen NOTIFY strokePenChanged)


    ChartPen* strokePen() const;
    void setStrokePen(ChartPen* value);

    double angleOffset() const;
    void setAngleOffset(double value);

protected:
    static void appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice);
    static int slicesListLength(QQmlListProperty<PieSlice> *slicesList);
    static PieSlice *sliceAt(QQmlListProperty<PieSlice> *slicesList, int index);
    QList<PieSlice *> slicesList;
    void paint(QPainter *painter) override;

private:
    double pAngleOffset;
    double sumSliceValue;
    ChartPen *pStrokePen;

signals:
    void slicesChanged();
    void angleOffsetChanged();
    void strokePenChanged();

public slots:
    void calculateDataRange();

};

#endif // PIECHART_H
