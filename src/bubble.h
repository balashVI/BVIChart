#ifndef BUBBLE_H
#define BUBBLE_H

#include "chartpoint.h"

class Bubble : public ChartPoint
{
    Q_OBJECT
public:
    explicit Bubble(QQuickItem *parent = 0);
    ~Bubble();

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    double value() const;
    void setValue(double value);

protected:
    double pValue;

signals:
    void valueChanged();
};

#endif // BUBBLE_H

