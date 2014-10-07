#ifndef ABSTRACTAXIS_H
#define ABSTRACTAXIS_H

#include <QQuickPaintedItem>

class AbstractAxis : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit AbstractAxis(QQuickItem *parent = 0);

    ///Містить користувацькі позначки осі
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    void setLabels(QList<QString> in);
    QList<QString> labels() const;

protected:
    QList<QString> pLabels;

signals:
    void labelsChanged();

public slots:

};

#endif // ABSTRACTAXIS_H
