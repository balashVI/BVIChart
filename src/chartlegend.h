#ifndef CHARTLEGEND_H
#define CHARTLEGEND_H

#include <QQuickItem>

class ChartLegend : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(LegendLocation)
public:
    explicit ChartLegend(QQuickItem *parent = 0);

    void setLegendData(QVector<QString>&& labels, QVector<QColor> && colors);
    enum LegendLocation{TopLocation, RightLocation, BottomLocation, LeftLocation};

    Q_PROPERTY(int location READ location WRITE setLocation NOTIFY locationChanged)

    void setLocation(int value);
    LegendLocation location() const;

private:
    LegendLocation pLocation;

signals:
    void locationChanged();

public slots:

};

#endif // CHARTLEGEND_H
