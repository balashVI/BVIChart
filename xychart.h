#ifndef XYChart_H
#define XYChart_H

#include <QQuickItem>
#include "chartheader.h"

class XYChart : public QQuickItem
{
    Q_OBJECT
public:
    explicit XYChart(QQuickItem *parent = 0);
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

    Q_PROPERTY(ChartHeader* header READ header)
    ChartHeader *header();

private:
    ChartHeader pHeader;

signals:

public slots:

};

#endif // XYChart_H
