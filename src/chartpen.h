#ifndef CHARTPEN_H
#define CHARTPEN_H

#include <QPen>

/**
 * @brief Клас ChartPen
 *
 * Клас призначений для доступу до властивостей класу QPen методами QML
 */
class ChartPen : public QObject
{
    Q_OBJECT
public:
    explicit ChartPen(QObject *parent = 0);

    ///Ширина лінії
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    int width() const;
    void setWidth(int newWidth);

    ///Колір лінії
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    QColor color() const;
    void setColor(const QColor &newColor);

private:
    QPen pen;

signals:
    void widthChanged();
    void colorChanged();

};

#endif // CHARTPEN_H
