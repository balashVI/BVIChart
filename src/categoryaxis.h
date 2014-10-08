#ifndef CATEGORYAXIS_H
#define CATEGORYAXIS_H

#include "abstractaxis.h"

class CategoryAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit CategoryAxis(QQuickItem *parent = 0);

    //Задає кількість категорій
    void setNumberOfCategories(int value);

private:
    virtual void paint(QPainter *painter);
    int numberOfCategories;

signals:

public slots:

};

#endif // CATEGORYAXIS_H
