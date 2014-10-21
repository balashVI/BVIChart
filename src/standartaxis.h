#ifndef STANDARTAXIS_H
#define STANDARTAXIS_H

#include "abstractaxis.h"

class StandartAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit StandartAxis(QQuickItem *parent = 0);

    int calculateAxisLinePosition();

private:
    virtual void paint(QPainter *painter) override;

signals:

public slots:

};

#endif // STANDARTAXIS_H
