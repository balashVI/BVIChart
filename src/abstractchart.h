#ifndef ABSTRACTCHART_H
#define ABSTRACTCHART_H

#include <QQuickItem>
#include "chartheader.h"
#include "chartlegend.h"

class AbstractChart : public QQuickItem
{
    Q_OBJECT
public:
    explicit AbstractChart(QQuickItem *parent = 0);
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) override;

    Q_PROPERTY(ChartHeader* header READ header NOTIFY headerChanged)
    Q_PROPERTY(ChartLegend* legend READ legend NOTIFY legendChanged)
    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY paddingChanged)

    void setPadding(int value);
    int padding() const;
    ChartHeader *header();
    ChartLegend *legend();

protected:
    ChartHeader pHeader;
    ChartLegend pLegend;
    int pPadding;

signals:
    void headerChanged();
    void legendChanged();
    void paddingChanged();

private slots:
    virtual void updateChildrenGeometry();
};

#endif // ABSTRACTCHART_H
