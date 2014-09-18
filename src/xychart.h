#ifndef XYChart_H
#define XYChart_H

#include <QQuickItem>
#include "chartheader.h"
#include "abstractchart.h"

class XYChart : public AbstractChart
{
    Q_OBJECT
public:
    explicit XYChart(QQuickItem *parent = 0);

private:


signals:

public slots:

};

#endif // XYChart_H
