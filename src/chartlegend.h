#ifndef CHARTLEGEND_H
#define CHARTLEGEND_H

#include <QQuickItem>

/**
 * @brief Легенда графіка
 *
 * Малює легенду графіка, та містить усі властивості для її налаштування
 */
class ChartLegend : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(LegendLocation)
public:
    explicit ChartLegend(QQuickItem *parent = 0);

    void setLegendData(QVector<QString>&& labels, QVector<QColor> && colors);

    ///Способи розміщення легенди відносно полотна графіка
    enum LegendLocation{
        ///зверху
        TopLocation,
        ///справа
        RightLocation,
        ///знизу
        BottomLocation,
        ///зліва
        LeftLocation,
    };

    ///Задає положення легенди відносно полотна графіка
    Q_PROPERTY(int location READ location WRITE setLocation NOTIFY locationChanged)

    void setLocation(int value);
    LegendLocation location() const;

private:
    LegendLocation pLocation;

signals:
    void locationChanged();

public slots:

};

#endif // CHARTLEGEND_H
