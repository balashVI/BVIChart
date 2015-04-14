#ifndef CHARTPOINT_H
#define CHARTPOINT_H

#include <QQuickItem>

class ChartPoint : public QQuickItem
{
    Q_OBJECT
public:
    explicit ChartPoint(QQuickItem *parent = 0);
    ~ChartPoint();

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    double x() const;
    void setX(double value);

    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    double y() const;
    void setY(double value);

protected:
    double pX, pY;

signals:
    void xChanged();
    void yChanged();

public slots:
};

#endif // CHARTPOINT_H
