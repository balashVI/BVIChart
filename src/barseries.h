#ifndef BARSERIES_H
#define BARSERIES_H

#include "abstractseries.h"

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
    explicit BarSeries(QQuickItem *parent = 0);

protected:
    virtual void paint(QPainter *painter);

signals:

public slots:

};

#endif // BARSERIES_H
