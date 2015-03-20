#ifndef CATEGORYAXIS_H
#define CATEGORYAXIS_H

#include "abstractaxis.h"

class CategoryAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit CategoryAxis(QQuickItem *parent = 0);

    ///Містить список даних
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    const QList<QString> &labels() const;
    void setLabels(QList<QString> newLabels);

    void setNumberOfCategories(int value);
    int getWidthOfMaxLabel();//Повертає довжину найдовшого підпису

private:
    int numberOfCategories;
    QList<QString> pLabels;
    int widthOfMaxLabel;

    void calculateWidthOfMaxLabel(); //Обчислює довжину найдовшого підпису

signals:
    void labelsChanged();

public slots:

};

#endif // CATEGORYAXIS_H
