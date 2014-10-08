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

    ///Містить список даних
    Q_PROPERTY(QList<double> data READ data WRITE setData NOTIFY dataChanged)

    const QList<double> &data() const;
    void setData(QList<double> value);

private:
    QList<double> pData;

protected:
    virtual void paint(QPainter *painter);

signals:
    void dataChanged();

public slots:

};

#endif // BARSERIES_H
