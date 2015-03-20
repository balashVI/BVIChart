#ifndef XYChart_H
#define XYChart_H

#include <QQuickItem>
#include "abstractchart.h"

class XYChart : public AbstractChart
{
    Q_OBJECT
public:
    explicit XYChart(QQuickPaintedItem *parent = 0);

private:


signals:

public slots:

};

#endif // XYChart_H
