#ifndef PIESLICE_H
#define PIESLICE_H

#include <QQuickItem>
#include <QColor>
#include "chartpen.h"

/**
 * @brief Сегмент PieChart
 *
 * Інкапсулює властивості сегмента графіка PieChart
 */
class PieSlice : public QQuickItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit PieSlice(QQuickItem *parent = 0);

    ///Задає числове значення сегмента
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

    ///Задає назву сегмента
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

    ///Задає колір мегмента
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    void setColor(const QColor& value);
    const QColor& color() const;
    void setLabel(const QString &value);
    const QString& label() const;
    double value() const;
    void setValue(double value);

private:
    double pValue;
    QString pLabel;
    QColor pColor;

signals:
    void valueChanged();
    void labelChanged();
    void colorChanged();

public slots:

};

#endif // PIESLICE_H
