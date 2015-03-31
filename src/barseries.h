#ifndef BARSERIES_H
#define BARSERIES_H

#include "abstractseries.h"
#include "chartpen.h"

/**
 * @brief Стовпчикова серія
 *
 * Малює серії стовпчикових графіків
 */
class BarSeries : public AbstractSeries
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit BarSeries(QObject *parent = 0);

    ///Містить список даних
    Q_PROPERTY(QList<double> data READ data WRITE setData NOTIFY dataChanged)

    ///Містить налаштування лінії обведення стовпців
    Q_PROPERTY(ChartPen* strokePen READ strokePen WRITE setStrokePen NOTIFY strokePenChanged)

    ///Містить колір заливки стовпця
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    QColor color() const;
    void setColor(const QColor &newColor);

    ChartPen* strokePen() const;
    void setStrokePen(ChartPen* value);

    const QList<double> &data() const;
    void setData(QList<double> value);

private:
    QList<double> pData;
    ChartPen *pStrokePen;
    QColor pColor;

signals:
    void dataChanged();
    void strokePenChanged();
    void colorChanged();

public slots:

};

#endif // BARSERIES_H
