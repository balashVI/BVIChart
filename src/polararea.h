#ifndef POLARAREA_H
#define POLARAREA_H

#include "pieslice.h"

class PolarArea : public PieSlice
{
    Q_OBJECT
public:
    explicit PolarArea(QQuickItem *parent = 0);
};

#endif // POLARAREA_H
