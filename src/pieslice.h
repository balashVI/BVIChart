#ifndef PIESLICE_H
#define PIESLICE_H

#include <QQuickItem>
#include <QColor>
#include "chartpen.h"
#include "abstractseries.h"

/**
 * @brief Сегмент PieChart
 *
 * Інкапсулює властивості сегмента графіка PieChart
 */
class PieSlice : public AbstractSeries
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit PieSlice(QQuickItem *parent = 0);

    ///Задає числове значення сегмента
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

    double value() const;
    void setValue(double value);

private:
    double pValue;

signals:
    void valueChanged();

public slots:

};

#endif // PIESLICE_H
