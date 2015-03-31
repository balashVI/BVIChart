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

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    bool visible() const;
    void setVisible(bool value);

    ///Повертає QPen
    Q_INVOKABLE const QPen &getPen() const;

private:
    QPen pen;
    bool pVisible;

signals:
    void widthChanged();
    void colorChanged();
    void visibleChanged();

};

#endif // CHARTPEN_H
