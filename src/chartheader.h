#ifndef ChartHeader_H
#define ChartHeader_H

#include <QQuickPaintedItem>
#include "chartfont.h"

/**
 * @brief Заголовок графіка
 *
 * Малює заголовок графіка
 */
class ChartHeader : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit ChartHeader(QQuickItem *parent = 0);

    /// Задає заголовок графіка
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    ///Задає налаштування шрифта заголовка
    Q_PROPERTY(ChartFont* font READ font WRITE setFont NOTIFY fontChanged)

    ///Задає колір заголовка
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)

    void setTitleColor(const QColor& value);
    const QColor& titleColor() const;
    void setFont(ChartFont* value);
    ChartFont* font();
    const QString& title() const;
    void setTitle(const QString& value);

private:
    virtual void paint(QPainter *painter);

    QString pTitle;
    ChartFont *pFont;
    QColor pTitleColor;

signals:
    void titleChanged();
    void fontChanged();
    void titleColorChanged();
    void sizeChanged();

private slots:
    void recalculateSize();
};

#endif // ChartHeader_H
