#ifndef CHARTLEGEND_H
#define CHARTLEGEND_H

#include <QQuickPaintedItem>
#include "abstractseries.h"
#include "chartfont.h"

/**
 * @brief Легенда графіка
 *
 * Малює легенду графіка, та містить усі властивості для її налаштування
 */
class ChartLegend : public QQuickPaintedItem
{
    Q_OBJECT
    Q_ENUMS(LegendLocation)
public:
    ///Конструктор класу
    explicit ChartLegend(QQuickItem *parent = 0);

    void recalculateSize(int newSize);
    void setSeriesList(QList<AbstractSeries*>* list);

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
    ///Задає нашалтування шрифта
    Q_PROPERTY(ChartFont* font READ font WRITE setFont NOTIFY fontChanged)
    ///Задає ширину елемента легенди
    Q_PROPERTY(int elementsWidth READ elementsWidth WRITE setElementsWidth NOTIFY elementsWidthChanged)

    void setElementsWidth(int value);
    int elementsWidth() const;
    void setFont(ChartFont* value);
    ChartFont* font();
    void setLocation(int value);
    LegendLocation location() const;

private:
    LegendLocation pLocation;
    QList<AbstractSeries*> *series;
    ChartFont *pFont;
    int pElementsWidth;

    int mElementsHeight; //Висота елемента легенди
    int rows, columns; //Кількість стовпців та рядків легенди

    virtual void paint(QPainter *painter);

signals:
    void locationChanged();
    void fontChanged();
    void elementsWidthChanged();

public slots:
    void updateLegend();

private slots:
    void calculateElementsHeight();

};

#endif // CHARTLEGEND_H
