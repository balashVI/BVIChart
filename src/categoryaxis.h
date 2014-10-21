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
    //Обчислює положення лінії осі
    int calculateAxisLinePosition();

private:
    virtual void paint(QPainter *painter) override;
    int numberOfCategories, axisLinePosition;
    int space; //Містить значення відступів між елементами

signals:

public slots:

};

#endif // CATEGORYAXIS_H
